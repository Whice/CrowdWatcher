#pragma once
#include "Unit.h"
#include <fstream>
#include <cstring>
#include <thread>

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

        auto end = (*units).end();
        for (auto it = (*units).begin(); it != end; ++it)
        {
            (*it).CalculateUnitsVisibilityForThisUnit((*units));
        }
    }
    /// <summary>
    /// Узнать кого видит каждый из юнитов в списке.
    /// </summary>
    void CalculateVisionForAllUnitsParallel()
    {
        const uint16_t processorCount = std::thread::hardware_concurrency();

        vector<thread> treads(processorCount);

        vector<Unit>* units = &this->units;

        for (int i = 0; i < processorCount; ++i)
        {
            treads[i] = thread([i, processorCount, units]() { Units::PerfromCircleCalculateVisionForAllUnitsParallel(i, processorCount, units); });
        }
        for (int i = 0; i < processorCount; ++i)
        {
            treads[i].join();
        }
    }
public:
    static void PerfromCircleCalculateVisionForAllUnitsParallel(int partNumber, const uint16_t processorCount, vector<Unit>*units)
    {
        int countOfUnits = (*units).size();

        int startNumber = partNumber * countOfUnits / processorCount;
        int endNumer = (partNumber +1)* countOfUnits / processorCount;

        auto start = (*units).begin() + startNumber;
        auto end = (*units).begin()+endNumer;
        for (auto it = start; it != end; ++it)
        {
            (*it).CalculateUnitsVisibilityForThisUnit((*units));
        }
    }

#pragma region Сохранение и загрузка

public:
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

