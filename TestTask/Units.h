#pragma once
#include "Unit.h"

using namespace std;

/// <summary>
/// Класс, который хранит список юнитов.
/// Имеет методы сохранения и загрузки списка юнитов из файлов.
/// </summary>
class Units
{
public:
    Units(int countOfUnits = 10)
    {
        this->units = vector<Unit>(countOfUnits);
    }

public:
    /// <summary>
    /// Список юнитов.
    /// </summary>
    vector<Unit> units;

public:
    /// <summary>
    /// Уcтановить всем юнитам случайные параметры местонахождения и направления.
    /// </summary>
    /// <param name="min">Нижняя граница для случайно задаваемых значений.</param>
    /// <param name="max">Верхняя граница для случайно задаваемых значений.</param>
    /// <returns></returns>
    void SetRandomParametrsForAllUnits(double min, double max)
    {
        int countOfUnits = this->units.size();
        for (auto it = this->units.begin(); it < this->units.end(); ++it)
        {
            (*it).CalculateRandomLocation(min, max);
            (*it).CalculateRandomDirectionOfSight(min, max);
        }
    }
    /// <summary>
    /// Узнать кого видит каждый из юнитов в списке.
    /// </summary>
    void CalculateVisionForAllUnits()
    {
        vector<Unit>* units = &this->units;

        int countOfUnits = (*units).size();
        for (auto it = (*units).begin(); it != (*units).end(); ++it)
        {
            (*it).CalculateUnitsVisibilityForThisUnit((*units));
        }
    }
};

