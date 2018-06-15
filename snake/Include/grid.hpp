#pragma once
#include <map>
#include <cmath>
#include "flattenvector.hpp"
#include "point.hpp"

namespace Model
{

enum class PointType{ EMPTY, SNAKE };

class IGrid
{
public:
    virtual ~IGrid(){}

    virtual void setPointType(const Point& p, PointType type) = 0;

    virtual PointType getPointType(const Point& p) const = 0;

    virtual size_t rows() const = 0;
    virtual size_t cols() const = 0;

    virtual void reset() = 0;
};

class Grid : public IGrid
{
public:
    Grid(size_t size);

    Grid(size_t cols, size_t rows);

    void setPointType(const Point& p, PointType type) override;

    PointType getPointType(const Point& p) const override;

    size_t rows() const override { return m_rows; }
    size_t cols() const override { return m_cols; }

    void reset() override;

private:
    const size_t m_cols;
    const size_t m_rows;
    FlattenVector<PointType> m_points;
};

}
