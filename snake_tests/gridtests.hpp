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
        m_objectUnderTest(COLS, ROWS)
    {}

protected:
    const size_t ROWS = 3;
    const size_t COLS = 2;
    Grid m_objectUnderTest;
};

class GridTestPointParam : public GridTest,
                           public WithParamInterface<Point>
{};

TEST_F(GridTest, shouldCreateGridWith2ColsAnd3Rows)
{
    ASSERT_EQ(ROWS, m_objectUnderTest.rows());
    ASSERT_EQ(COLS, m_objectUnderTest.cols());
}

TEST_P(GridTestPointParam, shouldBeEmptyByDefault)
{
    const auto point = GetParam();
    ASSERT_EQ(PointType::EMPTY, m_objectUnderTest.getPointType(point));
}

INSTANTIATE_TEST_CASE_P(AllPoints,
                        GridTestPointParam,
                        Values(Point{0, 0}, Point{1, 0},
                               Point{0, 1}, Point{1, 1},
                               Point{0, 2}, Point{1, 2}));

TEST_F(GridTest, shouldPutSnake)
{
    m_objectUnderTest.setPointType(Point{1, 0}, PointType::SNAKE);

    ASSERT_EQ(PointType::SNAKE, m_objectUnderTest.getPointType(Point{1, 0}));
    ASSERT_NE(PointType::SNAKE, m_objectUnderTest.getPointType(Point{0, 1}));
}


class GridTestOutOfBoundParam : public GridTest,
                                public WithParamInterface<Point>
{};

TEST_P(GridTestOutOfBoundParam, shouldNotSetPointOutOfBounds)
{
    const auto point = GetParam();
    ASSERT_THROW(m_objectUnderTest.setPointType(point, PointType::SNAKE),
                 std::out_of_range);
}

TEST_P(GridTestOutOfBoundParam, shouldNotGetPointOutOfBounds)
{
    const auto point = GetParam();
    ASSERT_THROW(m_objectUnderTest.getPointType(point),
                 std::out_of_range);
}

INSTANTIATE_TEST_CASE_P(OutOfBoundPoints,
                        GridTestOutOfBoundParam,
                        Values(Point{2, 0}, Point{0, 3},
                               Point{2, 1}, Point{1, 3},
                               Point{2, 3}, Point{2, 3}));

TEST_F(GridTest, shouldSetPointsToEmptyWhenReset)
{
    const Point point1{1, 0};
    const Point point2{0, 2};
    m_objectUnderTest.setPointType(point1, PointType::SNAKE);
    m_objectUnderTest.setPointType(point2, PointType::SNAKE);

    m_objectUnderTest.reset();
    ASSERT_EQ(m_objectUnderTest.getPointType(point1), PointType::EMPTY);
    ASSERT_EQ(m_objectUnderTest.getPointType(point2), PointType::EMPTY);
}
