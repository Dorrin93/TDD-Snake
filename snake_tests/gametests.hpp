#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <memory>
#include "game.hpp"
#include "gridmock.hpp"
#include "snakemock.hpp"

using namespace testing;
using namespace Model;

class GameTest: public Test
{
public:
    GameTest()
    {
        EXPECT_CALL(m_gridMock, rows()).WillRepeatedly(Return(ROWS));
        EXPECT_CALL(m_gridMock, cols()).WillRepeatedly(Return(COLS));

        m_objectUnderTest = std::make_unique<Game>(m_gridMock, m_snakeMock);
    }

    void setExpectationsForInit()
    {
        EXPECT_CALL(m_snakeMock, head()).WillRepeatedly(ReturnRef(INITIAL_HEAD));
        EXPECT_CALL(m_gridMock, setPointType(ROWS/2, COLS/2, PointType::SNAKE));
    }

protected:
    const size_t ROWS = 6;
    const size_t COLS = 8;
    Point INITIAL_HEAD{static_cast<int>(ROWS)/2,
                       static_cast<int>(COLS)/2};
    Point BORDER_DOWN_LEFT{static_cast<int>(ROWS)-1, 0};
    Point BORDER_UP_RIGHT{0, static_cast<int>(COLS)-1};

    NiceMock<GridMock> m_gridMock;
    StrictMock<SnakeMock> m_snakeMock;

    std::unique_ptr<Game> m_objectUnderTest;
};


TEST_F(GameTest, shouldPutSnakeInTheMiddleWhenInitialized)
{
    setExpectationsForInit();

    m_objectUnderTest->init();
}

TEST_F(GameTest, shouldPutBonusNotInTheMiddleWhenInitialized)
{
    setExpectationsForInit();

    m_objectUnderTest->init();

    auto bonus = m_objectUnderTest->getBonusPlacement();
    ASSERT_FALSE(static_cast<size_t>(bonus.x) == ROWS/2 and
                 static_cast<size_t>(bonus.y) == COLS/2);
}

TEST_F(GameTest, shouldSimplyMoveSnakeRightWhenNextStepCalled)
{
    setExpectationsForInit();

    m_objectUnderTest->init();
    m_objectUnderTest->setBonusPlacement(BORDER_DOWN_LEFT.x, BORDER_DOWN_LEFT.y);

    Point headNow = INITIAL_HEAD;
    ++headNow.y;

    EXPECT_CALL(m_snakeMock, tail()).WillOnce(ReturnRef(INITIAL_HEAD));
    EXPECT_CALL(m_snakeMock, move(BORDER_DOWN_LEFT)).WillOnce(ReturnRef(headNow));

    EXPECT_CALL(m_gridMock, setPointType(INITIAL_HEAD.x, INITIAL_HEAD.y, PointType::EMPTY));
    EXPECT_CALL(m_gridMock, setPointType(headNow.x, headNow.y, PointType::SNAKE));

    m_objectUnderTest->nextStep();

    ASSERT_EQ(m_objectUnderTest->getHeadNowPlacement(), headNow);
    ASSERT_EQ(m_objectUnderTest->getTailBeforePlacement(), INITIAL_HEAD);
}

TEST_F(GameTest, shouldReturnFalseWhenSnakeHitWallRight)
{
    EXPECT_CALL(m_gridMock, setPointType(BORDER_UP_RIGHT.x, BORDER_UP_RIGHT.y, PointType::SNAKE));
    EXPECT_CALL(m_snakeMock, head()).WillOnce(ReturnRef(BORDER_UP_RIGHT));
    m_objectUnderTest->init();
    m_objectUnderTest->setBonusPlacement(BORDER_DOWN_LEFT.x, BORDER_DOWN_LEFT.y);

    Point headNow = BORDER_UP_RIGHT;
    ++headNow.y;

    EXPECT_CALL(m_snakeMock, tail()).WillOnce(ReturnRef(BORDER_UP_RIGHT));
    EXPECT_CALL(m_snakeMock, move(BORDER_DOWN_LEFT)).WillOnce(ReturnRef(headNow));

    ASSERT_FALSE(m_objectUnderTest->nextStep());
}

TEST_F(GameTest, shouldEnlargeWhenBonusEaten)
{
    setExpectationsForInit();

    m_objectUnderTest->init();
    m_objectUnderTest->setBonusPlacement(INITIAL_HEAD.x+1, INITIAL_HEAD.y);

    Point headNow = INITIAL_HEAD;
    ++headNow.x;
    EXPECT_CALL(m_snakeMock, tail()).WillOnce(ReturnRef(INITIAL_HEAD));
    EXPECT_CALL(m_snakeMock, move(m_objectUnderTest->getBonusPlacement())).
            WillOnce(ReturnRef(headNow));
    EXPECT_CALL(m_gridMock, setPointType(INITIAL_HEAD.x+1, INITIAL_HEAD.y, PointType::SNAKE));

    m_objectUnderTest->nextStep();
}
