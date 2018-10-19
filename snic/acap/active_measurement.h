

typedef struct {
  unsigned int task_category                  :  2; //主动测量类型
  unsigned int template_id                    : 14; //包模板类型
  unsigned int variable_field_type            :  8; //TODO
  unsigned int variable_field_step            :  8; //
  unsigned int variable_field_start_value     : 32; //
  unsigned int task_fire_interval             : 32; //周期任务的interval
  unsigned int burst_size                     : 16; //burst数据包的大小
  unsigned int reserved_0                     : 16; //do nothing
  unsigned char report_field_1                :  8; //action id 决定去抓哪个域
  unsigned char report_field_2                :  8; //
  unsigned char report_field_3                :  8; //
  unsigned char report_field_4                :  8; //
  unsigned int reserved_1                     : 32; //保留字段
  unsigned int reserved_2                     : 32; //
  unsigned int reserved_3                     : 32; //
} active_measurement_task_t;

typedef struct {
  unsigned int associated_task_id;
  unsigned long variable_field_value;
  unsigned int found;
  unsigned long rtt;
  unsigned int field_0;
  unsigned int field_1;
  unsigned int field_2;
  unsigned int field_3;
} active_measurement_result_t;

typedef struct {
  unsigned int report_valid                     :  1;
  unsigned int report_type                      :  1;
  unsigned int task_id                          : 14;
  unsigned long long match_field                : 64;
  unsigned long long sent_time                  : 64;
  unsigned long long received_time              : 64;
  // other report fields
} active_measurement_result_hw_t;

typedef int (*active_measurement_expire_cb)(unsigned int task_id, active_measurement_result_t* result);

/*
explain:开启主动测量任务
parameter:bool enable = 1 ,开启测试
return:1:成功 0：失败 
*/
int ActiveMeasuremnet_control(bool enable);

/*
explain:增加一个主动测量任务
parameter:active_measurement_task_t* entry
return:1:成功 0：失败 
*/
int ActiveMeasurement_write_entry(int entry_id, active_measurement_task_t* entry) ;

/*
explain:删除一个主动测量任务
parameter:int entry_id：任务编号
return:1:成功 0：失败 
*/
int ActiveMeasurement_delete_entry(int entry_id);

int ActiveMeasurement_read_report(unsigned int task_id, active_measurement_result_t *result, int size);

/*
//explain:返回测量结果的回调函数
//parameter:注册回调函数
//return:1:成功 0：失败 
int ActiveMeasurement_register_callback(active_measurement_expire_cb func) ;
*/