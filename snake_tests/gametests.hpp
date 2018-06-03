#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <memory>
#include "game.hpp"
#include "gridmock.hpp"

using namespace testing;
using namespace Model;

class GameTest: public Test
{
public:
    GameTest()
    {
        EXPECT_CALL(m_gridMock, rows()).WillRepeatedly(Return(ROWS));
        EXPECT_CALL(m_gridMock, cols()).WillRepeatedly(Return(COLS));

        m_objectUnderTest = std::make_unique<Game>(m_gridMock);
    }

    void setCommonExpectationsForInit()
    {
        EXPECT_CALL(m_gridMock, setPointType(ROWS/2, COLS/2, PointType::SNAKE));
    }

protected:
    const size_t ROWS = 6;
    const size_t COLS = 8;

    NiceMock<GridMock> m_gridMock;

    std::unique_ptr<Game> m_objectUnderTest;
};


TEST_F(GameTest, shouldPutSnakeInTheMiddleWhenInitialized)
{
    setCommonExpectationsForInit();
    EXPECT_CALL(m_gridMock, setPointType(Ne(ROWS/2), Ne(COLS/2), PointType::BONUS));

    m_objectUnderTest->init();
}

TEST_F(GameTest, shouldPutBonusNotInTheMiddleWhenInitialized)
{
    setCommonExpectationsForInit();
    m_objectUnderTest->init();


}
