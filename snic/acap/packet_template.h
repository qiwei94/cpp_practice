
/*
explain:增加一个packet template
parameter:int id:在硬件表项中的位置，char* packet_data：存放模板位置的指针，int size模板大小（单位Byte）
return:1:成功 0：失败 
*/
int insert_packet_template(int id, char* packet_data, int size) ;

/*
explain:删除一个packet template
parameter:int id:硬件中的位置
return:1:成功 0：失败 
*/
int delete_packet_template(int id) ;

/*
explain:获取能插入的包模板的最大数量
parameter:
return:返回可以插入的最大数量
*/
int get_packet_template_table_size() ;

/*
explain:初始化一个包模板
parameter:
return:1:成功 0：失败 
*/
int init_packet_template() ;