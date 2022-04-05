#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "gamepiece.h"

class ChessPiece:public GamePiece
{
public:
    ChessPiece();
    virtual std::unique_ptr<GamePiece>clone() override;
};

#endif // CHESSPIECE_H
