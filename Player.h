// Player.h

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include "Order.h"
#include "Inventory.h"


using namespace std;

class Player
{
    private:
        string name;
        Inventory user_inventory;
        int energy;
        vector <Order> all_orders;
        static const int momento_size = 10;
        string momentos_collected[momento_size];

    public:
        // Constructor
        Player(string user_name);
        
        // Getters and setters
        void setName(string user_name);
        string getName();

        void addOrder(Order order_);
        Order getOrder(int order_number);
        void setOrder(int index, Order order_);

        void setEnergy(int new_energy);
        int getEnergy();

        Inventory getInventory();
        void setInventory(Inventory inventory);

        int getNumOrders();
        void setNumOrders();

        void setMomento(string momento_name, int index);
        string getMomento(int index);

        // Player functions
        void printOutCurrentOrders();
        void printOutInventory();

        bool removeOrders(int order_number);
        void finalOutput();

};

#endif 