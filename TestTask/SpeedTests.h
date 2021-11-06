#pragma once
#include <chrono>
#include "Units.h"
#include <iostream>

using namespace std;
using namespace std::chrono;

/// <summary>
/// Класс для проведения тестов.
/// </summary>
class Tests
{
private:
	const int countOfRepeats = 1;
Units manyUnits;

public:
/// <summary>
/// Запустить все тесты на скорость.
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
/// Запустить тест на скорость, с определенным количеством юнитов.
/// /// </summary>
/// <param name="countOfUnits"></param>
void SpeedTest(int countOfUnits)
{
	const int countOfRepeats = this->countOfRepeats;

	cout << "Количество юнитов: " << countOfUnits << endl;

	this->manyUnits = Units(countOfUnits);
	this->manyUnits.SetRandomParametrsForAllUnits(-100, 100);

	//Запомнить время запуска.
	auto start = system_clock::now();

	for(int i=0;i<countOfRepeats;++i)
		this->manyUnits.CalculateVisionForAllUnits();

	auto end = system_clock::now();
	std::cout << "Выполнение заняло: " << ((duration<double>)(end - start)).count() << "\n\n";
}
};