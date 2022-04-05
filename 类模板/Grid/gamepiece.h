#ifndef GAMEPIECE_H
#define GAMEPIECE_H

#include <memory>

//棋子类的基类
class GamePiece
{
public:
    GamePiece();
    virtual std::unique_ptr<GamePiece> clone()=0;
};

#endif // GAMEPIECE_H
