#include "grid.hpp"
#include <iostream>

namespace Model
{

Grid::Grid(size_t size):
    m_cols(size), m_rows(size),
    m_points(m_cols, m_rows, PointType::EMPTY)
{}

Grid::Grid(size_t cols, size_t rows):
    m_cols(cols), m_rows(rows),
    m_points(m_cols, m_rows, PointType::EMPTY)
{}

void Grid::setPointType(const Point &p, PointType type)
{
    m_points.get(p.x, p.y) = type;
}

PointType Grid::getPointType(const Point &p) const
{
    return m_points.get(p.x, p.y);
}

void Grid::reset()
{
    m_points.fill(PointType::EMPTY);
}

}
