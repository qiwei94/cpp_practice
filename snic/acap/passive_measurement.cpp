
#include<iostream>
#include<vector>
#include<map>
#include<set>

#include "passive_measurement.h"

#define PASSIVE_MEASUREMENT_BASE 0x90000
#define PASSIVE_MEASUREMENT_COUNTER_WIDTH 4
#define PASSIVE_MEASUREMENT_COUNTER_SIZE 1024;

static int passive_measurement_counter_size;

int PassiveMeasurement_control(bool enable) {
  // FIXME:
  // TODO: hardware defination
  return 0;
}

int PassiveMeasurement_set_hw_freq(long long freq) {
  // FIXME:
  // TODO: hardware defination
  // hardware not support
  return 1;
}

int PassiveMeasurement_set_counter_array_size(int size) {
  return 0;
}

int PassiveMeasurement_get_counter_array_size() {
  return PASSIVE_MEASUREMENT_COUNTER_SIZE;
}

int PassiveMeasurement_get_counter_width() {
  return PASSIVE_MEASUREMENT_COUNTER_WIDTH;
}

int PassiveMeasurement_get_counter_array_block(char* data, int max_size) {
  return 1;
}

int PassiveMeasurement_get_counter_array_nonblock(char* data, int max_size) {

  return 1;
}

