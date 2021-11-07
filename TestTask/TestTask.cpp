#pragma once
#include <iostream>
#include <conio.h>
#include <cmath>
#include "Units.h"
#include "Tests.h"
#include <cstring>
#include <string>




using namespace std;

int main()
{

    setlocale(LC_ALL, "");




    Unit u = Unit(Point(0, 0), Point(-5, 5));
    u.radius = 50;
    Unit u2 = Unit(Point(-8, 3), Point(0, 0));
    vector<Unit> vu ={ u2 };
    u.FindNumberOfUnitsThatThisUnitSees(vu);


    //Создать тестовый объект
    Tests test;
    //Тесты скорости
    test.StartAllSpeedTests();
    //Тесты сохранения и загрузки
    test.StartAllSaveAndLoadTests();

    _getch();
    return 0;
}
