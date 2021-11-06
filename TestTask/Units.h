#pragma once
#include "Unit.h"

using namespace std;

/// <summary>
/// �����, ������� ������ ������ ������.
/// ����� ������ ���������� � �������� ������ ������ �� ������.
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
    /// ������ ������.
    /// </summary>
    vector<Unit> units;

public:
    /// <summary>
    /// �c�������� ���� ������ ��������� ��������� ��������������� � �����������.
    /// </summary>
    /// <param name="min">������ ������� ��� �������� ���������� ��������.</param>
    /// <param name="max">������� ������� ��� �������� ���������� ��������.</param>
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
    /// ������ ���� ����� ������ �� ������ � ������.
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

