// Customers.cpp

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#include <iostream>
#include <vector>
#include "Customers.h"

using namespace std;

// Constructors
Customers::Customers()
{
    name = "";
    patience = 0;
    tips = 0;
    num_orders = 0;
    order_taken = false;
}
Customers::Customers(string newName, int newPatience, Order newOrders[3], int newNumOrders)
{
    name = newName;
    patience = newPatience;
    tips = 0;
    order_taken = false;
    for (int i = 0; i < 3; i++)
    {
        if(newOrders[i].getTea() == -1)
        {
            i = 3;
        }
        else
        {
            orders.push_back(newOrders[i]);
        }
    }
    num_orders = newNumOrders;
}

// Getters and setters
string Customers::getName()
{
    return name;
}
void Customers::setName(string newName)
{
    name = newName;
}

int Customers::getNumOrders()
{
    return num_orders;
}
void Customers::setNumOrders(int new_num_orders)
{
    num_orders += new_num_orders;
}

int Customers::getPatience()
{
    return patience;
}
// subtracts or adds the value of customer patience
void Customers::setPatience(int newPatience)
{
    patience += newPatience;
}

/**
 * Algorithim: Sets the customers patience based on the number of turns
 * 1. Accepts the number of turns 
 * 2. If 20 turns have passed, and the customer is in the store, subtract 5 from their patience
 * Parameters: numMoves(int)
 * Returns: void
 */
void Customers::setPatienceTurns(int numMoves)
{
    if (numMoves % 20 == 0 && numMoves != 0 && patience != 0)
    {
        patience -= 5;
    }
}

int Customers::getTip()
{
    return tips;
}
void Customers::setTip(int amount)
{
    tips = amount;
}

void Customers::addOrder(Order order_)
{
    orders.push_back(order_);
}

Order Customers::getOrder(int index)
{
    return orders.at(index);
}

void Customers::setOrder(int index, Order order_)
{
    orders.at(index) = order_;
}

void Customers::setOrderTaken()
{
    order_taken = true;
}

bool Customers::getOrderTaken()
{
    return order_taken;
}
