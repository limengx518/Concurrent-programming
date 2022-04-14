//切勿将受保护数据的指针或引用传递到互斥锁作用域之外，无论是函数返回值，还是存储在外部可见内存
//亦或是以参数的形式传递到用户提供的函数中去
#include <mutex>
#include <iostream>

class some_data{
private:
	int a;
	std::string b;
public:
	void do_some_thing(){
		std::cout<<"do some thing"<<std::endl;
	}
};

class data_wrapper{
private:
	some_data data;
	std::mutex m;
public:
	template<typename Function>
		void process_data(Function func){
			std::lock_guard<std::mutex> l(m);
			func(data);//传递“保护”数据给用户函数
		}
};

some_data* unprotected;
void malicious_function(some_data& protected_data){
	unprotected=&protected_data;
}


int main(){
	data_wrapper x;
	x.process_data(malicious_function);//传递一个“恶意”函数
	unprotected->do_some_thing();//在无保护的情况下访问保护数据
}
