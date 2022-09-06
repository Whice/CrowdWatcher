#pragma once

/// <summary>
/// Класс двумерной точки.
/// Сделан специально для этой задачи.
/// </summary>
class Point
{
public: Point()
{
    this->x = 0;
    this->y = 0;
}
public: Point(double x, double y)
{
    this->x = x;
    this->y = y;
}
      double x;
      double y;

public:
    inline
        bool operator<(const Point& other) const
    {
        if (this->x == other.x)
        {
            return this->y < other.y;
        }
        else
        {
            return this->x < other.x;
        }
    }
    inline
        bool operator>(const Point& other) const
    {
        if (this->x == other.x)
        {
            return this->y > other.y;
        }
        else
        {
            return this->x > other.x;
        }
    }
    inline
        bool operator==(const Point& other) const
    {
        return this->x == other.x && this->y == other.y;
    }
    inline
        bool operator!=(const Point& other) const
    {
        return this->x != other.x || this->y != other.y;
    }
};