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


#pragma region Тесты скорости

public:
	/// <summary>
	/// Запустить все тесты на скорость.
	/// </summary>
	void StartAllSpeedTests()
	{
		for (int i = 3; i < 7; i++)
		{
			int countUnits = (int)pow(10, i);
			SpeedTest(countUnits);
			SpeedTestWithMap(countUnits);
			SpeedTestParallel(countUnits);
		}
	}

private:
	double  spreadOfValues = 3000;
	/// <summary>
	/// Запустить тест на скорость, с определенным количеством юнитов.
	/// /// </summary>
	/// <param name="countOfUnits"></param>
	void SpeedTest(int countOfUnits)
	{
		const int countOfRepeats = this->countOfRepeats;

		cout << "Количество юнитов: " << countOfUnits << endl;

		this->manyUnits = Units(countOfUnits);

		//Запомнить время запуска.
		auto start = system_clock::now();

		for (int i = 0; i < countOfRepeats; ++i)
			this->manyUnits.CalculateVisionForAllUnits();

		auto end = system_clock::now();
		std::cout << "Выполнение заняло: " << ((duration<double>)(end - start)).count() << "\n\n";
	}
	/// <summary>
	/// Запустить тест на скорость, с определенным количеством юнитов.
	/// Запуск с учетом размещения юнитов на карте в ячейки.
	/// /// </summary>
	/// <param name="countOfUnits"></param>
	void SpeedTestWithMap(int countOfUnits)
	{
		const int countOfRepeats = this->countOfRepeats;

		cout << "Количество юнитов (с картой и ячейками): " << countOfUnits << endl;

		this->manyUnits = Units(countOfUnits);

		//Запомнить время запуска.
		auto start = system_clock::now();

		for (int i = 0; i < countOfRepeats; ++i)
			this->manyUnits.CalculateVisionForAllUnitsWithMapCells();

		auto end = system_clock::now();
		std::cout << "Выполнение заняло: " << ((duration<double>)(end - start)).count() << "\n\n";
	}
	/// <summary>
	/// Запустить тест на скорость, с определенным количеством юнитов с использованием потоков.
	/// /// </summary>
	/// <param name="countOfUnits"></param>
	void SpeedTestParallel(int countOfUnits)
	{
		const int countOfRepeats = this->countOfRepeats;

		cout << "Количество юнитов(параллельный код): " << countOfUnits << endl;

		this->manyUnits = Units(countOfUnits);

		//Запомнить время запуска.
		auto start = system_clock::now();

		for (int i = 0; i < countOfRepeats; ++i)
			this->manyUnits.CalculateVisionForAllUnitsParallel();

		auto end = system_clock::now();
		std::cout << "Выполнение заняло: " << ((duration<double>)(end - start)).count() << "\n\n";
	}

#pragma endregion

#pragma region Тесты сохранения/загрузки

public:
	/// <summary>
	/// Запустить все тесты сохранения в файл и загрузки из него.
	/// </summary>
	void StartAllSaveAndLoadTests()
	{
		string name = "Test save.txt";
		double x = 3.45;
		double y = 5.89;

		this->manyUnits = Units(5);
		this->manyUnits.units[0].location = Point(x, y);
		this->manyUnits.units[0].SetDirectionOfSight(Point(x, y));
		this->manyUnits.units[0].numbersUnitsInDirectionOfSight = { 1,2, 3 };

		this->manyUnits.Save(name);
		this->manyUnits.Load(name);


		cout << "\nSave and load tests was ";
		if (this->manyUnits.units[0].location.x != x ||
			this->manyUnits.units[0].location.y != y ||
			this->manyUnits.units[0].directionOfSight.x != x ||
			this->manyUnits.units[0].directionOfSight.y != y ||
			this->manyUnits.units[0].numbersUnitsInDirectionOfSight[0] != 1 ||
			this->manyUnits.units[0].numbersUnitsInDirectionOfSight[1] != 2 ||
			this->manyUnits.units[0].numbersUnitsInDirectionOfSight[2] != 3 ||
			this->manyUnits.units.size() != 5
			)
		{//Если хоть что-то не совпало после загрузки, то тест не пройден.
			cout << "not complete!\n";
		}
		else
		{
			cout << "complete!\n";
		}
	}

#pragma endregion
};