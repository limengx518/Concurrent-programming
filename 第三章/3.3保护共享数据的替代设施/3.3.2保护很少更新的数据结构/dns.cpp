#include <mutex>
#include <string>
#include <thread>
#include <map>
#include <iostream>
#include <boost/thread/shared_mutex.hpp>

class DnsEntry{
	int DNS;
public:
	DnsEntry(){
		std::cout<<"DnsEntry"<<std::endl;
	}
	DnsEntry(int x):DNS(x){}
	int getData(){
		return DNS;
	}
};

class DnsCache{
private:
	std::map<std::string,DnsEntry> entries;
	mutable boost::shared_mutex entry_mutex;
public:
	DnsCache(std::map<std::string,DnsEntry> entries){
		this->entries=entries;
	}

	DnsEntry find_entry(std::string const& domain) const{
			//使用boost::shared_lock来保护共享和只读权限
			//使得多线程同时调用find_entry而不会出错
		    boost::shared_lock<boost::shared_mutex> lk(entry_mutex);
			//std::lock_guard<boost::shared_mutex> lk(entry_mutex);
			std::map<std::string,DnsEntry>::const_iterator const it=entries.find(domain);
			return (it==entries.end())?DnsEntry():it->second;
	}

	void update_or_add_entry(std::string const& domain,DnsEntry const& dns_details){
		std::lock_guard<boost::shared_mutex> lk(entry_mutex);
		entries[domain]=dns_details;
	}

};

int main(){
	std::map<std::string,DnsEntry> maps={{"one",DnsEntry(1)},{"two",DnsEntry(2)},};
	DnsCache dnsCache(maps);
	std::thread thread_a(&DnsCache::find_entry,&dnsCache,std::string("one"));
	std::thread thread_b(&DnsCache::find_entry,&dnsCache,std::string("one"));

	thread_a.join();
	thread_b.join();
}
