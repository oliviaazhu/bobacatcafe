// Cats.h

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#ifndef CATS_H
#define CATS_H

#include <iostream>
#include "Player.h"
#include "Inventory.h"

using namespace std;

class Cats
{
    private:
        string name;
        string momento_name;
        int momento_count;
        bool met;
        int met_count; 
        bool received_momento;

    public:
        // Constructors
        Cats();
        Cats(string cat_name, string momento_name_);

        // Getters and Setters
        string getName();
        void setName(string cat_name);

        string getMomentoName();
        void setMomentoName(string new_momento_name);

        int getMomentoCount();
        void setMomentoCount(int new_momento_count);

        int getMetCount();
        void setMetCount(int met_count_);

        bool getMomentoReceived();
        void setMomentoReceived(bool momento_recieved_);

        // Cat functions
        bool metCat();
        bool guessingGame();
        Inventory trip(Player player_);
        Inventory bring_item(Player player_);
        bool quiz();

};

#endif 
