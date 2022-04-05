#include <iostream>
#include <thread>
#include <unistd.h>

void do_something(int& i){
	std::cout<<i<<"do something"<<std::endl;
}

struct func{
	//i表示变量的地址
	int& i;
public:
	//构造函数
	func(int& i_):i(i_){}
	void operator()(){
		//确保当函数结束时，线程还没有退出
		for(unsigned j=0;j<1000000;++j){
			do_something(i);
		}
	}

};

void oops(){
	int some_local_state=0;
	func my_func(some_local_state);
	std::thread my_thread(my_func);
	sleep(20000);
	//if(my_thread.joinable()){
		//std::cout<<"可以加入"<<std::endl;
	//}else{
		//std::cout<<"不可以加入"<<std::endl;
	//}
	my_thread.detach();//不等待线程结束

}
int main(){
	//在这个例子中，线程启动了，但是很快就停止了，应该是opps()函数运行的时间有点短
	oops();
}
