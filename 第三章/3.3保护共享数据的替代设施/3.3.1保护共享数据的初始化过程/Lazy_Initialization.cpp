#include <mutex>
#include <thread>
#include <iostream>
#include <string>
#include <fstream>

class LogFile{
private:
	std::mutex _mu;
	//std::mutex _mu_open;
	std::ofstream _f;

	std::once_flag _mu_once;
public:
	LogFile(){
		//在初始化时将资源文件打开
		//_f.open("log.txt");
	}

	void shared_print(std::string s,int value){

		//双重检查锁模式，这个会影响线程之间的同步
		/*{
			std::unique_lock<mutex> lock2(_mu_open);
			//Lazy Initialization
			if(!_f.is_open()){
				//std::unique_lock<mutex> locker2(_mu_open);
				_f.open("log.txt");
			}//Initialization Upon First Use Idiom
		}*/

		std::call_once(_mu_once,[&](){_f.open("log.txt");});

		
		std::unique_lock<std::mutex> locker(_mu,std::defer_lock);
		_f<<"From"<<s<<":"<<value<<std::endl;
	}
};

int main(){
	LogFile logFile;
	std::thread thread_a(&LogFile::shared_print,&logFile,"string",1);
	thread_a.join();
}
