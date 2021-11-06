#pragma once
#include "Unit.h"
#include <fstream>
#include <cstring>

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


#pragma region ���������� � ��������

    void Load(string name)
    {
        ifstream in = ifstream(name);
        this->units.clear();
        string stroka;
        string token;
        while (!in.eof())
        {
            getline(in, stroka);
            if (stroka == "")
                break;
            /* "Unit number " << i << ": " +"location: " + to_string(this->location.x) + ";" + to_string(this->location.y) + "; "
            + "directionOfSight: " + to_string(this->directionOfSight.x) + ";" + to_string(this->directionOfSight.y) + "; "
            + "numbersUnitsInDirectionOfSight: ";*/
            
            stroka = stroka.erase(0, stroka.find("n: ") + 3);
            token = stroka.substr(0, stroka.find(";"));
            Unit unit;
            unit.location.x = std::stod(token);

            stroka = stroka.erase(0, stroka.find(";") + 1);
            token = stroka.substr(0, stroka.find(";"));
            unit.location.y = std::stod(token);

            stroka = stroka.erase(0, stroka.find(": ") + 2);
            token = stroka.substr(0, stroka.find(";"));
            unit.directionOfSight.x = std::stod(token);

            stroka = stroka.erase(0, stroka.find(";") + 1);
            token = stroka.substr(0, stroka.find(";"));
            unit.directionOfSight.y = std::stod(token);

            stroka = stroka.erase(0, stroka.find(": ") + 2);
            while (stroka != "")
            {
                token = stroka.substr(0, stroka.find(";"));
                unit.numbersUnitsInDirectionOfSight.push_back(std::atoi(token.c_str()));
                stroka = stroka.erase(0, stroka.find(";") + 1);
            }
            this->units.push_back(unit);
        }

        in.close();
    }

    void Save(string name)
    {
        ofstream out = ofstream(name);

        int size = this->units.size();
        for (int i = 0; i < size; ++i)
        {
            out << "Unit number " << i << ": " << this->units[i].ToString()<<endl;
        }

        out.close();
    }

#pragma endregion
};

