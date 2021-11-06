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

int main()
{
    setlocale(LC_ALL, "");

    double visionAngle;

    Point centerOfView;
    Point positionUnit;

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

        if (IsUnitInSight(centerOfView, positionUnit, visionAngle))
            cout << "Yes";
        else
            cout << "No";
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
