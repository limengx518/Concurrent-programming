#ifndef GRID_H
#define GRID_H

#include <memory.h>
#include <optional>
#include <stdexcept>

//非类型的模板参数
//编译器为模板化的方法生成代码的方式是在编译之前替换模板参数，
//在编译代码之前就知道这些参数的值了，所以可以用c语言风格的数组来写

template <typename T,size_t WIDTH,size_t HEIGHT>
class Grid
{
public:
    Grid();

    //析构函数
    ~Grid()=default;
    //复制构造、复制赋值
    Grid(const Grid& src)=default;
    Grid& operator=(const Grid& src)=default;

    //c语言风格的数组不支持移动语义
    //移动构造、移动赋值
//    Grid(Grid&& src);
//    Grid& operator=(Grid&& src);

    std::optional<T>& at(size_t x,size_t y);
    const std::optional<T>& at(size_t x,size_t y) const;

    size_t getHeight(){return HEIGHT;}
    size_t getWidth(){return WIDTH;}

private:
    void vertifyGoodinate(size_t x,size_t y) const;

    std::optional<T> mCells[WIDTH][HEIGHT];
};
#include "grid.cpp"
#endif // GRID_H

