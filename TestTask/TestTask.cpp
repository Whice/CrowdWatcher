
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
    double visionAngle = 135.5;


    Tests test;
    test.StartAllSpeedTests();
    test.StartAllSaveAndLoadTests();

    _getch();
    return 0;
}
