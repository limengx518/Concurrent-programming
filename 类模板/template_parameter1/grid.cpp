#include "grid.inl"



template<typename T, size_t WIDTH, size_t HEIGHT>
Grid<T, WIDTH, HEIGHT>::Grid()
{


}

template<typename T, size_t WIDTH, size_t HEIGHT>
std::optional<T> &Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y)
{
    vertifyGoodinate(x,y);
    return mCells[x][y];
}

template<typename T, size_t WIDTH, size_t HEIGHT>
const std::optional<T> &Grid<T, WIDTH, HEIGHT>::at(size_t x, size_t y) const
{
    return const_cast<std::optional<T>&>(std::as_const(*this).at(x,y));
}

template<typename T, size_t WIDTH, size_t HEIGHT>
void Grid<T, WIDTH, HEIGHT>::vertifyGoodinate(size_t x, size_t y) const
{
    if(x>=WIDTH||y>=HEIGHT)
        throw std::out_of_range("");
}
