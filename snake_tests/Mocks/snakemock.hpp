#pragma once
#include "gmock/gmock.h"
#include "snake.hpp"

namespace Model
{

class SnakeMock: public ISnake
{
public:
    MOCK_METHOD1(move, Point&(const Point&));
    MOCK_CONST_METHOD0(head, Point&());
    MOCK_CONST_METHOD0(tail, Point&());
    MOCK_CONST_METHOD0(direction, Direction());
    MOCK_METHOD1(setDirection, void(Direction));
    MOCK_CONST_METHOD0(size, size_t());
    MOCK_METHOD1(reset, void(const Point&));
};

}
