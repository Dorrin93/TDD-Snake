#include "pointgenerator.hpp"

namespace Model
{

PointGenerator::PointGenerator(size_t maxX, size_t maxY):
    m_xGenerator(0, maxX), m_yGenerator(0, maxY)
{}

Point PointGenerator::getRandomPoint()
{
    return {static_cast<int>(m_xGenerator(getGenerator())),
            static_cast<int>(m_yGenerator(getGenerator()))};
}

std::mt19937 &PointGenerator::getGenerator()
{
    const static auto seed =
            std::chrono::system_clock::now().time_since_epoch().count();
    static std::mt19937 generator(seed);

    return generator;
}

}

