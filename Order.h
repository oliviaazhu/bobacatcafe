// Order.h

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3 - Class Skeleton

#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include "Inventory.h"

using namespace std;

class Player;
class Order
{
    private:
        int order_[3];
        const static constexpr double order_price = 8;
        bool made;
        int order_number;
        string order_name;
    public:
        // Constructors
        Order();
        Order(int boba, int milk, int tea);

        // Getters and setters
        void setBoba(int boba);
        int getBoba();
        void setMilk(int milk);
        int getMilk();
        void setTea(int tea);
        int getTea();
        double getPrice();
        bool getMade();
        int getOrderNum();
        void setOrderNum(int order_num_);
        string getOrderName();
        void setOrderName(string order_name_);

        // Order functions
        Inventory makeOrder(Player player);
};

#endif
