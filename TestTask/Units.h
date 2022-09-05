#pragma once
#include "Unit.h"
#include <fstream>
#include <cstring>
#include <thread>
#include <map>
#include <set>

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
        this->countOfUnits = countOfUnits;
        PlaceUnitsOnMap();
    }

public:
    /// <summary>
    /// Список юнитов.
    /// </summary>
    vector<Unit> units;
/// <summary>
/// Получить всех юнитов с карты с ячейками.
/// </summary>
/// <returns></returns>
public: vector<Unit> GetUnitsFromMap()
{
    vector<Unit> allUnits;
    for (auto cell : this->cellsWithUnits)
    {
        for (auto unit : cell.second)
        {
            allUnits.push_back(unit);
        }
    }
    return allUnits;
}
/// <summary>
/// Количество всех юнитов.
/// </summary>
private: int countOfUnits;
/// <summary>
/// Размер ячейки на карте для определения области, в которой может быть юнит.
/// Размер ячейки должен быть больше дальности обзора, т.к. иначе деления на ячейки не имеет смысла.
/// </summary>
private: static const int MAP_CELL_SIZE = Unit::SIGHT_DISTANCE*2;
/// <summary>
/// Карта содержащая ячейки, в которых храняться юниты.
/// Юниты распределены по ячейкам в зависимости от своего местоположения.
/// </summary>
private: map<Point, vector<Unit>> cellsWithUnits;

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
        auto end = this->units.end();
        for (auto it = this->units.begin(); it < end ; ++it)
        {
            (*it).CalculateRandomLocation(min, max);
            (*it).CalculateRandomDirectionOfSight(min, max);
        }
    }
/// <summary>
/// Получить ячейку, в которой находиться юнит.
/// </summary>
/// <param name="unitPosition"></param>
/// <returns></returns>
private: inline Point GetCellForUnit(const Point &unitPosition)
{
    return Point(//double туда запишутся после деления двух целых.
        (int)unitPosition.x / this->MAP_CELL_SIZE,
        (int)unitPosition.y / this->MAP_CELL_SIZE
    );
}
/// <summary>
/// Получить всех юнитов из этой ячйки и ее соседей.
/// Предполагается, что дальность видимости юнита меньше, чем размер ячейки.
/// </summary>
/// <param name="cellPosition"></param>
/// <returns></returns>
private: void GetUnitsForCellAndHerNeighbors(const Point &cellPosition, vector<Unit> &neighborsForCell)
{
    Point keyCells[] =//получить позиции всех соседних ячеек и самой указанной ячейки.
    {
        Point(cellPosition.x, cellPosition.y),
        Point(cellPosition.x + 1, cellPosition.y),
        Point(cellPosition.x - 1, cellPosition.y),

        Point(cellPosition.x, cellPosition.y - 1),
        Point(cellPosition.x + 1, cellPosition.y - 1),
        Point(cellPosition.x - 1, cellPosition.y - 1),

        Point(cellPosition.x, cellPosition.y + 1),
        Point(cellPosition.x + 1, cellPosition.y + 1),
        Point(cellPosition.x - 1, cellPosition.y + 1),
    };

    set<Unit*> neighborsForCellSet;
    neighborsForCell = vector<Unit>();
    vector<Unit> *unitsInCell;
    Point key;
    for (int i = 0; i < 9; i++)
    {
        key = keyCells[i];
        unitsInCell = &this->cellsWithUnits[key];
        auto end = (*unitsInCell).end();
        for (auto it = (*unitsInCell).begin(); it != end; ++it)
        {
            if (neighborsForCellSet.count(&( * it)) == 0)
            {
                neighborsForCellSet.insert(&(*it));
                neighborsForCell.push_back(*it);
            }
        }
    }
}
    /// <summary>
    /// Разместить юнитов на карте.
    /// Размещение равномерное, для тестов.
    /// </summary>
private: void PlaceUnitsOnMap()
    {
        const int countOfUnits = this->countOfUnits;
        int unitsCountHave = 0;
        const int mapCellSize = this->MAP_CELL_SIZE;
        //расстояние размещения друг от друга
        int distanceBeetwenUnits = 1;
        //Определить стартовую точку заполнения при единичном расстоянии между юнитами
        int step = 0;//Это шаг в сторону от любой из осей.
        while ((2 * step + 1) * (2 * step + 1) < countOfUnits)
            ++step;
        //Точка начала по х 
        const int xStart = step * distanceBeetwenUnits;
        //Точка начала по у
        const int yStart = step * distanceBeetwenUnits;
        //Точка конца по х 
        const int xEnd = -step * distanceBeetwenUnits;
        //Точка конца по у
        const int yEnd = -step * distanceBeetwenUnits;

        for (int x = xStart; x >= xEnd; x -= distanceBeetwenUnits)
            for (int y = yStart; y >= yEnd; y -= distanceBeetwenUnits)
            {
                Point position = Point(x, y);
                Unit u = Unit();
                u.location = position;
                /*раздать как будто случайные направления взглядов.
                Так они не будут смотреть в одну сторону, но всегда одинково.*/
                u.directionOfSight = Point
                (
                    (int)position.x % 2 == 0 ? position.x - 1 : position.x - 1,
                    (int)position.y % 2 == 0 ? position.y - 1 : position.y - 1
                );
                Point cellPosition = GetCellForUnit(position);
                if (this->cellsWithUnits.count(cellPosition)==0)
                {
                    this->cellsWithUnits[cellPosition] = vector<Unit>();
                }
                this->cellsWithUnits[cellPosition].push_back(u);
                this->units.push_back(u);

                ++unitsCountHave;
                if (unitsCountHave >= countOfUnits)
                    return;
            }
    }
public:
    /// <summary>
    /// Узнать кого видит каждый из юнитов в списке.
    /// </summary>
    void CalculateVisionForAllUnits()
    {
        vector<Unit>* units = &this->units;

        auto end = (*units).end();
        for (auto it = (*units).begin(); it != end; ++it)
        {
            (*it).FindCountOfUnitsThatThisUnitSees((*units));
        }
    }
    /// <summary>
    /// Узнать кого видит каждый из юнитов в списке с 
    /// использованием ячеек карты.
    /// </summary>
    void CalculateVisionForAllUnitsWithMapCells()
    {
        vector<Unit>* units = &this->units;
        vector<Unit> neighbors;

        auto end = (*units).end();
        for (auto it = (*units).begin(); it != end; ++it)
        {
            Point p = GetCellForUnit((*it).location);
            GetUnitsForCellAndHerNeighbors(p, neighbors);
            (*it).FindCountOfUnitsThatThisUnitSees(neighbors);
        }
    }
    /// <summary>
    /// Узнать кого видит каждый из юнитов в списке. Многопоточное выполнение.
    /// </summary>
    void CalculateVisionForAllUnitsParallel()
    {
        const uint16_t processorCount = std::thread::hardware_concurrency();

        vector<thread> treads(processorCount);

        vector<Unit>* units = &this->units;

        for (int i = 0; i < processorCount; ++i)
        {
            treads[i] = thread([i, processorCount, units]() 
                {
                    Units::PerfromCircleCalculateVisionForAllUnitsParallel(i, processorCount, units);
                });
        }
        for (int i = 0; i < processorCount; ++i)
        {
            treads[i].join();
        }
    }
public:
    /// <summary>
    /// Выполнение цикла проверки видимости других юнитов в одном потоке. 
    /// </summary>
    /// <param name="threadNumber">Номер потока выполнения.</param>
    /// <param name="processorCount">Общее количество потоков, на которых идет выполнение.</param>
    /// <param name="units">Список юнитов.</param>
    static void PerfromCircleCalculateVisionForAllUnitsParallel(int threadNumber, const uint16_t processorCount, vector<Unit>*units)
    {
        int countOfUnits = (*units).size();

        int startNumber = threadNumber * countOfUnits / processorCount;
        int endNumer = (threadNumber +1)* countOfUnits / processorCount;

        auto start = (*units).begin() + startNumber;
        auto end = (*units).begin()+endNumer;
        for (auto it = start; it != end; ++it)
        {
            (*it).FindCountOfUnitsThatThisUnitSees((*units));
        }
    }

#pragma region Сохранение и загрузка

public:
    /// <summary>
    /// Загрузка из текстового файла.
    /// </summary>
    /// <param name="name"></param>
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

