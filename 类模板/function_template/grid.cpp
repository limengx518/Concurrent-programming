#include "grid.h"


template<typename T>
Grid<T>::Grid(size_t width, size_t height)
{
    mCells.resize(width);
    for(auto& column:mCells){
        column.resize(height);
    }
}



template<typename T>
std::optional<T> &Grid<T>::at(size_t x, size_t y)
{
    vertifyGood(x,y);
    return mCells[x][y];
}

template<typename T>
const std::optional<T> &Grid<T>::at(size_t x, size_t y) const
{
    return const_cast<std::optional<T>&>(std::as_const((*this).at(x,y)));

}

template<typename T>
void Grid<T>::vertifyGood(size_t x, size_t y) const
{
    if(x>=mwidth || y>=mheight)
        throw std::out_of_range("");

}


//必须通过公共的访问方法getWidth(),getHeight(),at()来访问src中分元素，因为这两者不是同一种类型
template<typename T>
template<typename E>
Grid<T>::Grid(const Grid<E> &src):
    Grid(src.getWidth(),src.getHeight())
{
    for(size_t i=0;i<src.getWidth();i++){
        for(size_t j=0;j<src.getHeight();j++){
            mCells[i][j]=src.at(i,j);
        }
    }
}

template <typename T>
template <typename E>
Grid<T> &Grid<T>::operator=(const Grid<E> &src)
{
    for(size_t i=0;i<src.getWidth();i++){
        for(size_t j=0;j<src.getHeight();j++){
            mCells[i][j]=src.at(i,j);
        }
    }
}
