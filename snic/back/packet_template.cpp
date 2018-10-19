
#include<iostream>
#include<vector>
#include<map>
#include<set>

#include "arm/ureg.h"
#include "packet_template.h"

#define PACKET_TEMPLATE_BASE_ADDR 0x10000;
#define PACKET_TEMPLATE_ENTRY_WIDTH 256;
#define PACKET_TEMPLATE_SIZE 16;

using namespace std;
static map<int,vector<char>> packet_template_db;
static vector<int> packet_template_free_id;


int insert_packet_template(int id, char* packet_data, int size) {
  unsigned * buff = (unsigned*)malloc(size+4);
  memset(buff, 0, size+4);
  memcpy(buff, packet_data, size);
  writeReg32(PACKET_TEMPLATE_BASE_ADDR, PACKET_TEMPLATE_ENTRY_WIDTH*id, size);
  for(int i=0; i<size; i+=4) {
    writeReg32(PACKET_TEMPLATE_BASE_ADDR, PACKET_TEMPLATE_ENTRY_WIDTH*id+i+1, *(buff+i));
  }
  return 0;
}

int delete_packet_template(int id) {
  // TODO: call hardware delete
  // FIXME: waiting for hardware
  writeReg32(PACKET_TEMPLATE_BASE_ADDR, PACKET_TEMPLATE_WIDTH*id, 0);
  return 0;
}

int clean_packet_template_table() {
  // TODO: call hardware clean all
  // FIXME: waiting for hardware
  return -1;
}

int get_packet_template_table_size() {
  return PACKET_TEMPLATE_SIZE;
}

int init_packet_template() {
  clean_packet_template_table();
  // TODO: call hardware init
  // FIXME: wait for hardware
  return 0;
}