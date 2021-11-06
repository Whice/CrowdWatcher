#include <iostream>
#include <conio.h>
#include <cmath>
#include "Unit.h"

using namespace std;





int main()
{
    setlocale(LC_ALL, "");
    double visionAngle = 135.5;


    /*
    Юнит1, позиция (1,1), направление (0,1)
    Юнит2, позиция (1,2), направление (1,0)
    Юнит3, позиция (-5,-1), направление (0.707, 0.707)*/
    vector<Unit> units(3);
    units[0] = Unit(Point(1, 1), Point(0, 1));
    units[1] = Unit(Point(1, 2), Point(1,0));
    units[2] = Unit(Point(-5, -1), Point(0.707, 0.707));


    Point directionOfSight;
    Point positionUnit;
    Point observerLocation = Point(0, 0);
    
    Unit testUnit = Unit();

    while (true)
    {
        cout << "Input visionAngle: ";
        cin >> visionAngle;
        visionAngle = visionAngle * PI / 180;
        
        cout << "Input centerOfView x: ";
        cin >> testUnit.directionOfSight.x;
        cout << "Input centerOfView y: ";
        cin >> testUnit.directionOfSight.y;
        cout << "Input positionUnit x: ";
        cin >> positionUnit.x;
        cout << "Input positionUnit y: ";
        cin >> positionUnit.y;

        if (testUnit.UnitIsVisible(positionUnit, visionAngle))
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
