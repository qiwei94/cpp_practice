#include "measurement.h"
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <map>
#include <string>
#include "../acap/active_measurement.h"
#include "../acap/measurement.h"

using namespace std;

#define max_result 2

/*
将进行一次主动测量的过程分为：
init过程：
向硬件中插入需要的包模板类型：
1、ping包 2、tcp包seq包  

添加测量任务过程：
1、将任务识别并拆分成具体的任务
2、添加测量任务

删除测量任务：
1、删除测量任务表项

*/

map<int,active_measurement_task_t*> active_task_map;
//key:task_id;
//value:entry id
map<int,int> a_task_entry;
//key:entry id
//value:task id
map<int,int> a_entry_task;


//存放包模板id和实际硬件中包位置对应关系
//key：index of the hardware table
//value: packet templete id 
//used for add a packet templete
map<int,int>  packet_templete_index;

//key:the packet templete id 
//value:index of the hw table id 
//used for 
map<int, int> anti_packet_templete_index;
    //获取可用的最小的包模板的id
int free_packet_templete_id()
{
  if(packet_templete_index.empty()){
    return 0;
  }
  map<int,int>::iterator it;
  int count=0;
  for(it=packet_templete_index.begin();it!=packet_templete_index.end();it++){
    if(count!=it->first){
      return count;
    }
    count++;
  }
  return count;
}

int add_packet_templete(int id, char *packet_data,int size)
{
  int min_free_pac_id=free_packet_templete_id();
  map<int,int>::iterator it=packet_templete_index.find(min_free_pac_id);
  map<int,int>::iterator a_it =anti_packet_templete_index.find(id);
  if (it == packet_templete_index.end() && a_it!=anti_packet_templete_index.end())
  {
    if(insert_packet_template(min_free_pac_id,packet_data,size)){
      packet_templete_index.insert(pair<int,int>(min_free_pac_id,id));
      anti_packet_templete_index.insert(pair<int,int>(id,min_free_pac_id));
      cout<<"id="<<id<<" insert at "<<min_free_pac_id<<endl;
      return 1;
    }else{
      return 0;
    }
  }else{
    cout<<"the min free pac id is not valid"<<endl;
    return 0;
  }
}

int delete_packet_templete(int id){
  map<int, int>::iterator it = anti_packet_templete_index.find(id);
  if(it!=anti_packet_templete_index.end()){
    int hw_id = anti_packet_templete_index[id];
    if(delete_packet_template(hw_id)){
      anti_packet_templete_index.erase(id);
      packet_templete_index.erase(hw_id);
      return 1;
    }else{
      return 0;
    }
  }else{
    return 0;
  }
}

bool id_in_entry(int id){
  map<int,int>::iterator it = a_entry_task.find(id);
  if(it==a_entry_task.end()){
    return false;
  }else{
    return true;
  }
}

bool id_in_task(int id){
  map<int, int>::iterator it = a_task_entry.find(id);
  if (it == a_task_entry.end()){
    return false;
  }else{
    return true;
  }
}

int free_entry_id()
{
  if (a_entry_task.empty())
  {
    return 0;
  }
  map<int, int>::iterator it;
  int count = 0;
  for (it = a_entry_task.begin(); it != a_entry_task.end(); it++)
  {
    if (count != it->first)
    {
      return count;
    }
    count++;
  }
  return count;
}


void *get_result(void *threadarg){
  active_measurement_task_t *task;
  task=(active_measurement_task_t*)threadarg;
  int task_id=task->task_id;
  int interval=task->task_fire_interval;
  std::future<void> futureObj = task->futureObj;
  while (futureObj.wait_for(std::chrono::milliseconds(1)) == std::future_status::timeout)
  {
    sleep(interval);
    active_measurement_result_t* tmp_task_res = new (active_measurement_result_t);
    ActiveMeasurement_read_report(task->task_id,tmp_task_res);
    if ((task->result).size() < max_result){
      (task->result).push(tmp_task_res);
    }else{
      active_measurement_task_t* rush_task=(task->result).front();
      delete(rush_task);
      (task->result).push(tmp_task_res);
    }
    
  }
  map<int, active_measurement_task_t *>::iterator key_erase = active_task_map.find(task_id);
  if (key_erase != active_task_map.end())
  {
    active_task_map.erase(key_erase);
  }
  pthread_exit(NULL);
}

int add_active_task(
  unsigned int task_id,
  unsigned int task_category,              //
  unsigned int template_id,                //包模板类型
  unsigned int variable_field_type,        //TODO
  unsigned int variable_field_step,        //
  unsigned int variable_field_start_value, //
  unsigned int task_fire_interval,
  unsigned int burst_size,
  unsigned char report_field_1
)
{
  active_measurement_task_t* a_task=new(active_measurement_task_t);
  a_task->task_category=task_category;
  a_task->template_id=template_id;
  a_task->variable_field_type=variable_field_type;
  a_task->variable_field_step=variable_field_step;
  a_task->variable_field_start_value=variable_field_start_value;
  a_task->task_fire_interval=task_fire_interval;
  a_task->burst_size=burst_size;
  a_task->report_field_1=report_field_1;

  map<int, active_measurement_task_t *>::iterator it = active_task_map.find(task_id);
  int entry_id=free_entry_id();
  if(!id_in_entry(entry_id)||!id_in_task(task_id)){
    return 0;
  }
  if(it==active_task_map.end()){
    promise<void> exitSignal;
    future<void> futureObj = exitSignal.get_future();
    thread th(&get_result,a_task,std::move(futureObj));
    pthread_t task_handle=th.native_handle();
    a_task->thread_id=task_handle;
    a_task->exitSignal=exitSignal;
    active_task_map[task_id] = a_task;
    a_entry_task[entry_id] = task_id;
    a_task_entry[task_id] = entry_id;
    return 1;
  }
  else{
    return 0;
  }
}

int delete_active_task(int task_id){
  if(id_in_task(task_id)){
    int entry_id=a_task_entry[task_id];
    if(ActiveMeasurement_delete_entry(entry_id)){
      a_entry_task.erase(entry_id);
      a_task_entry.erase(task_id);
      active_measurement_task_t* a_task=active_task_map[task_id];
      a_task->exitSignal.set_value();
      delete(a_task);
      active_task_map.erase(task_id);
      return 1;
    }else{
      return 0;
    }
  }else{
    return 0;
  }

}

active_measurement_result_t* query_task_result(int task_id)
{
  active_measurement_task_t* a_task;
  map<int,active_measurement_task_t*>::iterator it=active_task_map.find(task_id);
  if(it!=active_task_map.end()){
    a_task=active_task_map[task_id];
    //TODO：return the result
    //what is the interface to return result
    //now we return the first result,but store 10
    
    //unsigned long rtt_sum;

    return (a_task->result).front();
  }
}



