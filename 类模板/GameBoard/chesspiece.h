#ifndef CHESSPIECE_H
#define CHESSPIECE_H
#include "gamepiece.h"
#include <memory>

//象棋棋子
class ChessPiece:public GamePiece
{
public:
    ChessPiece();
    //重写复制操作
    virtual std::unique_ptr<GamePiece> clone() const override;
};

#endif // CHESSPIECE_H
