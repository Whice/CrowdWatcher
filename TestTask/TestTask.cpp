#include <iostream>
#include <conio.h>
#include <cmath>

using namespace std;

const double PI = 3.14159265;

struct Point
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

/// <summary>
/// Проверить, находится ли юнит в поле зрения.
/// </summary>
/// <param name="centerOfView">Точка - центр направления взгляда.</param>
/// <param name="positionUnit">Точка - местонахождение юнита.</param>
/// <param name="visionAngle">Угол обзора.</param>
/// <returns></returns>
bool IsUnitInSight(Point& centerOfView, Point& positionUnit, double& visionAngle)
{
    //Если позиция юнита "за спиной" у смотрящего.
    // Позиции не могут быть далеко длпруг от друга из-за ограниченности дальности видимости.
    // Потому можно перемножать и не боться переполнения.
    if ((centerOfView.x * positionUnit.x < 0) &&
        (centerOfView.y * positionUnit.y < 0))
    {
        return false;
    }

    //Найти в радианах половину угла обзора
    double halfOfVisionAngle = (visionAngle * 0.5)*PI/180;
    //найти в радианах соответствующие углы зрению и метоположению
    double angleOfView = atan(centerOfView.y / centerOfView.x);
    double angleOfVectorToUnit = atan(positionUnit.y / positionUnit.x);

    //Если разница между углом зрения и местоположением меньше половины угла обзора, то юнит видно.
    if (abs(angleOfView - angleOfVectorToUnit) < halfOfVisionAngle)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/// <summary>
/// Проверить находится ли юнитв пределах коружности или на ее границе.
/// </summary>
/// <param name="centerOfCircle">Точка центра окружности.</param>
/// <param name="positionUnit">Местонахождение юнита.</param>
/// <param name="radius">Радиус окружности.</param>
/// <returns>true, если в переделах окружности или на ней самой.</returns>
bool IsInsideCircle(Point& centerOfCircle, Point& positionUnit, double radius=2)
{
    double deltaX = positionUnit.x - centerOfCircle.x;
    double deltaY = positionUnit.y - centerOfCircle.y;

    //При хорошем разбросе юнитов эта ситуация будет встречаться чаще всего.
    if (abs(deltaX) > radius || abs(deltaY) > radius)
        return false;

    //Если юнит все-таки где-то рядом, тогда проверить в границе ли он или на ней ли.
    if (deltaX * deltaX + deltaY * deltaY <= radius * radius)
    {
        return true;
    }
    else
    {
        return false;
    }
}
/// <summary>
/// Проверяет находится ли юнит в поле видимости наблюдателя.
/// </summary>
/// <param name="observerLocation">Позиция наблюдателя.</param>
/// <param name="centerOfView">Точка - центр направления взгляда.</param>
/// <param name="positionUnit">Точка - местонахождение юнита.</param>
/// <param name="visionAngle">Угол обзора. Размер сектора в градусах.</param>
/// <param name="radius">Радиус окружности. Дальность видимости.</param>
/// <returns></returns>
bool UnitIsVisible(Point& observerLocation, Point& centerOfView, Point& positionUnit, double visionAngle = 135.5, double radius = 2)
{
    return IsUnitInSight(centerOfView, positionUnit, visionAngle) & IsInsideCircle(observerLocation, positionUnit, radius);
}

int main()
{
    setlocale(LC_ALL, "");

    double visionAngle;

    Point centerOfView;
    Point positionUnit;
    Point observerLocation = Point(0, 0);
    
    while (true)
    {
        cout << "Input visionAngle: ";
        cin >> visionAngle;

        
        cout << "Input centerOfView x: ";
        cin >> centerOfView.x;
        cout << "Input centerOfView y: ";
        cin >> centerOfView.y;
        cout << "Input positionUnit x: ";
        cin >> positionUnit.x;
        cout << "Input positionUnit y: ";
        cin >> positionUnit.y;

        if (UnitIsVisible(observerLocation, centerOfView, positionUnit, visionAngle))
        {
            cout << "Yes";
        }
        else
        {
            cout << "No";
        }
        cout << endl << endl;
    }
    double param = 45.0;                      // угол 45 градусов

    std::cout << "Тангенс угла "
        << param << " градусов = "
        << atan(1) * 180 / PI      // вычисляем тангенс угла, переведённого в радианы
        << std::endl;

    _getch();
    return 0;
}
