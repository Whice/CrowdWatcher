#include <iostream>
#include <conio.h>
#include <cmath>
#include "Units.h"
#include "SpeedTests.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");
    double visionAngle = 135.5;

    Tests test;
    test.StartAllSpeedTests();

    _getch();
    return 0;
}
