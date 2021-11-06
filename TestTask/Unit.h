#pragma once
#include "Point.h"
#include <vector>

const double PI = 3.14159265;

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
	Unit(Point location=Point(0, 0), Point directionOfSight= Point(0, 0))
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

#pragma region Вычисление видимости

private:
    /// <summary>
/// Проверить, находится ли юнит в поле зрения.
/// </summary>
/// <param name="positionUnit">Местонахождение наблюдаемого юнита.</param>
/// <param name="halfOfVisionAngleInRadians">Угол обзора в радианах.</param>
/// <returns></returns>
    bool IsUnitInSight(Point& positionUnit, double& halfOfVisionAngleInRadians )
    {
        //Сдвинуть все точки так, чтобы этот юнит был в координатах 0;0
        double shiftX = this->location.x;
        double shiftY = this->location.y;
        Point shiftDirectionOfSight = Point(this->directionOfSight.x-shiftX, this->directionOfSight.y-shiftY);
        Point shiftPositionUnit = Point(positionUnit.x - shiftX, positionUnit.y - shiftY);


        //Если позиция юнита "за спиной" у смотрящего.
        // Позиции не могут быть далеко длпруг от друга из-за ограниченности дальности видимости.
        // Потому можно перемножать и не боться переполнения.
        if ((shiftDirectionOfSight.x * shiftPositionUnit.x < 0) &&
            (shiftDirectionOfSight.y * shiftPositionUnit.y < 0))
        {
            return false;
        }
        //найти в радианах соответствующие углы зрению и метоположению
        double angleOfView = atan(shiftDirectionOfSight.y / shiftDirectionOfSight.x);
        double angleOfVectorToUnit = atan(shiftPositionUnit.y / shiftPositionUnit.x);

        //Если разница между углом зрения и местоположением меньше половины угла обзора, то юнит видно.
        if (abs(angleOfView - angleOfVectorToUnit) < halfOfVisionAngleInRadians)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    /// <summary>
    /// Проверить находится ли юнит в пределах коружности или на ее границе.
    /// </summary>
    /// <param name="positionUnit">Местонахождение наблюдаемого юнита.</param>
    /// <param name="radius">Радиус окружности.</param>
    /// <returns>true, если в переделах окружности или на ней самой.</returns>
    bool IsInsideCircle(Point& positionUnit, double& radius)
    {
        double deltaX = positionUnit.x - this->location.x;
        double deltaY = positionUnit.y - this->location.y;

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
    /// <param name="visionAngle">Угол обзора в радианах. Размер сектора.</param>
    /// <param name="radius">Радиус окружности. Дальность видимости.</param>
    /// <returns></returns>
    bool UnitIsVisible(Point& positionUnit, double halfOfVisionAngleInRadians = (135.5 * PI) / 360/*135.5/2 * PI / 180*/,
        double radius = 2)
    {
        bool sight = IsUnitInSight(positionUnit, halfOfVisionAngleInRadians);
        bool inCircle = IsInsideCircle(positionUnit, radius);
        return  sight&inCircle ;
    }

    void CalculateUnitsVisibilityForThisUnit(std::vector<Unit>& listOfUnits)
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

};



