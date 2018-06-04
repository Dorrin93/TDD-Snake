#pragma once
#include "gmock/gmock.h"
#include "pointgenerator.hpp"

namespace Model
{

class PointGeneratorMock: public IPointGenrator
{
public:
    MOCK_METHOD0(getRandomPoint, Point());
};

}
