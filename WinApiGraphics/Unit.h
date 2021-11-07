﻿#pragma once
#include "Point.h"
#include <vector>
#include <cstring>
#include <string>

const double PI = 3.141592653;

/// <summary>
/// Класс определяющий юнита.
/// </summary>
class Unit
{
public:
    /// <summary>
    /// Создать юнита, задав ему позицию и направление взгляда.
    /// </summary>
    /// <param name="location">Позиция юнита.</param>
    /// <param name="directionOfSight">Точка, куда направлен взгляд юнита. Центр сектора.</param>
    Unit(Point location = Point(0, 0), Point directionOfSight = Point(0, 0))
    {
        this->location = location;
        this->directionOfSight = directionOfSight;
    }
    /// <summary>
    /// Позиция юнита.
    /// </summary>
    Point location;
    /// <summary>
    /// Точка, куда направлен взгляд юнита. Центр сектора.
    /// </summary>
    Point directionOfSight;
    /// <summary>
    /// Номера юнитов, которые видны этому юниту.
    /// </summary>
    std::vector<int> numbersUnitsInDirectionOfSight;
    
    /// <summary>
    /// Половина угла обзора в радианах.
    /// По умолчанию: (135.5/2) * (PI / 180)
    /// </summary>
    double halfOfVisionAngleInRadians = (135.5 * PI) / 360;
    /// <summary>
    /// Радиус - дальность обзора.
    /// </summary>
    double radius = 2;

#pragma region Вычисление видимости

private:

    bool AreClockwise(Point p1, Point p2)
    {
        return (-p1.x * p2.y + p1.y * p2.x) > 0;
    }
    /// <summary>
    /// Перемещение точки по окружности.
    /// </summary>
    /// <param name="point"></param>
    /// <param name="angle">Угол в радианах.</param>
    /// <param name="radius"></param>
    /// <returns></returns>
    Point RotatePointOnCircle(Point point, double angle)
    {
        Point rotatePoint;
        rotatePoint.x = this->radius * cos(angle);
        rotatePoint.y = this->radius * sin(angle);
        return rotatePoint;
    }
    bool isInsideSector(Point positionUnit, Point shiftDirectionOfSight)
    {

        //Посчитать sectorStart и sectorEnd
        Point sectorStart = RotatePointOnCircle(shiftDirectionOfSight, this->halfOfVisionAngleInRadians);
        Point sectorEnd = RotatePointOnCircle(shiftDirectionOfSight, -this->halfOfVisionAngleInRadians);

        return !AreClockwise(sectorStart, positionUnit) &&
            AreClockwise(sectorEnd, positionUnit);
    }

    /// <summary>
    /// Проверить, что точки находятся в одной четверти.
    /// </summary>
    /// <param name="firstPoint"></param>
    /// <param name="secondPoint"></param>
    /// <returns>true, если они в одной четверти.</returns>
    bool DotsInOneQuarter(Point firstPoint, Point secondPoint)
    {
        bool isBothHigherOrLowerThanX = false;
        if ((firstPoint.x >= 0 && secondPoint.x >= 0) ||
            (firstPoint.x <= 0 && secondPoint.x <= 0))
            isBothHigherOrLowerThanX = true;
        bool isBothHigherOrLowerThanY = false;
        if ((firstPoint.y >= 0 && secondPoint.y >= 0) ||
            (firstPoint.y <= 0 && secondPoint.y <= 0))
            isBothHigherOrLowerThanY = true;
        return isBothHigherOrLowerThanX & isBothHigherOrLowerThanY;
    }
    /// <summary>
/// Проверить, находится ли юнит в поле зрения.
/// </summary>
/// <param name="positionUnit">Местонахождение наблюдаемого юнита.</param>
/// <returns></returns>
    inline bool IsUnitInSight(Point positionUnit)
    {
        //Сдвинуть все точки так, чтобы этот юнит был в координатах 0;0
        double shiftX = this->location.x;
        double shiftY = this->location.y;
        Point shiftDirectionOfSight = Point(this->directionOfSight.x - shiftX, this->directionOfSight.y - shiftY);
        Point shiftPositionUnit = Point(positionUnit.x - shiftX, positionUnit.y - shiftY);

        /*
        //Если позиция юнита "за спиной" у смотрящего.
        // Позиции не могут быть далеко друг от друга из-за ограниченности дальности видимости.
        // Потому можно перемножать и не боться переполнения.
        if ((shiftDirectionOfSight.x * shiftPositionUnit.x < 0) && (shiftDirectionOfSight.y * shiftPositionUnit.y < 0) ||
            (shiftDirectionOfSight.x * shiftPositionUnit.x == 0) && (shiftDirectionOfSight.y * shiftPositionUnit.y < 0) ||
            (shiftDirectionOfSight.x * shiftPositionUnit.x < 0) && (shiftDirectionOfSight.y * shiftPositionUnit.y == 0))
        {
            return false;
        }
        //найти в радианах соответствующие углы зрению и метоположению
        double angleOfView = atan(shiftDirectionOfSight.y / shiftDirectionOfSight.x);
        double angleOfVectorToUnit = atan(shiftPositionUnit.y / shiftPositionUnit.x);*/

        //Если разница между углом зрения и местоположением меньше половины угла обзора, то юнит видно.
        if (isInsideSector(shiftPositionUnit, shiftDirectionOfSight))
        {
            return true;
        }

        //Если мы уже тут, то не видно юнита.
        return false;
    }
    /// <summary>
    /// Проверить находится ли юнит в пределах коружности или на ее границе.
    /// </summary>
    /// <param name="positionUnit">Местонахождение наблюдаемого юнита.</param>
    /// <returns>true, если в переделах окружности или на ней самой.</returns>
    inline bool IsInsideCircle(Point positionUnit)
    {
        double deltaX = positionUnit.x - this->location.x;
        double deltaY = positionUnit.y - this->location.y;
        const double radius = this->radius;

        //Если они стоят в одной точке, то они не могут друг друга видеть.
        if (!(deltaX + deltaY))
        {
            return false;
        }
        //При хорошем разбросе юнитов эта ситуация будет встречаться чаще всего.
        if (abs(deltaX) > radius || abs(deltaY) > radius)
            return false;

        //Если юнит все-таки где-то рядом, тогда проверить в границе ли он или на ней ли.
        if (deltaX * deltaX + deltaY * deltaY <= radius * radius)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

public:
    /// <summary>
    /// Проверяет находится ли указанный юнит в поле видимости этого юнита.
    /// </summary>
    /// <param name="positionUnit">Местонахождение наблюдаемого юнита.</param>
    /// <returns></returns>
    inline bool UnitIsVisible(Point positionUnit)
    {
        bool sight = IsUnitInSight(positionUnit);
        bool inCircle = IsInsideCircle(positionUnit);
        return  sight & inCircle;
    }
    /// <summary>
    /// Узнать номера юнитов, которых видит этот юнит.
    /// </summary>
    /// <param name="listOfUnits"></param>
    void FindNumberOfUnitsThatThisUnitSees(std::vector<Unit>& listOfUnits)
    {
        std::vector<int> numbersVisibilityUnits;
        int countOfUnits = listOfUnits.size();
        for (int i = 0; i < countOfUnits; ++i)
        {
            if (this->UnitIsVisible(listOfUnits[i].location))
            {
                numbersVisibilityUnits.push_back(i);
            }
        }
        this->numbersUnitsInDirectionOfSight = numbersVisibilityUnits;
    }
    /// <summary>
    /// Получить количество юнитов, которых видит этот юнит.
    /// </summary>
    /// <returns></returns>
    int GetCountVisibilityUnits()
    {
        return this->numbersUnitsInDirectionOfSight.size();
    }

#pragma endregion 

#pragma region Задание случайных значений

private:
    /// <summary>
    /// Вычислить случайный double в диапазоне.
    /// </summary>
    /// <param name="fMin"></param>
    /// <param name="fMax"></param>
    /// <returns></returns>
    inline double fRand(double fMin, double fMax)
    {
        double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
    }
public:
    /// <summary>
    /// Задать случайное местоположение из указанного диапазона для обеих координат.
    /// </summary>
    /// <param name="min"></param>
    /// <param name="max"></param>
    void CalculateRandomLocation(double min, double max)
    {
        this->location = Point(fRand(min, max), fRand(min, max));
    }
    /// <summary>
    /// Задать случайное направление из указанного диапазона для обеих координат точки направления.
    /// </summary>
    /// <param name="min"></param>
    /// <param name="max"></param>
    void CalculateRandomDirectionOfSight(double min, double max)
    {
        this->directionOfSight = Point(fRand(min, max), fRand(min, max));
    }

#pragma endregion 

public:
    /// <summary>
    /// Перевести значения объекта в строковое представление.
    /// </summary>
    /// <returns></returns>
    std::string ToString()
    {
        using namespace std;
        string returnString = "location: " + to_string(this->location.x) + ";" + to_string(this->location.y) + "; "
            + "directionOfSight: " + to_string(this->directionOfSight.x) + ";" + to_string(this->directionOfSight.y) + "; "
            + "numbersUnitsInDirectionOfSight: ";

        for (auto it = this->numbersUnitsInDirectionOfSight.begin();
            it != this->numbersUnitsInDirectionOfSight.end(); ++it)
        {
            returnString += to_string(*it) + ";";
        }

        return returnString;
    }

};



