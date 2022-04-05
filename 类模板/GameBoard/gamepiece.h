#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include <memory>

//代表棋子这个基类
class GamePiece
{
public:
    GamePiece();
    //棋子的复制操作
    virtual std::unique_ptr<GamePiece> clone() const=0;
};

#endif // GAMEPIECE_H
