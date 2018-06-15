#pragma once
#include "gmock/gmock.h"
#include "grid.hpp"

namespace Model
{

class GridMock: public IGrid
{
public:
    MOCK_METHOD2(setPointType, void(const Point&, PointType));
    MOCK_CONST_METHOD1(getPointType, PointType(const Point&));
    MOCK_CONST_METHOD0(rows, size_t());
    MOCK_CONST_METHOD0(cols, size_t());
    MOCK_METHOD0(reset, void());
};

}
