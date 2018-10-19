
#include <iostream>
#include <vector>

#include "active_measurement.h"

using namespace std;

//开始进行主动测量
//return 1:sucess;
int ActiveMeasuremnet_control(bool enable) {
  return 1;
}

int ActiveMeasurement_write_entry(int entry_id, active_measurement_task_t *entry)
{
  return 1;
}

int ActiveMeasurement_delete_entry(int entry_id) {
  // FIXME: wait hardare
  return 1;
}

// 读取主动测量结果，size为想要读取几个，返回值为读到的数量
int ActiveMeasurement_read_report(unsigned int task_id, active_measurement_result_t* result, int size) {
  return 10;
}


/*
//(QA6:没懂。。。如果expire超时，就调用这个注册的回调函数)
//硬件通过这个callback注册函数，返回结果
int ActiveMeasurement_register_expire_callback(active_measurement_expire_cb func) {

}
*/
