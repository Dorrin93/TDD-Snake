#pragma once

namespace Model
{

struct Point
{
    int x;
    int y;
};

inline Point operator+(const Point& lhs, const Point& rhs)
{
    return {lhs.x + rhs.x, lhs.y + rhs.y};
}

inline bool operator==(const Point& lhs, const Point& rhs)
{
    return lhs.x == rhs.x and lhs.y == rhs.y;
}

inline bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs == rhs);
}

}
