#include <thread>
#include <iostream>

class Scoped_thread{
public:
	explicit Scoped_thread(std::thread t_):t(std::move(t_)){
		//在构造函数中直接检查是否可以加入
		if(!t.joinable()){
			throw std::logic_error("No Thread");
		}
	}
	~Scoped_thread(){
		t.join();
	}
	Scoped_thread(Scoped_thread const&)=delete;
	Scoped_thread& operator=(Scoped_thread const&)=delete;

private:
	std::thread t;
};

void do_some_work(int& i){
	std::cout<<"do some work"<<i<<std::endl;
}

struct func{
	int& i;
	func(int& i_):i(i_){
	}
	void operator()(){
		do_some_work(i);
	}
};

int main(){
	int local_state;
	try{
		Scoped_thread t((std::thread(func(local_state))));
	}catch (std::exception& e){
		std::cout<<e.what()<<std::endl;
	}
}
