#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <fstream>
using namespace std;


struct recipe {
    char s_ingredient[50];
    int s_need_quantity;
    int s_quantiti_on_storage;
    int s_cost;
    int s_shelf_life;
    int s_date_of_purchase;
    int s_month_of_purchase;
};

void print(recipe* f, int count);
int find_normal_ingredient(recipe* f, int day, int month, int count, bool bad_cost);
void print_menu();
int load(const char* file, recipe* a);
void enough(recipe* f, int count);
void setData(const char* fileName, int size);


int main()
{
    setlocale(LC_ALL, "RUS");

    recipe f[15];
    int count = 0;
    int c = 0;
    char flower[50] = {};
    int day;
    int month;
    while (true)
    {
        print_menu();
        char ch = _getch();
        switch (ch)
        {
        case '1':
            count = load("TXT.txt", f);
            if (count < 0)
            {
                return 0;
            }
            break;
        case '2':
            print(f, count);
            break;
        case '3':
            cout << "Enter num: ";
            cin >> c;
            setData("TXT.txt", c);
            break;
        case '4':
            cout << "Enter date: ";
            cin >> day;
            for (; day > 30;) {
                cin >> day;
            }
            cin >> month;
            for (; month > 12;) {
                cin >> month;
            }
            cout << find_normal_ingredient(f, day, month, count, 1);
            break;
        case '5':
            cout << "Enter date: ";
            cin >> day;
            for (; day > 30;) {
                cin >> day;
            }
            cin >> month;
            for (; month > 12;) {
                cin >> month;
            }
            cout << find_normal_ingredient(f, day, month, count, 0);
            break;
        case '6':
            enough(f, count);
            break;
        case '0':
            return 0;
            break;
        default:
            cout << "Noname command!!!" << endl;
        }
        cout << "..." << endl;
        _getch();
    }

}
void print(recipe* f, int count)
{
    for (int i = 0; i < count; i++)
    {
        cout << "recipe #" << i + 1 << endl;
        cout << "ingredient name " << f[i].s_ingredient << endl;
        cout << "need " << f[i].s_need_quantity << endl;
        cout << "on storage " << f[i].s_quantiti_on_storage << endl;
        cout << "cost " << f[i].s_cost << endl;
        cout << "shelf life  " << f[i].s_shelf_life << endl;
        cout << "date of purchase " << f[i].s_date_of_purchase << '.' << f[i].s_month_of_purchase << endl;
        cout << endl;
    }
}
int find_normal_ingredient(recipe* f, int day, int month, int count, bool bad_cost) {
    int quantity_normal = 0;
    int bad_cost_sum = 0;
    int end = 0;
    for (int i = 0; i < count; i++) {
        if (f[i].s_date_of_purchase + (30 * f[i].s_month_of_purchase) + f[i].s_shelf_life <= day + 30 * month) {
            bad_cost_sum += f[i].s_cost * f[i].s_quantiti_on_storage;
        }
        else end += (quantity_normal++)*f[i].s_quantiti_on_storage;
    }
    if (bad_cost == 0)
        return end;
    else
        return bad_cost_sum;
}
void print_menu()
{
    cout << endl;
    cout << "1 - Downloading data" << endl;
    cout << "2 - Output data" << endl;
    cout << "3 - Input new data" << endl;
    cout << "4 - Storage bad cost" << endl;
    cout << "5 - Storage normal" << endl;
    cout << "6 - Are there enough supplies? " << endl;
    cout << "0 - Exit" << endl;
    cout << "Enter your answer: ";
}
int load(const char* file, recipe* a)
{
    ifstream f;
    f.open(file);
    if (!f.is_open())
    {
        cout << "File is not open: " << file << endl;
        return -1;
    }

    char buff[100];
    f.getline(buff, 99);
    int count = atoi(buff);

    for (int i = 0; i < count; i++)
    {
        if (f.eof())
        {
            f.close();
            return -1;
        }
        f.getline(a[i].s_ingredient, 49);

        char need_quantity[49] = {};
        f.getline(need_quantity, 49);
        a[i].s_need_quantity = atoi(need_quantity);

        char quantiti_on_storage[49] = {};
        f.getline(quantiti_on_storage, 49);
        a[i].s_quantiti_on_storage = atoi(quantiti_on_storage);

        char cost[49] = {};
        f.getline(cost, 49);
        a[i].s_cost = atoi(cost);

        char shelf_life[49] = {};
        f.getline(shelf_life, 49);
        a[i].s_shelf_life = atoi(shelf_life);

        char date_of_purchase[49] = {};
        f.getline(date_of_purchase, 49);
        a[i].s_date_of_purchase = atoi(date_of_purchase);

        char month_of_purchase[49] = {};
        f.getline(month_of_purchase, 49);
        a[i].s_month_of_purchase = atoi(month_of_purchase);
    }
    f.close();
    return count;
}
void enough(recipe* f, int count) {
    for (int i = 0; i < count; i++) {
        cout << "Recipe #" << i + 1 << ": ";
        if (f[i].s_need_quantity > f[i].s_quantiti_on_storage) {
            cout << "NO" << endl;
        }
        else
            cout << "Yes" << endl;
    }
}

void setData(const char* fileName, int size) {
    recipe* dataBase = new recipe[size];
    std::ofstream file;
    file.open(fileName, ios::app);
    if (file.is_open()) {
        cout << "Enter details: " << std::endl;
        for (int i = 0; i < size; i++) {

            cout << "Enter ingredient: " << std::endl;
            std::cin >> dataBase[i].s_ingredient;

            std::cout << "Enter need quantity: " << std::endl;
            std::cin >> dataBase[i].s_need_quantity;
            for (; dataBase[i].s_need_quantity < 0 || dataBase[i].s_need_quantity> 100;) {
                std::cout << "Enter need quantity: " << std::endl;
                std::cin >> dataBase[i].s_need_quantity;
            }

            std::cout << "Enter quantity on storage: " << std::endl;
            std::cin >> dataBase[i].s_quantiti_on_storage;
            for (; dataBase[i].s_quantiti_on_storage < 0 || dataBase[i].s_quantiti_on_storage > 10000;) {
                std::cout << "Enter quantity on storage: " << std::endl;
                std::cin >> dataBase[i].s_quantiti_on_storage;
            }

            std::cout << "Enter cost: " << std::endl;
            std::cin >> dataBase[i].s_cost;
            for (; dataBase[i].s_cost < 0 || dataBase[i].s_cost > 10000;) {
                std::cout << "Enter cost: " << std::endl;
                std::cin >> dataBase[i].s_cost;
            }

            std::cout << "Enter shelf life: " << std::endl;
            std::cin >> dataBase[i].s_shelf_life;
            for (; dataBase[i].s_shelf_life <= 0 || dataBase[i].s_shelf_life > 365;) {
                std::cout << "Enter shelf life: " << std::endl;
                std::cin >> dataBase[i].s_shelf_life;
            }

            std::cout << "Enter date: " << std::endl;
            std::cin >> dataBase[i].s_date_of_purchase;
            for (; dataBase[i].s_date_of_purchase < 0 || dataBase[i].s_date_of_purchase > 30;) {
                std::cout << "Enter date: " << std::endl;
                std::cin >> dataBase[i].s_date_of_purchase;
            }

            std::cout << "Enter month: " << std::endl;
            std::cin >> dataBase[i].s_month_of_purchase;
            for (; dataBase[i].s_month_of_purchase < 0 || dataBase[i].s_month_of_purchase> 30;) {
                std::cout << "Enter month: " << std::endl;
                std::cin >> dataBase[i].s_month_of_purchase;
            }

            file << dataBase[i].s_ingredient << std::endl
                << dataBase[i].s_need_quantity << std::endl
                << dataBase[i].s_quantiti_on_storage << std::endl
                << dataBase[i].s_cost << std::endl
                << dataBase[i].s_shelf_life << std::endl
                << dataBase[i].s_date_of_purchase << std::endl
                << dataBase[i].s_month_of_purchase << std::endl;
        }
        file.close();
    }
    else {
        std::cout << "Fatal error! Try again.." << std::endl;
    }
    delete[]dataBase;
}
