#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "grid.hpp"
#include "point.hpp"

using namespace testing;
using namespace Model;

class GridTest: public Test
{
public:
    GridTest():
        m_objectUnderTest(ROWS, COLS)
    {}

protected:
    const size_t ROWS = 3;
    const size_t COLS = 2;
    Grid m_objectUnderTest;
};

class GridTestPointParam : public GridTest,
                           public WithParamInterface<Point>
{};

TEST_F(GridTest, shouldCreateGridWith3Rows2Cols)
{
    ASSERT_EQ(ROWS, m_objectUnderTest.rows());
    ASSERT_EQ(COLS, m_objectUnderTest.cols());
}

TEST_P(GridTestPointParam, shouldBeEmptyByDefault)
{
    const auto point = GetParam();
    ASSERT_EQ(PointType::EMPTY, m_objectUnderTest.getPointType(point.x, point.y));
}

INSTANTIATE_TEST_CASE_P(AllPoints,
                        GridTestPointParam,
                        Values(Point{0, 0}, Point{0, 1},
                               Point{1, 0}, Point{1, 1},
                               Point{2, 0}, Point{2, 1}));

TEST_F(GridTest, shouldPutSnake)
{
    m_objectUnderTest.setPointType(1, 0, PointType::SNAKE);

    ASSERT_EQ(PointType::SNAKE, m_objectUnderTest.getPointType(1, 0));
    ASSERT_NE(PointType::SNAKE, m_objectUnderTest.getPointType(0, 1));
}


class GridTestOutOfBoundParam : public GridTest,
                                public WithParamInterface<Point>
{};

TEST_P(GridTestOutOfBoundParam, shouldNotSetPointOutOfBounds)
{
    const auto point = GetParam();
    ASSERT_THROW(m_objectUnderTest.setPointType(point.x, point.y, PointType::SNAKE),
                 std::out_of_range);
}

TEST_P(GridTestOutOfBoundParam, shouldNotGetPointOutOfBounds)
{
    const auto point = GetParam();
    ASSERT_THROW(m_objectUnderTest.getPointType(point.x, point.y),
                 std::out_of_range);
}

INSTANTIATE_TEST_CASE_P(OutOfBoundPoints,
                        GridTestOutOfBoundParam,
                        Values(Point{3, 0}, Point{3, 1},
                               Point{3, 2}, Point{0, 2},
                               Point{1, 2}, Point{2, 2}));
