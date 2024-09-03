//Player.cpp 

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3 

#include <iostream>
#include <vector>
#include <fstream>
#include "Player.h"
#include "Inventory.h"
#include "Order.h"

using namespace std;

// Constructor
Player::Player(string user_name)
{
    name = user_name;
    energy = 100;
    for(int i = 0; i < user_inventory.getSize(); i++)
    {
        user_inventory.setBoba(i, 0);
        user_inventory.setMilk(i,0);
        user_inventory.setTea(i,0);
        user_inventory.setCup(0);

    } 
}

// Getters and setters
void Player::setName(string user_name)
{
    name = user_name;
}
string Player::getName()
{
    return name;
}
void Player::addOrder(Order order_)
{
    all_orders.push_back(order_);
}
Order Player::getOrder(int order_number)
{
    return all_orders.at(order_number);
}
void Player::setOrder(int index, Order order_)
{
    all_orders.at(index) = order_;
}
void Player::setEnergy(int new_energy)
{
    energy += new_energy;
}
int Player::getEnergy()
{
    return energy;
}
Inventory Player::getInventory()
{
    return user_inventory;
}
void Player::setInventory(Inventory inventory_)
{
    user_inventory = inventory_;
}
int Player::getNumOrders()
{
    return all_orders.size();
}
void Player::setMomento(string momento_name, int index)
{
    momentos_collected[index] = momento_name;
}
string Player::getMomento(int index)
{
    return momentos_collected[index];
}

// prints the orders the player currently has (completed or not)
void Player::printOutCurrentOrders()
{
    cout << "=== Orders === " << endl;
    cout << endl;
  // for loop goes through each of the orders present
    for(int i = 0; i < all_orders.size(); i++)
    {
        Order temp_order = all_orders.at(i);
        cout << "Order #" << temp_order.getOrderNum() << endl;
        cout << "Name: " << temp_order.getOrderName() << endl;
        // prints status of orders made or not
        cout << "Status: ";
        if(temp_order.getMade() == true)
        {
            cout << "Made" << endl;
        }
        else
        {
            cout << "Not made" << endl;
        }
        // shows what type of boba the customer ordered
        if (temp_order.getBoba() == 0)
        {
            cout << "Pearl boba, ";
        }
        else if (temp_order.getBoba() == 1)
        {
            cout << "Popping boba, ";
        }
        else if (temp_order.getBoba() == 2)
        {
            cout << "Jelly, ";
        }
        else if (temp_order.getBoba() == 3)
        {
            cout << "Crystal boba, ";
        }
        else
        {
            cout << "No boba, ";
        }
      
        // shows what type of milk the customer ordered
        if (temp_order.getMilk() == 0)
        {
            cout << "whole milk, ";
        }
        else if (temp_order.getMilk() == 1)
        {
            cout << "almond milk, ";
        }
        else if (temp_order.getMilk() == 2)
        {
            cout << "coconut milk, ";
        }
        else if (temp_order.getMilk() == 3)
        {
            cout << "oat milk, ";
        }
        else
        {
            cout << "no milk, ";
        }
        // shows what type of tea the customer ordered
        if (temp_order.getTea() == 0)
        {
            cout << "black tea" << endl;
        }
        else if (temp_order.getTea() == 1)
        {
            cout << "thai tea" << endl;
        }
        else if (temp_order.getTea() == 2)
        {
            cout << "brown sugar tea" << endl;
        }
        else if (temp_order.getTea() == 3)
        {
            cout << "matcha" << endl;
        }
        else
        {
            cout << "no tea" << endl;
        }
        cout << endl;
    }
}

//prints the current inventory of the player
void Player::printOutInventory()
{
    cout << "=== Player Stats ====" << endl;
    cout << endl;
    cout << "Name: " << name << endl;
    cout << "Energy Level: " << energy << endl;
    cout << "=== Inventory === " << endl;
    cout << "Money: " << user_inventory.getTotalMoney() << endl;
    cout << "Total Items: "<< user_inventory.getTotalItems() << endl;
    cout << endl;
    cout << "Boba: " << endl;
    cout << "Pearl: " << user_inventory.getBoba(0) << endl;
    cout << "Popping: " << user_inventory.getBoba(1) << endl;
    cout << "Jelly: " << user_inventory.getBoba(2) << endl;
    cout << "Crystal: " << user_inventory.getBoba(3) << endl;
    cout << endl;
    cout << "Milk: " << endl;
    cout << "Whole milk: " << user_inventory.getMilk(0) << endl;
    cout << "Almond milk: " << user_inventory.getMilk(1) << endl;
    cout << "Coconut milk: " << user_inventory.getMilk(2) << endl;
    cout << "Oat milk: " << user_inventory.getMilk(3) << endl;
    cout << endl;
    cout << "Tea: " << endl;
    cout << "Black tea: " << user_inventory.getTea(0) << endl;
    cout << "Thai tea: " << user_inventory.getTea(1) << endl;
    cout << "Brown sugar: " << user_inventory.getTea(2) << endl;
    cout << "Matcha: " << user_inventory.getTea(3) << endl;
    cout << endl;
    cout << "Cups: " << user_inventory.getCup() << endl;

}

// removes the order from order list after giving it to the customer
bool Player::removeOrders(int order_number)
{
  // for loops through all the orders and removes the one with same index
    for(int i = 0; i < all_orders.size(); i++)
    {
        Order temp_order = all_orders.at(i);
        if(order_number == temp_order.getOrderNum())
        {
            all_orders.erase(all_orders.begin() + i);
            return true;
        }
    }
    return false;
}

// out files the players results
void Player::finalOutput()
{
    int count = 0;
    // prints results into results.txt
    ofstream out_file("results.txt");
    out_file << "====End Results====" << endl;
    out_file << "Energy Left: " << energy << endl;
    out_file << "Total Money: " << user_inventory.getTotalMoney() << endl;
    out_file << "Total Items Collected: " << user_inventory.getTotalItems() << endl;
    // finds the size of total momentos collected
    for (int i = 0; i < momento_size; i ++)
    {
        if (momentos_collected[i]!= "")
        {
            count++;
        }
    }

    out_file << "Total Momentos Collected: " << count << endl;
    int num[count];
    string temp = "";
    int tempNum = 0;
    int index[count];
    int tempIndex = 0;
    // stores the first letter of each moment and their index
    for (int i = 0; i < count; i ++)
    {
        temp = momentos_collected[i];
        num[i] = static_cast<int>(temp[0]);
        index[i]=i;
    }
    // bubble sort the letters into alphabetical order
    for (int i = 0; i < count; i++)
    {
        for (int j = i +1; j < count; j++)
        {
            if (num[i] > num[j])
            {
                tempNum = num[i];
                num[i]= num[j];
                num[j] = tempNum;
                tempIndex = index[i];
                index[i]= index[j];
                index[j]=tempIndex;
            }
        }
    }
  // prints out the the momentos in alphabetical order
    for (int i = 0; i < count; i ++)
    {
        out_file << momentos_collected[index[i]] << endl;
    }
    return;
}

