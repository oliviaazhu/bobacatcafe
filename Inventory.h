// Inventory.h

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#ifndef INVENTORY_H
#define INVENTORY_H

#include <iostream>

using namespace std;

class Inventory
{
private:





























    static constexpr double boba_price = 1.0;
    static constexpr double cup_price = 1.0;
    static constexpr double milk_price = 2.0;
    static constexpr double tea_price = 2.0;
    static constexpr int size = 4;
    int boba[size];
    int milk[size];
    int tea[size];
    int cup;
    double total_money;
    int total_item;

public:
    // Constructors
    Inventory();
    Inventory(int newBoba[], int newMilk[], int newTea[], int newCup);

    // Getters and setters
    int getBoba(int index);
    void setBoba(int index, int amount);

    int getMilk(int index);
    void setMilk(int index, int amount);

    int getTea(int index);
    void setTea(int index, int amount);

    int getCup();
    void setCup(int amount);

    double getTotalMoney();
    void setTotalMoney(double amount);

    double getSize();
    double getBobaPrice();
    double getCupPrice();
    double getMilkPrice();
    double getTeaPrice();

    int getTotalItems();
    void setTotalItems(int num_items);
};

#endif
