#include <iostream>
#include <conio.h>
#include <cmath>

using namespace std;

const double PI = 3.14159265;

struct Point
{
    double x;
    double y;
};

/// <summary>
/// Проверить, находится ли юнит в поле зрения.
/// </summary>
/// <param name="centerOfView"></param>
/// <param name="positionUnit"></param>
bool IsUnitInSight(Point& centerOfView, Point& positionUnit, double& visionAngle)
{
    double halfOfVisionAngle = visionAngle * 0.5;
    double angleOfView = atan(centerOfView.y / centerOfView.x);
    double angleOfVectorToUnit = atan(positionUnit.y / positionUnit.x);

    if (abs(angleOfView - angleOfVectorToUnit) < halfOfVisionAngle)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    setlocale(LC_ALL, "");
    double param = 45.0;                      // угол 45 градусов

    std::cout << "Тангенс угла "
        << param << " градусов = "
        << atan(1) * 180 / PI      // вычисляем тангенс угла, переведённого в радианы
        << std::endl;

    _getch();
    return 0;
}
