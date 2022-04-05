#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "gamepiece.h"
#include <memory>
#include <vector>

//棋盘类,因为用了指针，所以要进行资源管理
class GameBoard
{
public:
    explicit GameBoard(size_t width=kDefaultWidth,size_t height=kDefaultWidth);

    //复制构造,重写是因为GamePiece的复制操作
    GameBoard(const GameBoard& src);
    //复制赋值
    GameBoard& operator=(const GameBoard& src);

    //移动构造,vector会自动管理
    GameBoard(GameBoard&& src)=default;
    //移动赋值
    GameBoard& operator=(GameBoard&& src)=default;
    //析构函数，为什么要写成virtual？
    virtual ~GameBoard()=default;

    //at返回指定位置棋子的引用，而不是返回棋子的副本，GameBoard用作一个二维数组的抽象，所以他应该给出实际对象的索引，而不是给出对象的副本，以提供数组访问语义
    std::unique_ptr<GamePiece>& at(size_t x,size_t y);
    //const对象只能访问const成员函数,而非const对象可以访问任意的成员函数,包括const成员函数.
    //const对象的成员是不可修改的,然而const对象通过指针维护的对象却是可以修改的.
    //const成员函数不可以修改对象的数据,不管对象是否具有const性质.它在编译时,以是否修改成员数据为依据,进行检查.
    //然而加上mutable修饰符的数据成员,对于任何情况下通过任何手段都可修改,自然此时的const成员函数是可以修改它的

    //前一个const表示函数返回值（即指针）的内容不能被修改，该返回值只能被赋给加const修饰的同类型指针。
    //如果函数的返回值类型不是指针，那么由于函数会把返回值复制到外部临时的存储单元中，加const修饰没有任何价值。
    //后一个const表示把整个函数修饰为const，意思是“函数体内不能对成员数据做任何改动”
    const std::unique_ptr<GamePiece>& at(size_t x,size_t y) const;

    size_t getHeight() const{return mHeight;}
    size_t getWidth() const{return mWidth;}

    static const size_t kDefaultWidth=10;
    static const size_t kDefaultHeight=10;

    //noexcept表示函数不会产生异常，产生异常的话会用terminate函数终止程序的运行
    friend void swap(GameBoard& first,GameBoard& second) noexcept;

private:
    //检查输入值的范围
    void vertifyCoordinate(size_t x,size_t y)const;
    //棋子,相当于一个二位数组，数组中的类型是一个指针
    std::vector<std::vector<std::unique_ptr<GamePiece>>> mCells;
    size_t mWidth,mHeight;
};

#endif // GAMEBOARD_H
