#include <iostream>
#include "grid.h"

using namespace std;
int main()
{
    Grid<int> myIntGrid(11,12);
    Grid<double> myDoubleGrid(11,12);

    myIntGrid.at(0,0)=10;
//    myIntGrid.at(1,1)=20;
    try {
        //如果有值，返回该值，否则返回0
        int x=myIntGrid.at(0,0).value_or(0);
        //??为什么打印不出来值啊？？
        cout<<"x="<<x<<endl;
    }  catch (...) {
        cout<<"hello"<<endl;
    }

    Grid<int> grid2(myIntGrid);
    Grid<int> anotherGrid;
    anotherGrid=grid2;
}
