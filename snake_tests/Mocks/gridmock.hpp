#pragma once
#include "gmock/gmock.h"
#include "grid.hpp"

namespace Model
{

class GridMock: public IGrid
{
public:
    MOCK_METHOD3(setPointType, void(size_t, size_t, PointType));
    MOCK_CONST_METHOD2(getPointType, PointType(size_t, size_t));
    MOCK_CONST_METHOD0(rows, size_t());
    MOCK_CONST_METHOD0(cols, size_t());
};

}
