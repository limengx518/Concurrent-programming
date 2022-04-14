#include <iostream>
#include <memory>
#include <mutex>
#include <exception> //标准库中的所有异常都继承自std::exception
#include <thread>
#include <stack>

struct empty_stack:std::exception{
	//noexcept=throw()表示该函数不会抛出任何异常
	//如果一个函数带有noexcept标记却以某种方式抛出了异常，c++将调用terminate来终止应用程序
	const char* what() const throw(){
		return "empty stack!";
	};
};

template<typename T>
class threadsafe_stack{
private:
	std::stack<T> data;
	//mutable可变类型操作说明符、
	//utable member of a const object isn't const
	//Mutable is used to specify that the member does not affect the externally visible state of the class
	//The "M&M rule": mutable and mutex go together
	mutable std::mutex m;
public:
	threadsafe_stack():data(std::stack<T>()){}

	threadsafe_stack(const threadsafe_stack& other){
		//other.m???
		std::lock_guard<std::mutex> lock(other.m);
		data=other.data;
	}

	threadsafe_stack& operator=(const threadsafe_stack)=delete;

	void push(T new_value){
		std::lock_guard<std::mutex> lock(m);
		data.push(new_value);
	}

	std::shared_ptr<T> pop(){
		std::lock_guard<std::mutex> lock(m);
		if(data.empty())
			throw empty_stack();

		//在修改堆栈之前，分配出返回值,res算是资源的一种
		std::shared_ptr<T> const res(std::make_shared<T>(data.top()));
		data.pop();
		return res;
	}

	void pop(T& value){
		std::lock_guard<std::mutex> lock(m);
		if(data.empty())
			throw empty_stack();

		value=data.top();
		data.pop();
	}
	bool empty() const{
		std::lock_guard<std::mutex> lock(m);
		return data.empty();
	}
};

void f(threadsafe_stack<int> &s){
	if(!s.empty()){
		int value;
		s.pop(value);
		std::cout<<"the value is"<<value<<std::endl;
	}
	
}
int main(){
	threadsafe_stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	
	std::thread thread(f,std::ref(s));

	if(!s.empty()){
		int value;
		s.pop(value);
		std::cout<<"value="<<value<<std::endl;
	}

	thread.join();
}
