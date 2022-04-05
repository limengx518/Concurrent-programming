#ifndef GRID_H
#define GRID_H

#include <memory>
#include <vector>
#include <optional>

//模板类
template <typename T>
class Grid
{
public:
    explicit Grid(size_t width=kDefaultWidth,size_t height=kDefaultHeight);
    virtual ~Grid()=default;

    //默认的复制构造、复制赋值、移动构造、移动赋值函数
    Grid(const Grid<T>&)=default;
    Grid<T>& operator=(const Grid<T>&)=default;

    Grid(Grid<T>&&)=default;
    Grid<T>& operator=(Grid<T>&&)=default;

    std::optional<T>& at(size_t x,size_t y);
    const std::optional<T>& at(size_t x,size_t y) const;

    size_t getWidth(){return mWidth;}
    size_t getHeight(){return mHeight;}

    static const size_t kDefaultWidth=10;
    static const size_t kDefaultHeight=10;
private:
    void vertifyCoordinate(size_t x,size_t y) const;
    //std::optional表示可以有某个类型的值，也可以没有任何值
    std::vector<std::vector<std::optional<T>>> mCells;
    size_t mWidth;
    size_t mHeight;
};

#include "grid.cpp"

#endif // GRID_H
