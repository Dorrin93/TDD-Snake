#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "snake.hpp"

using namespace testing;
using namespace Model;


class SnakeTest: public Test
{
public:
    SnakeTest():
        INITIAL_HEAD{2, 3},
        CORNER_BONUS{0, 0},
        m_objectUnderTest(INITIAL_HEAD)
    {}

protected:
   Point INITIAL_HEAD;
   Point CORNER_BONUS;
   Snake m_objectUnderTest;
};


TEST_F(SnakeTest, shouldPointCorrectHeadWithOnlyOneElement)
{
    ASSERT_EQ(m_objectUnderTest.head(), INITIAL_HEAD);
}

TEST_F(SnakeTest, shouldPointCorrectTailWithOnlyOneElement)
{
    ASSERT_EQ(m_objectUnderTest.tail(), INITIAL_HEAD);
}

TEST_F(SnakeTest, shouldMoveRightByDefault)
{
    Point head = INITIAL_HEAD;
    ++head.x;

    ASSERT_EQ(m_objectUnderTest.move(CORNER_BONUS), head);
    ASSERT_EQ(m_objectUnderTest.size(), 1u);
}

TEST_F(SnakeTest, shouldMoveLeft)
{
    Point head = INITIAL_HEAD;
    --head.x;
    m_objectUnderTest.setDirection(Direction::LEFT);

    ASSERT_EQ(m_objectUnderTest.move(CORNER_BONUS), head);
    ASSERT_EQ(m_objectUnderTest.size(), 1u);
}

TEST_F(SnakeTest, shouldMoveUp)
{
    Point head = INITIAL_HEAD;
    --head.y;
    m_objectUnderTest.setDirection(Direction::UP);

    ASSERT_EQ(m_objectUnderTest.move(CORNER_BONUS), head);
    ASSERT_EQ(m_objectUnderTest.size(), 1u);
}

TEST_F(SnakeTest, shouldMoveDown)
{
    Point head = INITIAL_HEAD;
    ++head.y;
    m_objectUnderTest.setDirection(Direction::DOWN);

    ASSERT_EQ(m_objectUnderTest.move(CORNER_BONUS), head);
    ASSERT_EQ(m_objectUnderTest.size(), 1u);
}

TEST_F(SnakeTest, shouldMoveWithEnlargeRight)
{
    Point tail = INITIAL_HEAD;
    Point head = INITIAL_HEAD;
    ++head.x;

    ASSERT_EQ(m_objectUnderTest.move(head), head);
    ASSERT_EQ(m_objectUnderTest.head(), head);
    ASSERT_EQ(m_objectUnderTest.tail(), tail);
    ASSERT_EQ(m_objectUnderTest.size(), 2u);
}

TEST_F(SnakeTest, shouldMoveWithEnlargeRightThenUp)
{
    Point tail = INITIAL_HEAD;
    ++tail.x;
    Point head = tail;
    --head.y;

    m_objectUnderTest.move(tail);
    m_objectUnderTest.setDirection(Direction::UP);
    m_objectUnderTest.move(CORNER_BONUS);

    ASSERT_EQ(m_objectUnderTest.head(), head);
    ASSERT_EQ(m_objectUnderTest.tail(), tail);
    ASSERT_EQ(m_objectUnderTest.size(), 2u);
}

TEST_F(SnakeTest, shouldNotTurnOpositeWithSizeGreaterThanOne)
{
    Point tail = INITIAL_HEAD;
    ++tail.x;
    Point head = tail;
    ++head.x;

    m_objectUnderTest.move(tail);
    m_objectUnderTest.setDirection(Direction::LEFT);
    m_objectUnderTest.move(CORNER_BONUS);

    ASSERT_NE(m_objectUnderTest.direction(), Direction::LEFT);
    ASSERT_EQ(m_objectUnderTest.head(), head);
    ASSERT_EQ(m_objectUnderTest.tail(), tail);
}
