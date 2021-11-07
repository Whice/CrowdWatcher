#pragma once

/// <summary>
///  ласс двумерной точки.
/// —дела специально дл¤ этой задачи.
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
};

