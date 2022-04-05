#include "grid.h"
#include <stdexcept>

template<typename T>
Grid<T>::Grid(size_t width, size_t height):
    mWidth(width),mHeight(height)
{
    mCells.resize(mWidth);
    for(auto& column:mCells){
        column.resize(mHeight);
    }
}

template<typename T>
std::optional<T> &Grid<T>::at(size_t x, size_t y)
{
    return const_cast<std::optional<T>&>(std::as_const(*this).at(x,y));
}

template<typename T>
const std::optional<T> &Grid<T>::at(size_t x, size_t y) const
{
    vertifyCoordinate(x,y);
    return mCells[x][y];
}

template<typename T>
void Grid<T>::vertifyCoordinate(size_t x, size_t y) const
{
    if(x>=mWidth||y>mHeight){
        throw std::out_of_range("");
    }

}
