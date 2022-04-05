#include <iostream>
#include "gameboard.h"
#include <memory>
#include "chesspiece.h"

int main()
{
    GameBoard chessBoard(15,15);
    auto pawn=std::make_unique<ChessPiece>();
//    std::cout<<chessBoard.getHeight()<<std::endl;
//    std::cout<<chessBoard.getWidth()<<std::endl;
    chessBoard.at(0,0)=std::move(pawn);
    chessBoard.at(0,1)=std::make_unique<ChessPiece>();
    chessBoard.at(0,1)=nullptr;
}
