#include <iostream>
#include <random>
#include <time.h>
#include <stdio.h>
using namespace std;

struct Pigeon
{
    int meat = 225 - rand() % 50;
    int fluff = 125 - rand() % 50;
};

void addPigeon (Pigeon*& arrPigeons, int& amount, Pigeon pigeon)
{
    Pigeon* temp = new Pigeon[amount + 1];

    for (int i = 0; i < amount; i++)
        temp[i] = arrPigeons[i];
    temp[amount] = pigeon;
    
    delete[] arrPigeons;
    arrPigeons = temp;
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

void first_pigeon(Pigeon*& arrPigeons, Pigeon pigeon)
{
    Pigeon* temp = new Pigeon[1];
    
    temp[0] = pigeon;
    delete[] arrPigeons;
    arrPigeons = temp;
}

void create_pigeons(Pigeon*& arrPigeons, int& amount)
{
    int _amount = amount - 1;

    for (int i = 0; i < _amount; i++)
    {
        Pigeon* temp = new Pigeon[amount + 1];

        delete[] arrPigeons;
        arrPigeons = temp;
        amount++;
    }
}

void month(Pigeon*& arrPigeons, int& amount, int& shashlik, int& fluff, int weight_reduction, int fluff_reduction, int growth, int need_meat)
{
    fluff = 0;

    for (int i = 0; i < 7; i++)    //неделя
    {
        for (int j = 0; j < amount; j++)
        {
            arrPigeons[j].meat += weight_reduction;
            arrPigeons[j].fluff += fluff_reduction;
        }

        for (int j = 0; j < growth; j++)
        {
            Pigeon new_pigeon;
            addPigeon(arrPigeons, amount, new_pigeon);
        }
        
        if (shashlik < need_meat)
            while (shashlik < need_meat)
            {
                shashlik += arrPigeons[0].meat;
                fluff += arrPigeons[0].fluff;
                killPigeon(arrPigeons, amount);
            }
        else
            shashlik -= need_meat;
    }
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "ru");

    Pigeon* arrPigeons = new Pigeon[0];

    int amount;
    cout << "Введите начальное количество голубей\n";
    cin >> amount;

    Pigeon a;
    first_pigeon(arrPigeons, a);
    create_pigeons(arrPigeons, amount);

    int shashlik = 0;
    int fluff = 0;
    int meat_cost, fluff_cost;
    cout << "Введите стоимость мяса и пуха (за грамм)\n";
    cin >> meat_cost >> fluff_cost;
    int weight_reduction, fluff_reduction;
    cout << "Введите, на сколько граммов увеличивается масса голубей и масса их пуха в день\n";
    cin >> weight_reduction >> fluff_reduction;
    int growth;
    cout << "Введите, на сколько увеличивается количество голубей в день\n";
    cin >> growth;
    int need_meat;
    cout << "Введите, сколько мяса надо тратить в день на шашлык (в граммах)\n";
    cin >> need_meat;
    int meat_in_money, fluff_in_money;
    FILE* file;

    if (fopen_s(&file, "Z:\\Desktop\\programs\\march_21-master\\income.txt", "w") != NULL)
        cout << "The file cannot be opened";
    else
        for (int i = 1; i < 5; i++)
        {
            month(arrPigeons, amount, shashlik, fluff, weight_reduction, fluff_reduction, growth, need_meat);
            meat_in_money = need_meat * meat_cost;
            fluff_in_money = fluff * fluff_cost;
            fprintf(file, "%s", "Неделя ");
            fprintf(file, "%d", i);
            fprintf(file, "%s", "\n");
            fprintf(file, "%s", "Количество голубей в конце недели: ");
            fprintf(file, "%d", amount);
            fprintf(file, "%s", "\n");
            fprintf(file, "%s", "Оставшееся количество шашлыка в граммах в конце недели: ");
            fprintf(file, "%d", shashlik);
            fprintf(file, "%s", "\n");
            fprintf(file, "%s", "Количество пуха в граммах в конце недели: ");
            fprintf(file, "%d", fluff);
            fprintf(file, "%s", "\n");
            fprintf(file, "%s", "Вырученные деньги за продажу мяса в рублях: ");
            fprintf(file, "%d", meat_in_money);
            fprintf(file, "%s", "\n");
            fprintf(file, "%s", "Вырученные деньги за продажу пуха в рублях: ");
            fprintf(file, "%d", fluff_in_money);
            fprintf(file, "%s", "\n");
            fprintf(file, "%s", "Общая выручка в рублях: ");
            fprintf(file, "%d", meat_in_money + fluff_in_money);
            fprintf(file, "%s", "\n\n");
        }
    fclose(file);
}