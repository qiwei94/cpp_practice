
/*
explain:
parameter:
return:
*/

/*
explain:是否开启被动测量
parameter: bool enable:1:开启
return: 1:成功 0:失败
*/
int PassiveMeasurement_control(bool enable); // enable/disable

/*
explain:设置硬件的频率
parameter: long long freq (单位:hz)
return: 1:成功 0:失败
*/
int PassiveMeasurement_set_hw_freq(long long freq);

/*
explain:设置counter size
parameter:int size :counter的条数
return: 1:成功 0:失败
*/
int PassiveMeasurement_set_counter_array_size(int size);

/*
explain:传出测量的counter的结果（一直存到max_size条）
parameter:char* data:存放结果的指针 int max_size:在data指针处存放max_size条counter大小的counter结果
return: 成功读取的counter的数量
*/
int PassiveMeasurement_get_counter_array_block(char* data, int max_size);

/*
explain:传出测量的counter的结果（硬件读到多少，就存多少）
parameter:char* data:存放结果的指针 int max_size:在data指针处存放counter大小的counter结果（<max_size）
return: 成功读取的counter的数量
没有实现
*/
int PassiveMeasurement_get_counter_array_nonblock(char* data, int max_size); 

// 读取相关entry数量
int PassiveMeasurement_get_counter_array_size();

// 读取每个entry对应的counter字节数
int PassiveMeasurement_get_counter_width();