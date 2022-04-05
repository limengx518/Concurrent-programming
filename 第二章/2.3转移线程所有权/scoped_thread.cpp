#include <iostream>
#include <thread>

void do_some_work(int i){
	std::cout<<"i="<<i<<std::endl;
}

struct func{
	int& i;
	func(int& i_):i(i_){}
	void operator()(){
		for(unsigned j=0;j<1000000;j++){
			do_some_work(i);
		}
	}
};

class scoped_thread{
public:
	scoped_thread(std::thread t):
		thread(std::move(t))
	{}
	~scoped_thread(){
		if(thread.joinable()){
			thread.join();
		}
	}

	scoped_thread(scoped_thread& src)=delete;
	scoped_thread& operator=(scoped_thread& src)=delete;
private:
	std::thread thread;
};

int main(){
	int some_local_state=1;
	//线程的入口函数
	//func my_func(some_local_state);
	//std::thread myThread(my_func);
	//scoped_thread my_scoped_thread1(std::move(myThread));
	
	//这样会报错说这是函数声明
	scoped_thread my_scoped_thread2{std::thread(func(some_local_state))};

}
