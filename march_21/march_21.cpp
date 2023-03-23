#include <iostream>
#include <random>
#include <time.h>
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

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "ru");

    int amount = 0;
    Pigeon* arrPigeons = new Pigeon[amount];

    for (int i = 0; i < 1000; i++)
    {
        Pigeon new_pigeon = createPigeon();
        addPigeon(arrPigeons, amount, new_pigeon);
    }

    int shashlik = 0;
    int fluff = 0;

    for (int i = 0; i < 31; i++)    //месяц
    {
        for (int j = 0; j < amount; j++)
        {
            arrPigeons[j].meat += 10;
            arrPigeons[j].fluff += 20;
        }

        for (int j = 0; j < 100; j++)
        {
            Pigeon new_pigeon = createPigeon();
            addPigeon(arrPigeons, amount, new_pigeon);
        }

        do
        {
            shashlik += arrPigeons[0].meat;
            fluff += arrPigeons[0].fluff;
            killPigeon(arrPigeons, amount);
        } while (shashlik < 1000);

        shashlik -= 1000;
    }

    cout << "Количество кур в конце месяца: " << amount << endl;
    cout << "Оставшееся количество шашлыка в граммах в конце месяца: " << shashlik << endl;
    cout << "Количество пуха в граммах в конце месяца: " << fluff << endl;

    int meat_cost = 31 * 1000;  //по 1000р за 1кг
    float fluff_cost = fluff / 10;  //по 1р за 10г

    cout << "Вырученные деньги за продажу мяса: " << meat_cost << " рублей\n";
    cout << "Вырученные деньги за продажу пуха: " << fluff_cost << " рублей\n";

    float pigeon_cost = 10 * 75 * 31; //3/4 голубей закупается по 10р

    cout << "Сумма, потраченная на покупку голубей: " << pigeon_cost << " рублей\n";
    cout << "Общая выручка: " << fluff_cost + meat_cost - pigeon_cost << " рублей\n";
}