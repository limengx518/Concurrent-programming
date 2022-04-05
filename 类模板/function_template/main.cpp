#include <iostream>
#include "grid.h"

int main()
{
    Grid<int> myIntGrid;
    Grid<double> myDoubleGrid;
    myIntGrid=myDoubleGrid;
    Grid<double> newDoubleGrid(myIntGrid);

    return 0;
}
