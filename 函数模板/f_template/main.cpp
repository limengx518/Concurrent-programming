#include <iostream>



template <typename T>
size_t Find(const T& value,const T* arr,size_t size){
    for(size_t i=0;i<size;i++){
        if(arr[i]==value){
            return i;
        }
    }
    return -1;
}

int main()
{
    int myInt=3,intArray[]={1,2,3,4};
    const size_t setInArray=std::size(intArray);
    std::cout<<Find(myInt,intArray,setInArray)<<std::endl;

    return 0;
}
