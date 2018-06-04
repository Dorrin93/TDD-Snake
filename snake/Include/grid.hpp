#pragma once
#include <map>
#include <cmath>
#include "flattenvector.hpp"

namespace Model
{

enum class PointType{ EMPTY, SNAKE };

class IGrid
{
public:
    virtual ~IGrid(){}

    virtual void setPointType(size_t x, size_t y, PointType type) = 0;

    virtual PointType getPointType(size_t x, size_t y) const = 0;

    virtual size_t rows() const = 0;
    virtual size_t cols() const = 0;
};

class Grid : public IGrid
{
public:
    Grid(size_t size);

    Grid(size_t rows, size_t cols);

    void setPointType(size_t x, size_t y, PointType type) override;

    PointType getPointType(size_t x, size_t y) const override;

    size_t rows() const override { return m_rows; }
    size_t cols() const override { return m_cols; }

private:
    const size_t m_rows;
    const size_t m_cols;
    FlattenVector<PointType> m_points;
};

}
