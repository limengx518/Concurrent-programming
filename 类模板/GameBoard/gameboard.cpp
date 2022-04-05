#include "gameboard.h"
#include <stdexcept>

GameBoard::GameBoard(size_t width, size_t height):
    mWidth(width),mHeight(height)
{
    mCells.resize(width);
    for (auto& column:mCells){
        column.resize(height);
    }
}

GameBoard::GameBoard(const GameBoard &src):
    GameBoard(src.mWidth,src.mHeight)
{
    for(size_t i=0;i<mWidth;i++){
        for(size_t j=0;j<mHeight;j++){
            if(src.mCells[i][j]){
                mCells[i][j]=src.mCells[i][j]->clone();
            }
        }
    }

}

//()中的代表右值
GameBoard &GameBoard::operator=(const GameBoard &src)
{
    //代表取地址的操作
    if(this== &src){
        return *this;
    }

    //copy-and-swap idiom
    GameBoard temp(src);
    std::swap(*this,temp);
    return *this;

}

std::unique_ptr<GamePiece> &GameBoard::at(size_t x, size_t y)
{
    return const_cast<std::unique_ptr<GamePiece>&>(std::as_const(*this).at(x,y));
}

const std::unique_ptr<GamePiece> &GameBoard::at(size_t x, size_t y) const
{
    vertifyCoordinate(x,y);
    return mCells[x][y];

}

void GameBoard::vertifyCoordinate(size_t x, size_t y) const
{
    if(x>=mWidth||y>=mHeight){
        throw std::out_of_range("");
    }

}
void swap(GameBoard& first,GameBoard& second) noexcept{
    std::swap(first.mWidth,second.mWidth);
    std::swap(first.mHeight,second.mHeight);
    std::swap(first.mCells,second.mCells);
}
