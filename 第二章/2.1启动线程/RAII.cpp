#include <thread>
#include <iostream>
#include <memory>

void do_something(int i){
	std::cout<<"i="<<i<<std::endl;
}

struct func{
	int& i;
	func(int& i_):i(i_){}
	void operator()(){
		for(unsigned j=0;j<1000000;j++){
			do_something(i);
		}
	}
};

void oops(){
	int some_local_state=1;
	func my_func(some_local_state);
	std::thread thread(my_func);
	thread.detach();
}

class thread_guard{
public:
	thread_guard(std::thread& thread_):
		thread(thread_){}

	~thread_guard(){
		if(thread.joinable()){
			thread.join();
		}
	}

	thread_guard(thread_guard& src)=delete;
	thread_guard& operator=(thread_guard& src)=delete;
	
private:
	std::thread& thread;
};

void f(){
	int some_local_state=1;
	func my_func(some_local_state);
	std::thread myThread(my_func);
	thread_guard my_thread_guard(myThread);
}
int main(){
	//oops();
	f();
}
