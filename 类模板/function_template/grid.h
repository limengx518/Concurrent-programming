#ifndef GRID_H
#define GRID_H

#include <memory>
#include <stdexcept>
#include <optional>
#include <vector>

//Grid<int> myIntGrid
//Grid<double> myDoubleGrid
//myIntGrid=myDOubleGrid; Grid<double> newDoubleGrid(myIntGrid)
//方法模板
template <typename T>
class Grid
{
public:
    Grid(size_t width=mDefaultWidth,size_t height=mDefaultHeight);
    ~Grid()=default;

    //复制构造、复制赋值
    template<typename E>
    Grid(const Grid<E>& src);
    template<typename E>
    Grid& operator=(const Grid<E>& src);

    //移动构造、移动赋值
//    template<typename E>
//    Grid(Grid<E>&& src);
//    template<typename E>
//    Grid& operator=(Grid<E>&& src);

    std::optional<T>& at(size_t x,size_t y);
    const std::optional<T> & at(size_t x,size_t y) const;

    size_t getWidth() const {return mwidth;}
    size_t getHeight() const{return mheight;}

    const static int mDefaultWidth=15;
    const static int mDefaultHeight=15;
private:
    void vertifyGood(size_t x,size_t y) const;
    size_t mwidth,mheight;
    std::vector<std::vector<std::optional<T>>> mCells;

};

#include "grid.cpp"

#endif // GRID_H
