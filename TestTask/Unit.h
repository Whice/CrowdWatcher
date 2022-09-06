#pragma once
#include "Point.h"
#include <vector>
#include <cstring>
#include <string>
#include <math.h>
#include "Vector2.h"
#include "Consts.h"


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
    Unit(const Point& location = Point(0, 0), const Point& directionOfSight = Point(0, 0))
    {
        this->location = location;
        SetDirectionOfSight(directionOfSight);
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
    /// Задать точку, куда направлен взгляд юнита. Центр сектора.
    /// </summary>
    /// <param name="directionOfSight"></param>
public:
    inline void SetDirectionOfSight(const Point& directionOfSight = Point(0, 0))
    {
        this->directionOfSight = directionOfSight;
        this->direction = Vector2(directionOfSight.x, directionOfSight.y)
            - Vector2(this->location.x, this->location.y);
        this->direction.Normalize();
    }
    /// <summary>
    /// Направление взгляда юнита.
    /// </summary>
    Vector2 direction;
    /// <summary>
    /// Номера юнитов, которые видны этому юниту.
    /// </summary>
    std::vector<int> numbersUnitsInDirectionOfSight;
    /// <summary>
    /// Количество юнитов, которых выидит этот юнит.
    /// </summary>
    int countUnitsInDirectionOfSight;
private:
    /// <summary>
    /// Половина угла обзора в радианах.
    /// По умолчанию: (135.5/2) * (PI / 180)
    /// </summary>
    const double HALF_OF_VISION_ANGLE_IN_RADIANS = (135.5 * PI) / 360;
    /// <summary>
    /// Комплексное число для поворота вектора на половину
    /// угла видимости юнита против часовой стрелки.
    /// </summary>
    const Point ROTATE_COMPLEX_HALF_OF_VISION = Point
    (
        cos(this->HALF_OF_VISION_ANGLE_IN_RADIANS),
        sin(this->HALF_OF_VISION_ANGLE_IN_RADIANS)
    );
    /// <summary>
    /// Радиус - дальность обзора.
    /// </summary>
public:static const int SIGHT_DISTANCE = 2;

#pragma region Вычисление видимости

private:

    /// <summary>
/// Проверить, находится ли юнит в поле зрения.
/// </summary>
/// <param name="positionUnit">Местонахождение наблюдаемого юнита.</param>
/// <returns></returns>
    inline bool IsUnitInSightOld(const Point &positionUnit)
    {
        //Сдвинуть все точки так, чтобы этот юнит был в координатах 0;0
        double shiftX = this->location.x;
        double shiftY = this->location.y;
        Point shiftDirectionOfSight = Point(this->directionOfSight.x - shiftX, this->directionOfSight.y - shiftY);
        Point shiftPositionUnit = Point(positionUnit.x - shiftX, positionUnit.y - shiftY);

        // Т.к. atan2 работает с пи по -пи, то по абсцисс можно отразить координаты.
        if (shiftPositionUnit.x < 0)
        {
            shiftPositionUnit.x *= -1;
            shiftDirectionOfSight.x *= -1;
        }

        //Если позиция юнита "за спиной" у смотрящего.
        // Позиции не могут быть далеко длпруг от друга из-за ограниченности дальности видимости.
        // Потому можно перемножать и не боться переполнения.
        if ((shiftDirectionOfSight.x * shiftPositionUnit.x < 0) &&
            (shiftDirectionOfSight.y * shiftPositionUnit.y < 0))
        {
            return false;
        }
        //найти в радианах соответствующие углы зрению и метоположению
        double angleOfView = atan2(shiftDirectionOfSight.y, shiftDirectionOfSight.x);
        double angleOfVectorToUnit = atan2(shiftPositionUnit.y, shiftPositionUnit.x);

        //Если разница между углом зрения и местоположением меньше половины угла обзора, то юнит видно.
        if (abs(angleOfView - angleOfVectorToUnit) < this->HALF_OF_VISION_ANGLE_IN_RADIANS)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    /// <summary>
/// Проверить, находится ли юнит в поле зрения.
/// </summary>
/// <param name="positionUnit">Местонахождение наблюдаемого юнита.</param>
/// <returns></returns>
    inline bool IsUnitInSight(const Point& positionUnit)
    {
        Vector2 direction = this->direction;
        Vector2 distance;
        distance.SetFromTwoPoints(this->location, positionUnit);
        //Проверить, что другой юнит не сзади.
        if (distance.Dot(direction) > 0)
        {
            //Найти левую границу зрения через поворот центра зрения на половину его угла.
            Vector2 leftBorderVision = direction;
            leftBorderVision.RotateWithComplex(this->ROTATE_COMPLEX_HALF_OF_VISION.x, this->ROTATE_COMPLEX_HALF_OF_VISION.y);

            //Проверить, что другой юнит правее левой границы зрения.
            if (distance.Skew(leftBorderVision) > 0)
            {
                //Отразить вектор левой границы относительно направления зрения и получить правую границу.
                direction.Normalize();
                leftBorderVision.Negative();
                Vector2 rightBorderVision = leftBorderVision - direction * leftBorderVision.Dot(direction) * 2;

                //Проверить, что другой юнит находится левее правой границы зения.
                if (rightBorderVision.Skew(distance) > 0)
                    return true;
            }
        }

        return false;
    }
    /// <summary>
    /// Проверить находится ли юнит в пределах коружности или на ее границе.
    /// </summary>
    /// <param name="positionUnit">Местонахождение наблюдаемого юнита.</param>
    /// <returns>true, если в переделах окружности или на ней самой.</returns>
    inline bool IsInsideCircle(const Point& positionUnit)
    {
        const double deltaX = positionUnit.x - this->location.x;
        const double deltaY = positionUnit.y - this->location.y;
        const double radius = this->SIGHT_DISTANCE;

        //Если они стоят в одной точке, то они не могут друг друга видеть.
        if (!(deltaX + deltaY))
            return false;

        //При хорошем разбросе юнитов эта ситуация будет встречаться чаще всего.
        if (abs(deltaX) > radius || abs(deltaY) > radius)
            return false;

        //Если юнит все-таки где-то рядом, тогда проверить в границе ли он или на ней ли.
        if (deltaX * deltaX + deltaY * deltaY <= radius * radius)
            return true;
        else
            return false;
    }

public:
    /// <summary>
    /// Проверяет находится ли указанный юнит в поле видимости этого юнита.
    /// </summary>
    /// <param name="positionUnit">Местонахождение наблюдаемого юнита.</param>
    /// <returns></returns>
    inline bool UnitIsVisible(const Point& positionUnit)
    {
        return IsInsideCircle(positionUnit) && IsUnitInSight(positionUnit);
    }
    /// <summary>
    /// Узнать количество юнитов, которых видит этот юнит.
    /// </summary>
    /// <param name="listOfUnits"></param>
    void FindCountOfUnitsThatThisUnitSees(const std::vector<Unit>& listOfUnits)
    {
        int countVisibleUnits = 0;
        const int countOfUnits = listOfUnits.size();
        for (int i = 0; i < countOfUnits; ++i)
        {
            if (this->UnitIsVisible(listOfUnits[i].location))
            {
                ++countVisibleUnits;
            }
        }
        this->countUnitsInDirectionOfSight = countVisibleUnits;
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
        SetDirectionOfSight(Point(fRand(min, max), fRand(min, max)));
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

    bool operator<(const Unit& other) const
    {
        bool res = this->location > other.location;
        return res;
    }
    inline
        bool operator==(const Unit& other) const
    {
        return this->location == other.location;
    }

    inline
        bool operator!=(const Unit& other) const
    {
        return this->location != other.location;
    }

};



