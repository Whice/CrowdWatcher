#include <iostream>
#include <conio.h>
#include <cmath>
#include "Units.h"

using namespace std;

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}


int main()
{
    setlocale(LC_ALL, "");
    double visionAngle = 135.5;

    Units manyUnits = Units(9'999);
    manyUnits.SetRandomParametrsForAllUnits(-100, 100);
    vector<Unit>* units = &manyUnits.units;

    int countOfUnits = (*units).size();
    for (int i = 0; i < countOfUnits; ++i)
    {
        (*units)[i].CalculateUnitsVisibilityForThisUnit((*units), i);
    }


    _getch();
    return 0;
}
