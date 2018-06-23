#pragma once
#include <cstddef>

class GameContants
{
public:
    static size_t& ROWS()
    {
        static size_t rows = 12;
        return rows;
    }

    static size_t& COLS()
    {
        static size_t cols = 16;
        return cols;
    }

    static size_t& FIELD_SIZE()
    {
        static size_t fieldSize = 50;
        return fieldSize;
    }

    static unsigned& TIMEOUT()
    {
        static unsigned timeout = 500;
        return timeout;
    }

    static bool& DRAW_GRID()
    {
        static bool drawGrid = false;
        return drawGrid;
    }

};
