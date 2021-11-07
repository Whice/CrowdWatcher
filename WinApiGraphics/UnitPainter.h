#pragma once
#include "Units.h"
#include <Windows.h>

/// <summary>
/// ����� ��������� ������ � WinApi.
/// </summary>
class UnitPainter
{

public:
	UnitPainter()
	{
		this->colorBody = RGB(244, 188, 70);
		this->brushBody = CreateSolidBrush(this->colorBody);
		this->penBody = CreatePen(PS_SOLID, 1, RGB(58, 5, 52));
		this->sizeOfBody = 20;


		this->colorNose = RGB(255, 0, 0);
		this->brushNose = CreateSolidBrush(this->colorNose);
		this->penNose = CreatePen(PS_SOLID, 1, this->colorNose);
		this->sizeOfNose = sizeOfBody / 2;

		this->backColor = RGB(166, 85, 148);
		this->backBrush = CreateSolidBrush(this->backColor);
		this->backPen = CreatePen(PS_SOLID, 1, this->backColor);
	}
private:
	/// <summary>
	/// ���� ����.
	/// </summary>
	COLORREF colorBody = RGB(255, 255, 0);
	/// <summary>
	/// ����� ����.
	/// </summary>
	HBRUSH brushBody = CreateSolidBrush(this->colorBody);
	/// <summary>
	/// ����� ����.
	/// </summary>
	HPEN penBody = CreatePen(PS_SOLID, 1, this->colorBody);
	/// <summary>
	/// ������ ����.
	/// </summary>
	int sizeOfBody = 20;

	/// <summary>
	/// ���� ����.
	/// </summary>
	COLORREF colorNose = RGB(244, 188, 70);
	/// <summary>
	/// ����� ����.
	/// </summary>
	HBRUSH brushNose = CreateSolidBrush(this->colorBody);
	/// <summary>
	/// ����� ����.
	/// </summary>
	HPEN penNose = CreatePen(PS_SOLID, 1, this->colorBody);
	/// <summary>
	/// ������ ����.
	/// </summary>
	int sizeOfNose = sizeOfBody/2;

	/// <summary>
	/// ���� �������.
	/// </summary>
	COLORREF backColor = RGB(166, 85, 148);
	/// <summary>
	/// ����� �������.
	/// </summary>
	HBRUSH backBrush = CreateSolidBrush(this->colorBody);
	/// <summary>
	/// ����� �������.
	/// </summary>
	HPEN backPen = CreatePen(PS_SOLID, 1, this->colorBody);
public:
	/// <summary>
	/// ������ ������� �� ������.
	/// </summary>
	UINT backSizeWidth = 0;
	/// <summary>
	/// ������ ������� �� ������.
	/// </summary>
	UINT backSizeHeight = 0;
	void ClearBackground(HDC& hdc)
	{
		SelectObject(hdc, this->backBrush);
		SelectObject(hdc, this->backPen);
		Rectangle(hdc, -10, -10, this->backSizeWidth + 2, this->backSizeHeight + 2);
	}



private:
	/// <summary>
	/// ��������� ����� � �������� �����.
	/// </summary>
	void DrawCircle(HDC& hdc, Point location, int size)
	{
		int halfSize = size / 2;
		int left = (int)location.x - halfSize;
		int right = (int)location.x + halfSize;
		int top = (int)location.y - halfSize;
		int bottom = (int)location.y + halfSize;

		Ellipse(hdc, left, top, right, bottom);
	}

public:
	/// <summary>
	/// 
	/// </summary>
	/// <param name="numberObserver">����� ����� - ����������� � ������ ������.</param>
	/// <param name="units">������ ������ ��� ���������.</param>
	void DrawVisibleUnitsForUnit(HDC& hdc, int numberObserver, std::vector<Unit>* units)
	{
		// ������ ������, ��� ���������.
		std::vector<int>* numbersUnitsInDirectionOfSight = &(*units)[numberObserver].numbersUnitsInDirectionOfSight;

		Unit* localUnit;

		auto end = numbersUnitsInDirectionOfSight->end();
		for (auto i = numbersUnitsInDirectionOfSight->begin(); i != end; ++i)
		{
			DrawUnit(hdc, (*units)[*i]);
		}

	}
	/// <summary>
	/// ��������� ������ �����.
	/// </summary>
	/// <param name="hdc"></param>
	/// <param name="unitForDraw"></param>
	void DrawUnit(HDC& hdc, Unit& unitForDraw)
	{
		//��������� ����
		SelectObject(hdc, this->brushNose);
		SelectObject(hdc, this->penNose);
		DrawCircle(hdc, unitForDraw.location, this->sizeOfNose);

		//��������� ����
		SelectObject(hdc, this->brushBody);
		SelectObject(hdc, this->penBody);
		DrawCircle(hdc, unitForDraw.location, this->sizeOfBody);
	}

};

