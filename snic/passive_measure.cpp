#include "measurement.h"
//#include <pthread.h>
#include <time.h>
#include <iostream>
#include <unistd.h>
#include <map>
#include <vector>
#include <thread>
#include <chrono> //std::chrono::seconds
#include <unistd.h>
#include <assert.h>
#include <future>

using namespace std;

map<int,passive_measurement_task_t*> passive_task_map;

void *get_counter(void *threadarg)
{
  passive_measurement_task_t *task;
  task=(passive_measurement_task_t*)threadarg;
  int task_id=task->task_id;
  int interval=task->interval;
  int period=task->period;
  //TODO，头文件怎么包含？？？？
  //PassiveMeasurement_set_hw_freq(100);
  //PassiveMeasurement_control(true);
  int test_counter=1000;
  while(!(task->exit_flag))
  {
    sleep(interval);
    //FIX ME
    //get_counter(&(task->count_res))
    //put the result into task->count_res_t
    test_counter--;
    cout<< "task id=" << task_id << "  say :"<<test_counter<< endl;
    map<int, passive_measurement_task_t*>::iterator res_add = passive_task_map.find(task_id);
    if (res_add != passive_task_map.end())
    {
      passive_measurement_task_t* key=passive_task_map[task_id];
      (key->result).result = test_counter;
    }
  }
  map<int,passive_measurement_task_t*>::iterator key_erase=passive_task_map.find(task_id);
  if(key_erase!=passive_task_map.end()){
    passive_task_map.erase(key_erase);
  }
  pthread_exit(NULL);
}



int add_passive_measure_task(
  int task_id,
  //int period,
  int interval
){
  passive_measurement_task_t* p_task=new(passive_measurement_task_t);
  p_task->task_id=task_id;
  p_task->group_id=0;
  p_task->interval=interval;
  thread th(&get_counter,p_task);
  p_task->exit_flag=false;
  map<int, passive_measurement_task_t *>::iterator key = passive_task_map.find(task_id);
  if(key==passive_task_map.end()){
    passive_task_map.insert(std::pair<int,passive_measurement_task_t*>(task_id,p_task));
  }else{
    return 0;
  }
  th.detach();
  return 1;
}

count_res_t get_passive_task_result(int task_id){
  passive_measurement_task_t* task;
  //task->result->result=0;
  map<int,passive_measurement_task_t*>::iterator key=passive_task_map.find(task_id);
  if(key!=passive_task_map.end()){
    task=passive_task_map[task_id];
    return task->result;
  }else{
    count_res_t count_result;
    count_result.result=0;
    return count_result;
  }
}


int shutdow_task(int task_id){
  map<int, passive_measurement_task_t *>::iterator key = passive_task_map.find(task_id);
  if (key != passive_task_map.end())
  {
    passive_measurement_task_t* p_task=passive_task_map[task_id];
    p_task->exit_flag=true;
    delete(p_task);
    passive_task_map.erase(task_id);
    return 1;
  }
  else
  {
    return 0;
  }
}


