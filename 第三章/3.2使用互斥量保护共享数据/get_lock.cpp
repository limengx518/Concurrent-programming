#include <iostream>
#include <thread>
#include <mutex>

std::mutex some_mutex;

void prepare_data(){
	std::cout<<"prepare data"<<std::endl;
}

std::unique_lock<std::mutex> get_lock(){
	extern std::mutex some_mutex;
	std::unique_lock<std::mutex> lk(some_mutex);
	prepare_data();
	return lk;
}

void do_something(){
	std::cout<<"do some thing"<<std::endl;
}

//std::unique_lock 实例没有与自身相关的互斥量，一个互斥量的所有权可以通过移动操作
//在不同的实例中进行传递,std::unique_lock可以移动但不可赋值
void process_data(){
	std::unique_lock<std::mutex> lk(get_lock());
	do_something();
}

int main(){
	std::thread thread_a(process_data);
	thread_a.join();
	return 0;
}
