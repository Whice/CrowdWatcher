#pragma once
#include "Point.h"
#include <vector>

const double PI = 3.14159265;

/// <summary>
/// ����� ������������ �����.
/// </summary>
class Unit
{
public:
	/// <summary>
	/// ������� �����, ����� ��� ������� � ����������� �������.
	/// </summary>
	/// <param name="location">������� �����.</param>
	/// <param name="directionOfSight">�����, ���� ��������� ������ �����. ����� �������.</param>
	Unit(Point location=Point(0, 0), Point directionOfSight= Point(0, 0))
	{
		this->location = location;
		this->directionOfSight = directionOfSight;
	}
	/// <summary>
	/// ������� �����.
	/// </summary>
	Point location;
	/// <summary>
	/// �����, ���� ��������� ������ �����. ����� �������.
	/// </summary>
	Point directionOfSight;
    /// <summary>
    /// ������ ������, ������� ����� ����� �����.
    /// </summary>
	std::vector<int> numbersUnitsInDirectionOfSight;

#pragma region ���������� ���������

private:
    /// <summary>
/// ���������, ��������� �� ���� � ���� ������.
/// </summary>
/// <param name="positionUnit">����� - ��������������� �������� �����.</param>
/// <param name="halfOfVisionAngleInRadians">���� ������ � ��������.</param>
/// <returns></returns>
    bool IsUnitInSight(Point& positionUnit, double& halfOfVisionAngleInRadians )
    {
        //�������� ��� ����� ���, ����� ���� ���� ��� � ����������� 0;0
        int shiftX = this->location.x;
        int shiftY = this->location.y;
        Point shiftDirectionOfSight = Point(this->directionOfSight.x-shiftX, this->directionOfSight.y-shiftY);
        Point shiftPositionUnit = Point(positionUnit.x - shiftX, positionUnit.y - shiftY);


        //���� ������� ����� "�� ������" � ����������.
        // ������� �� ����� ���� ������ ������ �� ����� ��-�� �������������� ��������� ���������.
        // ������ ����� ����������� � �� ������ ������������.
        if ((shiftDirectionOfSight.x * shiftPositionUnit.x < 0) &&
            (shiftDirectionOfSight.y * shiftPositionUnit.y < 0))
        {
            return false;
        }
        //����� � �������� ��������������� ���� ������ � �������������
        double angleOfView = atan(shiftDirectionOfSight.y / shiftDirectionOfSight.x);
        double angleOfVectorToUnit = atan(shiftPositionUnit.y / shiftPositionUnit.x);

        //���� ������� ����� ����� ������ � ��������������� ������ �������� ���� ������, �� ���� �����.
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
    /// ��������� ��������� �� ���� � �������� ���������� ��� �� �� �������.
    /// </summary>
    /// <param name="positionUnit">��������������� �����.</param>
    /// <param name="radius">������ ����������.</param>
    /// <returns>true, ���� � ��������� ���������� ��� �� ��� �����.</returns>
    bool IsInsideCircle(Point& positionUnit, double& radius)
    {
        double deltaX = positionUnit.x - this->location.x;
        double deltaY = positionUnit.y - this->location.y;

        //��� ������� �������� ������ ��� �������� ����� ����������� ���� �����.
        if (abs(deltaX) > radius || abs(deltaY) > radius)
            return false;

        //���� ���� ���-���� ���-�� �����, ����� ��������� � ������� �� �� ��� �� ��� ��.
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
    /// ��������� ��������� �� ��������� ���� � ���� ��������� ����� �����.
    /// </summary>
    /// <param name="positionUnit">����� - ��������������� �����.</param>
    /// <param name="visionAngle">���� ������ � ��������. ������ �������.</param>
    /// <param name="radius">������ ����������. ��������� ���������.</param>
    /// <returns></returns>
    bool UnitIsVisible(Point& positionUnit, double halfOfVisionAngleInRadians = (135.5 * PI) / 360/*135.5/2 * PI / 180*/,
        double radius = 2)
    {
        bool sight = IsUnitInSight(positionUnit, halfOfVisionAngleInRadians);
        bool inCircle = IsInsideCircle(positionUnit, radius);
        return  sight&inCircle ;
    }

    void CalculateUnitsVisibilityForThisUnit(std::vector<Unit>& listOfUnits, int selfNumberInList)
    {
        std::vector<int> numbersVisibilityUnits;
        int countOfUnits = listOfUnits.size();
        for (int i = 0; i < selfNumberInList; ++i)
        {
            if (this->UnitIsVisible(listOfUnits[i].location))
            {
                numbersVisibilityUnits.push_back(i);
            }
        }
        for (int i = selfNumberInList+1; i < countOfUnits; ++i)
        {
            if (this->UnitIsVisible(listOfUnits[i].location))
            {
                numbersVisibilityUnits.push_back(i);
            }
        }
        this->numbersUnitsInDirectionOfSight = numbersVisibilityUnits;
    }

#pragma endregion ���������� ���������
};

