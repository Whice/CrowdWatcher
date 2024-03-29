#pragma once
#include <cmath>
#include <numbers>
#include "Point.h"
#include "Consts.h"

class Vector2
{
private:
	double x;
	double y;

public: Vector2()
{
	this->x = 0;
	this->y = 0;
}
public: Vector2(double x, double y)
{
	this->x = x;
	this->y = y;
}
#pragma region ��������.

public:
	inline Vector2& operator*=(double value)
	{
		x *= value;
		y *= value;
		return *this;
	}
	inline Vector2 operator*(double value)
	{
		return Vector2(this->x * value, this->y * value);
	}
	inline Vector2 operator+(Vector2 value)
	{
		return Vector2(this->x + value.x, this->y + value.y);
	}
	inline Vector2 operator-(Vector2 value)
	{
		return Vector2(this->x - value.x, this->y - value.y);
	}
	/// <summary>
	/// ������ ����� ��� x � y �� ���������������.
	/// </summary>
	inline void Negative()
	{
		this->x *= -1;
		this->y *= -1;
	}
#pragma endregion ��������.

public:
	/// <summary>
	/// ������ ������ ����� ��� �����.
	/// </summary>
	/// <param name="firstPoint">������ �������.</param>
	/// <param name="secondPoint">����� �������, ��� �����������.</param>
	void SetFromTwoPoints(const Point& firstPoint, const Point& secondPoint)
	{
		this->x = secondPoint.x - firstPoint.x;
		this->y = secondPoint.y - firstPoint.y;
	}
	/// <summary>
	/// ������ ������ ����� ���� � ��������.
	/// </summary>
	/// <param name="alpha"></param>
	void SetFromAngle(double alpha)
	{
		x = cos(alpha);
		y = sin(alpha);
	}
	/// <summary>
	/// �������� ���� � ��������.
	/// </summary>
	/// <returns></returns>
	double ToAngle()
	{
		return atan2(y, x);
	}
	/// <summary>
	/// ������ ������ ����� ���� � ��������.
	/// </summary>
	/// <param name="alpha"></param>
	void SetFromAngleDegrees(double alpha)
	{
		alpha = alpha * PI / 180;
		x = cos(alpha);
		y = sin(alpha);
	}
	/// <summary>
	/// �������� ���� � ��������.
	/// </summary>
	/// <returns></returns>
	double ToAngleDegrees()
	{
		return atan2(y, x) * 180 / PI;
	}
	inline double Length2()const
	{
		return x * x + y * y;
	}
	inline double Length()const
	{
		return sqrt(Length2());
	}
	inline Vector2& Normalize()
	{
		double length = Length();
		double rLength = length != 0 ? 1 / length : 0;
		x *= rLength;
		y *= rLength;
		return *this;
	}

public:
	inline double Dot(Vector2 otherVector)
	{
		return this->x * otherVector.x + this->y * otherVector.y;
	}
	inline double Skew(Vector2 otherVector)
	{
		return this->x * otherVector.y - this->y * otherVector.x;
	}
	/// <summary>
	/// �������� ���� � �������� ����� ���� �������� � ���������.
	/// </summary>
	/// <param name="therVector"></param>
	/// <returns></returns>
	inline double GetAngleRadWith(const Vector2& otherVector)
	{
		return acos(Dot(otherVector) / (Length() * otherVector.Length()));
	}
	/// <summary>
	/// ������� ���������� � ���� ������.
	/// </summary>
	/// <param name="therVector"></param>
	/// <returns>������ 1, ���� ���������� � ���� �������. 
	/// ������ 0, ���� ���������������.
	/// ������ -1, ���� � ������ ������� ����������.</returns>
	inline int SameDirectionWith(const Vector2& otherVector)
	{
		double dot = Dot(otherVector);
		if (dot > 0)
			return 1;
		if (dot < 0)
			return -1;
		return 0;
	}
	/// <summary>
	/// ����������� �������� ����� ����������� �����.
	/// </summary>
	/// <param name="a">�������������� �����.</param>
	/// <param name="b">������ �����.</param>
	/// <returns></returns>
	inline void RotateWithComplex(double a, double b)
	{
		double x = this->x;
		double y = this->y;
		this->x = x * a - y * b;
		this->y = x * b + y * a;
	}

public:
	inline std::string ToString()
	{
		return "X: " + std::to_string(this->x) + "; Y: " + std::to_string(this->y) + ";";
	}
};