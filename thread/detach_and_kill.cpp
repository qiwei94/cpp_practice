#include <iostream>			//std：：cout	
#include <thread>			//std::thread， std::this_thread::sleep_for()
#include <chrono>			//std::chrono::seconds
#include <unistd.h>
#include <map>
#include <set>

std::map<int,pthread_t> task_map;
std::thread threads[3];

void measure(int n){
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout<<"id="<<std::this_thread::get_id()<<std::endl;
	std::cout<<"work for "<<n<<"seconds\n";
}

void create_and_work(){
  std::cout << "Spawning and detaching 3 threads...\n";
  threads[0]=std::thread(measure,10);
  threads[1]=std::thread(measure,20);
  threads[2]=std::thread(measure,30);

  threads[0].detach();
  threads[1].detach();
  threads[2].detach();
}
/*
void show_thread(const std::string &keyword)
{
    std::string cmd("ps -T | grep ");
    cmd += keyword;
    system(cmd.c_str());
}
*/
int main() 
{
 
  std::cout << "Spawning and detaching 3 threads...\n";
  std::thread t1(measure,10);
  std::thread t2(measure,20);
  std::thread t3(measure,30);
  task_map[0]=t1.native_handle();
  std::cout<<"0:"<<task_map[0]<<std::endl;
  task_map[1]=t2.native_handle();
  std::cout<<"1:"<<task_map[1]<<std::endl;
  task_map[2]=t3.native_handle();
  std::cout<<"2:"<<task_map[2]<<std::endl;
  t1.detach();
  t2.detach();
  t3.detach();

  sleep(3);

  for(int i=0;i<3;i++){
  	std::cout<<"i="<<i<<std::endl;
  	std::map<int,pthread_t>::iterator key=task_map.find(i);
  	if(key!=task_map.end()){
  		std::cout<<i<<":"<<task_map[i]<<std::endl;
  		pthread_cancel(task_map[i]);
  		task_map.erase(i);
  		std::cout << "Thread " << i << " killed:" << std::endl;
  	}
  }
  return 0;
}
