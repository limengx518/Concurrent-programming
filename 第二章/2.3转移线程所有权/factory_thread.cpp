#include <iostream>
#include <thread>
#include <functional>
#include <vector>

void do_work(unsigned id){
	std::cout<<"do work"<<id<<std::endl;
}

void f(){
	std::vector<std::thread> threads;
	for(unsigned i=0;i<20;++i){
		threads.push_back(std::thread(do_work,i));
	}
	//std::mem_fn
	//Returns a function object whose functional call invokes the member function pointed by pm.
	std::for_each(threads.begin(),threads.end(),
			std::mem_fn(&std::thread::join));
}

int main(){
	f();
}
