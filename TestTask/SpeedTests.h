#pragma once
#include <chrono>
#include "Units.h"
#include <iostream>

using namespace std;
using namespace std::chrono;

/// <summary>
/// ����� ��� ���������� ������.
/// </summary>
class Tests
{
private:
	const int countOfRepeats = 1;
Units manyUnits;

public:
/// <summary>
/// ��������� ��� ����� �� ��������.
/// </summary>
void StartAllSpeedTests()
{
	SpeedTest(9);
	SpeedTest(99);
	SpeedTest(999);
	SpeedTest(9999);
}

private:
/// <summary>
/// ��������� ���� �� ��������, � ������������ ����������� ������.
/// /// </summary>
/// <param name="countOfUnits"></param>
void SpeedTest(int countOfUnits)
{
	const int countOfRepeats = this->countOfRepeats;

	cout << "���������� ������: " << countOfUnits << endl;

	this->manyUnits = Units(countOfUnits);
	this->manyUnits.SetRandomParametrsForAllUnits(-100, 100);

	//��������� ����� �������.
	auto start = system_clock::now();

	for(int i=0;i<countOfRepeats;++i)
		this->manyUnits.CalculateVisionForAllUnits();

	auto end = system_clock::now();
	std::cout << "���������� ������: " << ((duration<double>)(end - start)).count() << "\n\n";
}
};