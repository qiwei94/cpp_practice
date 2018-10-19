/**** Private project. All rights reserved ****/
//kiwi
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <queue>
#include <future>
#include <thread>
#include <chrono> //std::chrono::seconds
#include <unistd.h>
#include <assert.h>
#include <future>
using namespace std;
/*
//the measure task type : active or passive
typedef enum {
  ACTIVE,
  PASSIVE,
} measurement_task_type_t;

//active measure task type
typedef enum {
  PERIODIC,
  SINGLE_BURST,
  REACTIVE,
} active_measurement_task_type_t;

typedef struct{
  int inverval;
  int packet_templete_id;
} periodic_measure_t;

//the variable in packet(used for packet gen to override )
typedef struct {
  long long start; // FIXME: 64bit OK?
  long long end;
  long long step;
} variable_field_t;

//the packet generator
typedef struct {
  int packet_mixer_p4_action_id;
  int packet_template_id;
  variable_field_t override_field; // FIXME: 1 field OK?
} packet_generator_t;

//what is this?
typedef struct {
    int field_id;
    int field_bit_length;
    char* field_value;
} static_field_t;

//track the packet 
typedef struct {
  int packet_p4_action_id;
  static_field_t* static_fields;
  variable_field_t variable_field;
  uint64_t timeout;
} packet_tracker_t;

//get the offset=length packet value
typedef struct {
  int packet_p4_action_id;
  int metadata;
} packet_extracter_t;

//some math need to be relaize here
typedef struct {
  // TODO: NOT READ NOW, MATH FILTERS: EWMA, AVERAGE, BLOOM FILTER ...
} extend_math_t;

//what is this?
typedef struct {
  //report_control_t;
} report_generator_t;

typedef enum{
  SEND,
  WAIT,
  REPORT,
  DELETE,
} active_event_t;

typedef struct{
  active_event_t event_state;
  int time;
} active_state_t;

typedef struct
{
  unsigned int associated_task_id;
  unsigned long variable_field_value;
  unsigned int found;
  unsigned long rtt;
  unsigned int field_0;
  unsigned int field_1;
  unsigned int field_2;
  unsigned int field_3;
} active_measurement_result_t;

typedef struct
{
  unsigned int task_id;                         //任务的id
  unsigned int task_category : 2;               //主动测量类型
  unsigned int template_id : 14;                //包模板类型
  unsigned int variable_field_type : 8;         //TODO
  unsigned int variable_field_step : 8;         //
  unsigned int variable_field_start_value : 32; //
  unsigned int task_fire_interval : 32;         //周期任务的interval
  unsigned int burst_size : 16;                 //burst数据包的大小
  unsigned int reserved_0 : 16;                 //do nothing
  unsigned char report_field_1 : 8;             //action id 决定去抓哪个域
  unsigned char report_field_2 : 8;             //
  unsigned char report_field_3 : 8;             //
  unsigned char report_field_4 : 8;             //
  unsigned int reserved_1 : 32;                 //保留字段
  unsigned int reserved_2 : 32;                 //
  unsigned int reserved_3 : 32;                 //
  
  queue<active_measurement_result_t*> result;
  pthread_t thread_id;
  promise<void> exitSignal;
  future<void> futureObj;
} active_measurement_task_t;
*/


//active measurement function
/*
explain:加入一个数据包进入数据包模板
parameter:int id:数据包的逻辑id;char* packet_data:数据包的指针;int size 数据包的大小
return: 1:成功  0:失败
*/
int add_packet_templete(int id, char *packet_data,int size);

/*
explain:从模板列表中删除某个数据
parameter:int id: 数据包的逻辑id
return: 1:成功  0:失败
*/
int delete_packet_templete(int id);

/*
explain:加入一个主动测量任务
parameter:含义见下表
return: 1:成功  0:失败
*/
int add_active_task(
    unsigned int task_id,                    //主动测量的task_id
    unsigned int task_category,              //测量的类型
    unsigned int template_id,                //包模板id
    unsigned int variable_field_type,        //TODO：可变域的id名
    unsigned int variable_field_step,        //可变域的步长
    unsigned int variable_field_start_value, //可变域的起始值
    unsigned int task_fire_interval,         //发送时间间隔
    unsigned int burst_size);                //发送burst数据包的大小

/*
explain:删除一个主动测量任务
parameter:int task_id:任务的id
return: 1:成功  0:失败
*/
int delete_active_task(int task_id);

/*
explain:获取一个主动测量任务的结果
parameter:int task_id:任务的id
return: 这个result结构体
*/
active_measurement_result_t *query_task_result(int task_id);

/*the passive measure:
condition:3 kinds of condition to update info,what kind of packet info to update (when to update)
target:where to update the result(the destanation of the result)
res:the result format to update(what to update)
*/

/*
typedef struct
{
  //FIXME: master, monitor 
  ip
  type: master/monitor
} peer_connected;
*/

typedef struct {
  //FIXME
  int id;
  char* data;
  int size;
} packet_template_t;


typedef struct{
  int result;
} count_res_t;


typedef struct {
  int id;
  int task_id;
  int group_id;
  int interval;
  int period;
  pthread_t thread_id;
  promise<void> exitSignal;
  future<void> futureObj;
  count_res_t result;
} passive_measurement_task_t;

/*
explain:增加一个被动测量任务
parameter:int task_id:任务id ，int interval：时间间隔
return: 1:成功  0：失败
*/
int passive_measure(int task_id,int interval);

/*
explain:获取被动测量任务的结果
parameter:int task_id:任务id 
return: count_res (TODO)
*/
count_res_t get_task_result(int task_id);

/*
explain:结束一个被动测量任务
parameter:int task_id:任务id 
return: 1：成功 0：失败
*/
int shutdow_task(int task_id);
