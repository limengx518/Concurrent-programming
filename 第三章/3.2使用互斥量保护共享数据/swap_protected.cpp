#include <iostream>
#include <thread>
#include <mutex>

class some_big_object{
private:
	int *a;
public:
	some_big_object(int* b):a(b){}
};

void swap(some_big_object& lhs,some_big_object& rhs){
//	some_big_object
}

class X{
private:
	some_big_object some_detail;
	std::mutex m;
public:
	X(some_big_object const & sd):some_detail(sd){}

	friend void swap(X& lhs,X& rhs){
		if(&lhs==rhs)
			return;
		//将两个互斥量锁住
		std::lock(lhs.m,rhs.m);
		//提供std::adopt_lock 参数除了表示std::lock_guard可获取锁对象外，还将锁交由std::lock_guard对象管理，而不需要
		//std::lock_guard对象再去构建新的锁
		std::lock_guard<std::mutex> lock_a(lhs.m,std::adopt_lock);
		std::lock_guard<std::mutex> lock_b(rhs.m,std::adopt_lock);

		swap(lhs.some_detail,rhs.some_detail);
	}
}

int main(){

}
