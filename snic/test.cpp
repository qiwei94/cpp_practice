#include <iostream>
#include <unistd.h>
#include <string>
#include "measurement.h"
using namespace std;

int main(int argc, char const *argv[])
{   
    /*
    cout<<"zhang"<<endl;
    int add_res=add_passive_measure_task(10,1);
    if(add_res==1){
        cout<<"add success"<<endl;
    }
    add_passive_measure_task(100, 2);

    for(int i=0;i<10;i++){
        count_res_t task_res = get_passive_task_result(10);
        count_res_t task_res_2 = get_passive_task_result(100);
        cout<<"task result="<<task_res.result<<" res2="<<task_res_2.result<<endl;
        sleep(1);
    }

    int shutdown_res = shutdow_task(10);
    if (shutdown_res == 1)
    {
        cout<<"shutdown task 1 success"<<endl;
    }
    else if (shutdown_res == 0)
    {
        cout << "shutdown task 1 fail" << endl;
    }
    */
    
    char packet[7]="123456";
    int add_packet_res = add_packet_templete(1,packet,6);
    if(add_packet_res)
        cout<<"add pack tem success"<<endl;
    

    int add_task_res = add_active_task(1,
                                       0,
                                       1,
                                       1,
                                       1,
                                       1,
                                       1,
                                       10,
                                       'a');
    
    cout<<"add task res = "<<add_task_res<<endl;

    if(add_task_res==1){
        cout<<"add task success"<<endl;
    }
    //sleep(5);
    for(int i=0;i<10;i++){
        active_measurement_result_t* res=query_active_task_result(1);
        if(res)
            cout << "the res is " << res->rtt<<endl;
        sleep(1);
    }
    
   //sleep(5);
    int del_task_res = delete_active_task(1);

    if(del_task_res==1){
        cout<<"del task success"<<endl;;
    }

    int del_pac_res = delete_packet_templete(1);
    if (del_pac_res==1)
        cout << "delete packet success" << endl;
    
    return 0;
}

/*
  g++ test.cpp passive_measure.cpp active_measure.cpp  acap/packet_template.cpp acap/active_measurement.cpp  -lpthread -std=c++11 -o ctest.o
*/
