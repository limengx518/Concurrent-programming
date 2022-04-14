#include <thread>
#include <mutex>
#include <iostream>

class Y{
private:
	int some_detail;
	//mutable可变类型操作说明符
	//utable member of a const object isn't const
	//Mutable is used to specify that the member does not affect the externally visible state of the class
	//The "M&M rule": mutable and mutex go together
	mutable std::mutex m;

	int get_detail()const{
		std::lock_guard<std::mutex> lock_a(m);
		return som_detail;
	}

public:
	Y(int sd):some_detail(sd){}

	friend bool operator==(Y const& lhs,Y const& rhs){
		if(&lhs==&rhs)
			return true;
		int const lhs_value=lhs.get_detail();
		int const rhs_value=rhs.get_detail();
		return lhs_value==rhs_value;
	}

};
