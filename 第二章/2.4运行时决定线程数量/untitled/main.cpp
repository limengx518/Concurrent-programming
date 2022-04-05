#include <iostream>
#include <thread>
#include <numeric>
#include <vector>
#include <functional>

//类模板
template<typename Iterator,typename T>
struct accumulate_block{
    //计算一个片段的和
    void operator()(Iterator first,Iterator last,T& result){
        result=std::accumulate(first,last,result);
    }
};

//函数模板
template<typename Iterator,typename T>
T parallel_accumulate(Iterator first,Iterator last,T init)
{


    unsigned long const length=std::distance(first,last);
    //如果输入的范围为空，返回init的值
    if(!length)
        return init;

    //最小任务数
    unsigned long const min_per_thread=25;
    //启动线程的最大数量
    unsigned long const max_threads=(length+min_per_thread-1)/min_per_thread;
    unsigned long const hardware_threads=std::thread::hardware_concurrency();
    unsigned long const num_threads=std::min(hardware_threads!=0?hardware_threads:2,max_threads);

    unsigned long const block_size=length/num_threads;
    std::vector<T> results(num_threads);
    std::vector<std::thread> threads(num_threads-1);
    Iterator block_start=first;
    for(unsigned long i=0;i<(num_threads-1);i++){
        Iterator block_end=block_start;
        std::advance(block_end,block_size);
        threads[i]=std::thread(accumulate_block<Iterator,T>(),
                block_start,block_end,std::ref(results[i]));
        block_start=block_end;
    }

    //剩下的
    accumulate_block<Iterator,T>()(block_start,last,std::ref(results[num_threads-1]));

    std::for_each(threads.begin(),threads.end(),std::mem_fn(&std::thread::join));

    return std::accumulate(results.begin(),results.end(),init);

};

int main(){
    std::vector<int> myVector={1,2,3,4,5,6,7,8,9,10};

    int result=parallel_accumulate(myVector.begin(),myVector.end(),0);
    std::cout<<"result="<<result<<std::endl;
}
