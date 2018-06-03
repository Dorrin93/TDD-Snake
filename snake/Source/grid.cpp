#include "grid.hpp"
#include <iostream>

namespace Model
{

Grid::Grid(unsigned size):
    m_rows(size), m_cols(size),
    m_points(m_rows, m_cols, PointType::EMPTY)
{}

Grid::Grid(unsigned rows, unsigned cols):
    m_rows(rows), m_cols(cols),
    m_points(m_rows, m_cols, PointType::EMPTY)
{}

void Grid::setPointType(size_t x, size_t y, PointType type)
{
    m_points.get(x, y) = type;
}

PointType Grid::getPointType(size_t x, size_t y) const
{
    return m_points.get(x, y);
}

}
