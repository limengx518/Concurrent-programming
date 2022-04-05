#include <iostream>
#include <thread> //存储管理线程的类和函数

void hello(){
	std::cout<<"Hello,concurrent world!"<<std::endl;
}

int main(){
	std::thread t(hello);//hello是新线程的初始函数
	t.join();
}
