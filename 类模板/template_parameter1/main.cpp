#include <iostream>
#include "grid.inl"

int main()
{
    Grid<int,10,10> myGrid;
    Grid<int,10,10> myOtherGrid;
    myGrid.at(2,3)=42;
    myOtherGrid=myGrid;
    std::cout<<myOtherGrid.at(2,3).value_or(0)<<std::endl;
    return 0;
}
