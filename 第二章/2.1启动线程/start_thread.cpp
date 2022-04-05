#include <thread>
#include <iostream>


void do_something(){
	std::cout<<"do some thing"<<std::endl;
}

void do_something_else(){
	std::cout<<"do something else"<<std::endl;
}

class background_task{
	public:
		void operator()() const{
			do_something();
			do_something_else();
		}
};

int main(){
	background_task b;
	//std::thread myThread1(b);
	//std::thread myThread2((background_task()));
	std::thread myThread3{background_task()};

	//myThread1.join();
	//myThread2.join();
	myThread3.join();
}
