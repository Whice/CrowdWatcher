#pragma once
#include <iostream>
#include <conio.h>
#include <cmath>
#include "Units.h"
#include "Tests.h"
#include <cstring>
#include <string>

using namespace std;

int main()
{

    setlocale(LC_ALL, "");
    
    //Создать тестовый объект
    Tests test;
    //Тесты скорости
    test.StartAllSpeedTests();
    //Тесты сохранения и загрузки
    //test.StartAllSaveAndLoadTests();
    
    return _getch();
}
