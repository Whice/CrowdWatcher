#pragma once
#include "Unit.h"
#include <fstream>
#include <cstring>

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


#pragma region Сохранение и загрузка

    void Load(string name)
    {
        ifstream in = ifstream(name);
        this->units = vector<Unit>();
        string stringLine;
        string token;

        getline(in, stringLine);
        do
        {
            
            /* "Unit number " << i << ": " +"location: " + to_string(this->location.x) + ";" + to_string(this->location.y) + "; "
            + "directionOfSight: " + to_string(this->directionOfSight.x) + ";" + to_string(this->directionOfSight.y) + "; "
            + "numbersUnitsInDirectionOfSight: ";*/
            
            stringLine = stringLine.erase(0, stringLine.find("n: ") + 3);
            token = stringLine.substr(0, stringLine.find(";"));
            Unit unit;
            unit.location.x = std::stod(token);

            stringLine = stringLine.erase(0, stringLine.find(";") + 1);
            token = stringLine.substr(0, stringLine.find(";"));
            unit.location.y = std::stod(token);

            stringLine = stringLine.erase(0, stringLine.find(": ") + 2);
            token = stringLine.substr(0, stringLine.find(";"));
            unit.directionOfSight.x = std::stod(token);

            stringLine = stringLine.erase(0, stringLine.find(";") + 1);
            token = stringLine.substr(0, stringLine.find(";"));
            unit.directionOfSight.y = std::stod(token);

            stringLine = stringLine.erase(0, stringLine.find(": ") + 2);
            while (stringLine != "")
            {
                token = stringLine.substr(0, stringLine.find(";"));
                unit.numbersUnitsInDirectionOfSight.push_back(std::atoi(token.c_str()));
                stringLine = stringLine.erase(0, stringLine.find(";") + 1);
            }
            this->units.push_back(unit);

            getline(in, stringLine);
        } 
        while (stringLine != "");

        in.close();
    }
    /// <summary>
    /// Сохранение в тескстовой файл с нумерацией.
    /// </summary>
    /// <param name="name"></param>
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

