#include "chesspiece.h"

ChessPiece::ChessPiece()
{

}

std::unique_ptr<GamePiece> ChessPiece::clone()
{
    return std::make_unique<ChessPiece>(*this);
}
