#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <memory>
#include "game.hpp"
#include "gridmock.hpp"
#include "snakemock.hpp"
#include "pointgeneratormock.hpp"

using namespace testing;
using namespace Model;

class GameTest: public Test
{
public:
    GameTest()
    {
        EXPECT_CALL(m_gridMock, rows()).WillRepeatedly(Return(ROWS));
        EXPECT_CALL(m_gridMock, cols()).WillRepeatedly(Return(COLS));

        m_objectUnderTest = std::make_unique<Game>(m_gridMock, m_snakeMock,
                                                   m_generatorMock);
    }

    void setDefaultExpectationsForInit()
    {
        EXPECT_CALL(m_snakeMock, head()).WillRepeatedly(ReturnRef(INITIAL_HEAD));
        EXPECT_CALL(m_gridMock, setPointType(INITIAL_HEAD, PointType::SNAKE));
        EXPECT_CALL(m_generatorMock, getRandomPoint()).WillRepeatedly(Return(BORDER_DOWN_LEFT));
    }

    void setDefaultExpectationsForNextStep()
    {
        EXPECT_CALL(m_snakeMock, setDirection(Direction::RIGHT));
        EXPECT_CALL(m_snakeMock, head()).WillRepeatedly(ReturnRef(INITIAL_HEAD));
        EXPECT_CALL(m_snakeMock, tail()).WillRepeatedly(ReturnRef(INITIAL_HEAD));
        EXPECT_CALL(m_snakeMock, move(BORDER_DOWN_LEFT)).
                WillRepeatedly(ReturnRef(HEAD_AFTER_MOVE));
        EXPECT_CALL(m_gridMock, setPointType(INITIAL_HEAD, PointType::EMPTY)).
                Times(AtLeast(0));
        EXPECT_CALL(m_gridMock, setPointType(HEAD_AFTER_MOVE, PointType::SNAKE)).
                Times(AtLeast(0));
    }

protected:
    const int COLS = 8;
    const int ROWS = 6;
    Point INITIAL_HEAD{ COLS/2, ROWS/2 };
    Point HEAD_AFTER_MOVE { COLS/2+1, ROWS/2 };
    Point BORDER_DOWN_LEFT{ 0, ROWS-1 };
    Point BORDER_UP_RIGHT{ COLS-1, 0 };

    NiceMock<GridMock> m_gridMock;
    StrictMock<SnakeMock> m_snakeMock;
    StrictMock<PointGeneratorMock> m_generatorMock;

    std::unique_ptr<Game> m_objectUnderTest;
};


TEST_F(GameTest, shouldPutSnakeInTheMiddleWhenInitialized)
{
    setDefaultExpectationsForInit();
    m_objectUnderTest->init();
}

TEST_F(GameTest, shouldSimplyMoveSnakeRightWhenNextStepCalled)
{
    setDefaultExpectationsForInit();
    m_objectUnderTest->init();

    setDefaultExpectationsForNextStep();
    m_objectUnderTest->nextStep();

    ASSERT_EQ(m_objectUnderTest->getHeadNowPlacement(), HEAD_AFTER_MOVE);
    ASSERT_EQ(m_objectUnderTest->getTailBeforePlacement(), INITIAL_HEAD);
}

TEST_F(GameTest, shouldReturnFalseWhenSnakeHitWallRight)
{
    // Custom expectations for init, head right next to wall
    EXPECT_CALL(m_generatorMock, getRandomPoint()).WillRepeatedly(Return(BORDER_DOWN_LEFT));
    EXPECT_CALL(m_snakeMock, head()).WillOnce(ReturnRef(BORDER_UP_RIGHT));
    EXPECT_CALL(m_gridMock, setPointType(BORDER_UP_RIGHT, PointType::SNAKE));
    m_objectUnderTest->init();

    Point headNow = BORDER_UP_RIGHT;
    ++headNow.x;
    setDefaultExpectationsForNextStep();
    //Head "inside" wall
    EXPECT_CALL(m_snakeMock, move(BORDER_DOWN_LEFT)).WillOnce(ReturnRef(headNow));

    ASSERT_FALSE(m_objectUnderTest->nextStep());
}

TEST_F(GameTest, shouldEnlargeWhenBonusEaten)
{
    setDefaultExpectationsForInit();
    EXPECT_CALL(m_generatorMock, getRandomPoint()).WillOnce(Return(HEAD_AFTER_MOVE));

    m_objectUnderTest->init();

    setDefaultExpectationsForNextStep();
    EXPECT_CALL(m_snakeMock, tail()).WillOnce(ReturnRef(INITIAL_HEAD));
    EXPECT_CALL(m_snakeMock, move(m_objectUnderTest->getBonusPlacement())).
            WillOnce(ReturnRef(HEAD_AFTER_MOVE));
    EXPECT_CALL(m_gridMock, setPointType(HEAD_AFTER_MOVE, PointType::SNAKE));
    EXPECT_CALL(m_generatorMock, getRandomPoint()).WillOnce(Return(BORDER_DOWN_LEFT));

    ASSERT_TRUE(m_objectUnderTest->nextStep());
}

TEST_F(GameTest, shouldReturnFalseWhenSnakeHitItself)
{
    setDefaultExpectationsForInit();
    m_objectUnderTest->init();

    setDefaultExpectationsForNextStep();
    EXPECT_CALL(m_gridMock, getPointType(HEAD_AFTER_MOVE)).WillOnce(Return(PointType::SNAKE));

    ASSERT_FALSE(m_objectUnderTest->nextStep());
}
