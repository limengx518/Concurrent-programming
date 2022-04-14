#include <mutex>
#include <iostream>
#include <climits>
#include <thread>

class hierarchical_mutex{
	std::mutex internal_mutex;

	//层次锁的值
	unsigned long const hierarchy_value;
	unsigned long previous_hierarchy_value;

	//当前线程的层级值，他被初始化为最大值，所以最初所有的线程都可以被锁住
	static thread_local unsigned long this_thread_hierarchy_value;

	void check_for_hierarchy_volation(){
		if(this_thread_hierarchy_value<=hierarchy_value){
			throw std::logic_error("mutex hierarchy violated");
		}
	}

	void update_hierarchy_value(){
		previous_hierarchy_value=this_thread_hierarchy_value;
		this_thread_hierarchy_value=hierarchy_value;
	}

public:
	explicit hierarchical_mutex(unsigned long value):
		hierarchy_value(value),
		previous_hierarchy_value(0){}

	void lock(){
		check_for_hierarchy_volation();
		internal_mutex.lock();
		update_hierarchy_value();
	}

	void unlock(){
        this_thread_hierarchy_value=previous_hierarchy_value;
		internal_mutex.unlock();
	}

	bool try_lock(){
        check_for_hierarchy_volation();
		if(!internal_mutex.try_lock())
			return false;
		update_hierarchy_value();
		return true;
	}

};

hierarchical_mutex high_level_mutex(10000);
hierarchical_mutex low_level_mutex(5000);

int do_low_level_staff(){
	std::cout<<"do low level staff"<<std::endl;
	return 1;
}

int low_level_func(){
    std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
	return do_low_level_staff();
}

void high_level_stuff(int some_parm){
	std::cout<<"do high level staff"<<std::endl;
	std::cout<<"some_parm"<<some_parm<<std::endl;
}

void high_level_func(){
	std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
	high_level_stuff(low_level_func());
}

void thread_a(){
	high_level_func();
}

hierarchical_mutex other_mutex(100);
void do_other_stuff(){
    std::cout<<"do other stuff"<<std::endl;
}
void other_stuff(){
    high_level_func();
    do_other_stuff();
}

void thread_b(){
    std::lock_guard<hierarchical_mutex> lk(other_mutex);
    other_stuff();
}

thread_local unsigned long hierarchical_mutex::this_thread_hierarchy_value(ULONG_MAX);

int main(){
    std::thread a(thread_a);
    //std::thread b(thread_b);
    
    a.join();
    //b.join();
}
