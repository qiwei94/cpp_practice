
#include<iostream>
#include<vector>
#include<map>
#include<set>
#include "packet_template.h"
using namespace std;

int insert_packet_template(int id, char* packet_data, int size) {
  return 1;
}

int delete_packet_template(int id) {
  // TODO: call hardware delete
  // FIXME: waiting for hardware
  return 1;
}

int clean_packet_template_table() {
  // TODO: call hardware clean all
  // FIXME: waiting for hardware
  return 1;
}

int get_packet_template_table_size() {
  return 1;
}

int init_packet_template() {
  //clean_packet_template_table();
  // TODO: call hardware init
  // FIXME: wait for hardware
  return 1;
}
