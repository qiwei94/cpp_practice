#include <iostream>			//std：：cout	
#include <thread>			//std::thread， std::this_thread::sleep_for()
#include <chrono>			//std::chrono::seconds

std::thread::id main_thread_id=std::this_thread::get_id();

void pause_thread(int n){
	std::this_thread::sleep_for(std::chrono::seconds(n));
	std::cout<<"pause of "<<n<<" seconds ended\n";
}

void is_main_thread(){
	if(main_thread_id==std::this_thread::get_id())
		std::cout<<"yes\n";
	else
		std::cout<<"no\n";
}
void mythread(){

}



int main(){
	//std::cout<<"spawning 3 threads...."<<std::endl;
	//std::thread t1(pause_thread,1);
	//std::thread t2(pause_thread,2);
	//std::thread t3(pause_thread,3);
	//std::cout<<"ing "<<std::endl;
	//jion的作用就是等某个线程执行结束
	//t1.join();
	//t2.join();
	//t3.join();
	//std::cout<<"all thread joined"<<std::endl;

	/**********************************************/
	//is_main_thread();
	//std::thread th(is_main_thread);
	//is_main_thread();
	//th.join();
	/**********************************************/
	//std::cout<<"spawning and detaching 3 threads..\n";
	////detach 就是让线程脱离调用的主程序，使得他们可以各自执行
	////一旦detach，那么线程将不以任何形式blocking或者同步，当某个线程结束时
	////他们的资源就会被释放
	////当调用这个函数时，这个线程的object就会变成non-joinable,并且可以安全得销毁
	//std::thread(pause_thread,1).detach();
	//std::thread(pause_thread,2).detach();
	//std::thread(pause_thread,3).detach();
	//std::cout << "Done spawning threads.\n";
	//std::cout << "(the main thread will now pause for 5 seconds)\n";
	//pause_thread(5);
	/**********************************************/
	//std::thread foo;
	//std::thread bar(mythread);
	//std::cout<<"join able??\n";
//
	//std::cout<<"foo: " << foo.joinable() << '\n';
	//std::cout << "bar: " << bar.joinable() << '\n';
//
	//if(foo.joinable()) foo.join();
	//if(bar.joinable()) bar.join();
//
	//std::cout << "Joinable after joining:\n" << std::boolalpha;
  	//std::cout << "foo: " << foo.joinable() << '\n';
  	//std::cout << "bar: " << bar.joinable() << '\n';
	//return 0;

	std::thread threads[5];
	std::cout<<"spawning 5 threads...\n";
	for(int i=0;i<5;i++){
		threads[i]=std::thread(pause_thread,i+1);
	}

	std::cout<< "Done spawning threads. Now waiting for them to join:\n";
	for(int i=0;i<5;i++)
		threads[i].join();
	
	std::cout<<"all threads joined\n";
	
	return 0;
}