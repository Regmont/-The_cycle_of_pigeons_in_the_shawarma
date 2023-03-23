#include <iostream>
#include <random>
#include <time.h>
#include <stdio.h>
#include <string>
using namespace std;

struct Pigeon
{
    int meat;
    int fluff;
};

Pigeon createPigeon()
{
    Pigeon s;
    s.meat = 225 - rand() % 50;
    s.fluff = 125 - rand() % 50;
    return s;
}

void addPigeon (Pigeon*& pigeons, int& amount, Pigeon pigeon)
{
    Pigeon* temp = new Pigeon[amount + 1];

    for (int i = 0; i < amount; i++)
    {
        temp[i] = pigeons[i];
    }

    temp[amount] = pigeon;
    delete[] pigeons;
    pigeons = temp;
    amount++;
}

void killPigeon(Pigeon*& pigeons, int& amount)
{
    Pigeon* temp = new Pigeon[amount - 1];

    for (int i = 1; i < amount; i++)
    {
        temp[i - 1] = pigeons[i];
    }

    delete[] pigeons;
    pigeons = temp;
    amount--;
}

void month(int& amount, int& shashlik, int& fluff, int& meat_cost, int& fluff_cost, int& pigeon_cost)
{
    amount = 0;
    pigeon_cost = 0;
    Pigeon* arrPigeons = new Pigeon[amount];

    for (int i = 0; i < 1000; i++)
    {
        Pigeon new_pigeon = createPigeon();
        addPigeon(arrPigeons, amount, new_pigeon);
    }

    shashlik = 0;
    fluff = 0;

    for (int i = 0; i < 31; i++)    //месяц
    {
        for (int j = 0; j < amount; j++)
        {
            arrPigeons[j].meat += 10;
            arrPigeons[j].fluff += 20;
        }

        for (int j = 0; j < amount / 25; j++)
        {
            Pigeon new_pigeon = createPigeon();
            addPigeon(arrPigeons, amount, new_pigeon);
            pigeon_cost += 10;
        }

        do
        {
            shashlik += arrPigeons[0].meat;
            fluff += arrPigeons[0].fluff;
            killPigeon(arrPigeons, amount);
        } while (shashlik < 10000);

        shashlik -= 10000;
    }
    meat_cost = 31 * 1000;  //по 1000р за 1кг
    fluff_cost = fluff / 10;  //по 1р за 10г
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "ru");

    int amount;
    int shashlik;
    int fluff;
    int meat_cost;
    int fluff_cost;
    int pigeon_cost;
    FILE* file;
    int a;
    string str1 = "Месяц ";
    string str2 = "Количество голубей в конце месяца: ";
    string str3 = "Оставшееся количество шашлыка в граммах в конце месяца: ";
    string str4 = "Количество пуха в граммах в конце месяца: ";
    string str5 = "Вырученные деньги за продажу мяса в рублях: ";
    string str6 = "Вырученные деньги за продажу пуха в рублях: ";
    string str7 = "Сумма, потраченная на покупку голубей в рублях: ";
    string str8 = "Общая выручка в рублях: ";
    string str9 = "\n";

    if (fopen_s(&file, "P:\\Студенты\\П22\\python\\Dunin\\c++\\march_21\\income.txt", "w") != NULL)
        cout << "The file cannot be opened";
    else
        for (int i = 1; i < 13; i++)
        {
            month(amount, shashlik, fluff, meat_cost, fluff_cost, pigeon_cost);
            fputs(str1.c_str(), file);
            fputs(to_string(i).c_str(), file);
            fputs(str9.c_str(), file);
            fputs(str2.c_str(), file);
            fputs(to_string(amount).c_str(), file);
            fputs(str9.c_str(), file);
            fputs(str3.c_str(), file);
            fputs(to_string(shashlik).c_str(), file);
            fputs(str9.c_str(), file);
            fputs(str4.c_str(), file);
            fputs(to_string(fluff).c_str(), file);
            fputs(str9.c_str(), file);
            fputs(str5.c_str(), file);
            fputs(to_string(meat_cost).c_str(), file);
            fputs(str9.c_str(), file);
            fputs(str6.c_str(), file);
            fputs(to_string(fluff_cost).c_str(), file);
            fputs(str9.c_str(), file);
            fputs(str7.c_str(), file);
            fputs(to_string(pigeon_cost).c_str(), file);
            fputs(str9.c_str(), file);
            fputs(str8.c_str(), file);
            fputs(to_string(fluff_cost + meat_cost - pigeon_cost).c_str(), file);
            fputs(str9.c_str(), file);
            fputs(str9.c_str(), file);
        }
    fclose(file);
}