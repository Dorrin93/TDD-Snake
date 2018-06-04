#pragma once
#include <cstddef>
#include <random>
#include <chrono>
#include "point.hpp"

namespace Model
{

class IPointGenrator
{
public:
    virtual ~IPointGenrator(){}
    virtual Point getRandomPoint() = 0;
};

class PointGenerator: public IPointGenrator
{
public:
    PointGenerator(size_t maxX, size_t maxY);
    Point getRandomPoint() override;

private:
    static std::mt19937& getGenerator();

    std::uniform_int_distribution<size_t> m_xGenerator;
    std::uniform_int_distribution<size_t> m_yGenerator;
};

}
