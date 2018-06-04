#pragma once
#include <cstddef>

namespace GameContants
{

constexpr size_t ROWS = 10;
constexpr size_t COLS = 15;
constexpr size_t FIELD_SIZE = 40;

constexpr size_t FULL_ROW_SIZE = ROWS*FIELD_SIZE;
constexpr size_t FULL_COLS_SIZE = COLS*FIELD_SIZE;

constexpr unsigned TIMEOUT = 300;

constexpr bool DRAW_GRID = false;

}
