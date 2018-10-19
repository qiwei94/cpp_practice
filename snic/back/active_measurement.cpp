
#include<iostream>
#include<vector>

#include "arm/ureg.h"
#include "arm/udma.h"

#inlcude<active_measurement.h>

#define ACTIVE_MEASUREMENT_TABLE_BASE 0x20000;
#define ACTIVE_MEASUREMENT_ENTRY_WIDTH 32;
#define ACTIVE_MEASUREMENT_TABLE_DEPTH 128;

static dma_dev_t* dma;

using namespace std;

//开始进行主动测量
int ActiveMeasuremnet_control(bool enable) {
  // FIXME: hardwaer address and description
  // TODO: wait for hardware

  // initial dma
  dma = dma_init(0x40400000, 65535, 0x0e000000, 0x0f000000);
}

int ActiveMeasurement_write_entry(int entry_id, active_measurement_task_t* entry) {
  int size = ACTIVE_MEASUREMENT_ENTRY_WIDTH;
  unsigned * buff = (unsigned*)malloc(size+4);
  memset(buff, 0, size+4);
  memcpy(buff, entry, size);
  for(int i=0; i<size; i+=4) {
    writeReg32(PACKET_TEMPLATE_BASE_ADDR, ACTIVE_MEASUREMENT_ENTRY_WIDTH*id+i, *(buff+i));
  }
  return 0;
}

int ActiveMeasurement_delete_entry(int entry_id) {
  // FIXME: wait hardare
  return -1;
}

// 读取主动测量结果，size为想要读取几个，返回值为读到的数量
int ActiveMeasurement_read_report(unsigned int task_id, active_measurement_result_t* result, int size) {
  // read some register, get the data existed in dma
  int report_size;
  //TODO: read hardware register, wait for hardware
  report_size = report_size<size?report_size:size;
  dma_receive_block(dma, report_size*ACTIVE_MEASUREMENT_ENTRY_WIDTH);
  memcpy(result, dma->virtual_destination_address, report_size*ACTIVE_MEASUREMENT_ENTRY_WIDTH);
  return report_size;
}
/*
//(QA6:没懂。。。如果expire超时，就调用这个注册的回调函数)
//硬件通过这个callback注册函数，返回结果
int ActiveMeasurement_register_expire_callback(active_measurement_expire_cb func) {

}
*/
