// Game.cpp

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#include <iostream>
#include <fstream>
#include <vector>
#include "Player.h"
#include "Order.h"
#include "Cats.h"
#include "Customers.h"
#include "Inventory.h"
#include "Game.h"

Game::Game()
{
    num_customers = 0;
    num_cats = 0;
    time = 800;
}
int Game::getCustomerSize()
{
    return cust_size;
}
int Game::getCatSize()
{
    return cat_size;
}

// split function
int split(string input_string, char seperator, string arr[], int arr_size)
{
    int count = 0;
    int length = input_string.length();
    if (input_string == "")
    {
        // empty string return 0
        return 0;
    }
    else
    {
        for (int i = 0; i < length; i++)
        {
            // if index isn't seperator add char to string array
            if (input_string[i] != seperator)
            {
                arr[count] += input_string[i];
            }
            // else move to next array index
            else if (input_string[i] == seperator)
            {
                count++;
            }
        }
        if (count >= arr_size)
        {
            // if more elements is greater than array size return -1
            return -1;
        }
        // return total in array
        return count + 1;
    }
}

// reads the cats.txt file and splits it into cat objects
// return true if cats read successfully
bool Game::readCat(string filename)
{
    string temp = "";
    int index = 0;
    int count = 0;
    string tempArr[2];
    bool valid = false;

    // open file and check if it is open
    ifstream in_file;
    in_file.open(filename);
    if (in_file.is_open())
    {
        if (num_cats == cat_size)
        {
            cout << "Already full" << endl;
            return valid;
        }
        else
        {
            while (getline(in_file, temp) && index < cat_size)
            {
                // splits the tempArr into sections
                count = split(temp, ',', tempArr, 2);
                cats_[index].setName(tempArr[0]);
                cats_[index].setMomentoName(tempArr[1]);
                num_cats++;
                index++;
                valid = true;
                // clears the array
                for (int i = 0; i < 2; i++)
                {
                    tempArr[i] = "";
                }
            }
            return valid;
        }
    }
    else
    {
        cout << "Couldn't open file" << endl;
        return valid;
    }
}
// 
// returns true if customers file read successful
bool Game::readCustomers(string filename)
{
    string temp = "";
    int index = num_customers;
    int count = 0;
    string tempArr[8];
    bool valid = false;

    ifstream in_file;
    in_file.open(filename);
    // checks if file is open
    if (in_file.is_open())
    {
        // makes sure more customers isn't added
        if (num_customers == cust_size)
        {
            cout << "Already full" << endl;
            return valid;
        }
        else
        {
            while (getline(in_file, temp) && index < cust_size)
            {
                // splits the tempArr into sections
                count = split(temp, ',', tempArr, 8);
                customers_[index].setName(tempArr[0]);
                customers_[index].setPatience(stoi(tempArr[1]));

                // seperates them into orders
                for (int i = 2; i < 8; i += 3)
                {
                    if (tempArr[i] != "-2")
                    {
                        Order temp_order(stoi(tempArr[i]), stoi(tempArr[i + 1]), stoi(tempArr[i + 2]));
                        customers_[index].addOrder(temp_order);
                        customers_[index].setNumOrders(1);
                    }
                }
                // clears the array
                for (int i = 0; i < 8; i++)
                {
                    tempArr[i] = "";
                }
                num_customers++;
                index++;
                valid = true;
            }
            return valid;
        }
    }
    else
    {
        cout << "File doesn't exist" << endl;
        return valid;
    }
}

// Prints out shop interface, and allows player to shop for ingredients
Inventory Game::shopInventory(Player player_)
{
    int input = 0;
    // assigns the inventory to player
    Inventory temp_inventory = player_.getInventory();
    double amount = temp_inventory.getTotalMoney();

    // cout menu prompting what they want to buy
    do
    {
        if (amount <= 0)
        {
            cout << "Sorry, you don't have enough money." << endl;
            return temp_inventory;
        }
        else
        {
            cout << "=====Shop Menu====="
                << "\nTotal Money: " << amount 
                 << "\n1. Boba"
                 << "\n2. Milk"
                 << "\n3. Tea"
                 << "\n4. Cups"
                 << "\n5. Exit" << endl;
            cin >> input;
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Please enter a valid menu option (1-5)." << endl;
                cin >> input;
            }

            switch (input)
            {
            case 1:
                // do-while loops input validate
                do
                {
                    // makes sure player has enough money
                    if (amount <= 0)
                    {
                        cout << "Sorry, you don't have enough money." << endl;
                        temp_inventory.setTotalMoney(amount);
                        return temp_inventory;
                    }
                    else
                    {
                        cout << "=====Boba Menu====="
                            << "\n*$1 for each*"
                             << "\n1. Pearl"
                             << "\n2. Popping"
                             << "\n3. Jelly"
                             << "\n4. Crystal"
                             << "\n5. Exit" << endl;
                        cin >> input;
                        while(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Please enter a valid menu option (1-5)." << endl;
                            cin >> input;
                        }
                        switch (input)
                        {
                        case 1:
                            // comments here are the same throughout
                            cout << "How many pearl bobas would you like to buy?" << endl;
                            cin >> input;
                            // adds to inventory
                            temp_inventory.setBoba(0, input);
                            // subtracts from total amount of money
                            amount -= (temp_inventory.getBobaPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            // prints amount left
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 2:
                            cout << "How many popping bobas would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setBoba(1, input);
                            amount -= (temp_inventory.getBobaPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 3:
                            cout << "How many jelly bobas would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setBoba(2, input);
                            amount -= (temp_inventory.getBobaPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 4:
                            cout << "How many crystal bobas would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setBoba(3, input);
                            amount -= (temp_inventory.getBobaPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 5:
                            cout << "Exiting Boba Shop!" << endl;
                            input = 0;
                            break;
                        default:
                            cout << "Oops! Invalid number, please enter numbers 1-5." << endl;
                            break;
                        }
                    }
                } while (input != 0 && amount >= 0);
                break;
            case 2:
                do
                {
                    if (amount < 0)
                    {
                        cout << "Sorry, you don't have enough money." << endl;
                        temp_inventory.setTotalMoney(amount);
                        return temp_inventory;
                    }
                    else
                    {
                        cout << "=====Milk Menu====="
                          << "\n*$2 for each*"
                             << "\n1. Whole"
                             << "\n2. Almond"
                             << "\n3. Coconut"
                             << "\n4. Oat"
                             << "\n5. Exit" << endl;
                        cin >> input;
                        while(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Please enter a valid menu option (1-5)." << endl;
                            cin >> input;
                        }
                        switch (input)
                        {
                        case 1:
                            cout << "How many whole milks would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setMilk(0, input);
                            amount -= (temp_inventory.getMilkPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 2:
                            cout << "How many almond milks would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setMilk(1, input);
                            amount -= (temp_inventory.getMilkPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 3:
                            cout << "How many coconut milks would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setMilk(2, input);
                            amount -= (temp_inventory.getMilkPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 4:
                            cout << "How many oat milks would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setMilk(3, input);
                            amount -= (temp_inventory.getMilkPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 5:
                            cout << "Exiting Milk Shop!" << endl;
                            input = 0;
                            break;
                        default:
                            cout << "Oops! Invalid number, please enter numbers 1-5." << endl;
                            break;
                        }
                    }

                } while (input != 0 && amount >= 0);
                break;
            case 3:
                do
                {
                    if (amount <= 0)
                    {
                        cout << "Sorry, you don't have enough money." << endl;
                        temp_inventory.setTotalMoney(amount);
                        return temp_inventory;
                    }
                    else 
                    {
                        cout << "=====Tea Menu====="
                         << "\n*$2 for each*"
                         << "\n1. Black Tea"
                         << "\n2. Thai"
                         << "\n3. Brown Sugar"
                         << "\n4. Matcha"
                         << "\n5. Exit" << endl;
                        cin >> input;
                        while(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Please enter a valid menu option (1-5)." << endl;
                            cin >> input;
                        }
                        switch (input)
                        {
                        case 1:
                            cout << "How many black teas would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setTea(0, input);
                            amount -= (temp_inventory.getTeaPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 2:
                            cout << "How many thai teas would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setTea(1, input);
                            amount -= (temp_inventory.getTeaPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 3:
                            cout << "How many brown sugar teas would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setTea(2, input);
                            amount -= (temp_inventory.getTeaPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 4:
                            cout << "How many matcha teas would you like to buy?" << endl;
                            cin >> input;
                            temp_inventory.setTea(3, input);
                            amount -= (temp_inventory.getTeaPrice() * input);
                            temp_inventory.setTotalItems(input);
                            temp_inventory.setTotalMoney(amount);
                            cout << "You have $" << amount << " left." << endl;
                            break;
                        case 5:
                            cout << "Exiting Tea Shop!" << endl;
                            input = 0;
                            break;
                        default:
                            cout << "Oops! Invalid number, please enter numbers 1-5." << endl;
                            break;
                        }
                    }
                    
                } while (input != 0 && amount >=0);
                break;
            case 4:
                do
                {
                    if (amount <= 0)
                    {
                        cout << "Sorry, you don't have enough money." << endl;
                        temp_inventory.setTotalMoney(amount);
                        return temp_inventory;
                    }
                    else
                    {
                        cout << "How many cups would you like to buy? (Enter 0 to exit)" << endl;
                        cin >> input;
                        while(cin.fail())
                        {
                            cin.clear();
                            cin.ignore(1000, '\n');
                            cout << "Please enter a valid input." << endl;
                            cin >> input;
                        }
                        if (input == 0)
                        {
                          cout << "Exiting Cup Shop!" << endl;
                        }
                        else if (input < 0)
                        {
                          cout << "Oops! Invalid number, please enter numbers 0 or greater." << endl;
                        }
                        else 
                        {
                          temp_inventory.setCup(input);
                          amount -= (temp_inventory.getCupPrice() * input);
                          temp_inventory.setTotalItems(input);
                          temp_inventory.setTotalMoney(amount);
                          cout << "You have $" << amount << " left." << endl;
                        }   
                    }
                } while (input > 0 && amount > 0);
                break;
            case 5:
                temp_inventory.setTotalMoney(amount);
                cout << "Exiting Shop!" << endl;
                break;
            default:
                cout << "Oops! Invalid number, please enter numbers 1-5." << endl;
                break;
            }
        }

    } while (input != 5 && amount >= 0);
    return temp_inventory;
}

// calculates the tips based on patience level
double Game::tipsGiven(int patience, int price)
{
    double tip = 0;
    // if patience is still 100 get 50% tip based on what customers total
    // same format throughout with different tip percentage
    if (patience == 100)
    {
        tip = price * .5;
    }
    else if (patience < 100 && patience >= 80)
    {
        tip = price * .2;
    }
    else if (patience < 80 && patience >= 60){
        tip = price * .15;
    }
    else {
        tip = 0;
    }
    return tip;
}

// setters and getters
Cats Game::getCats(int index)
{
    return cats_[index];

}
void Game::setCats(Cats cat_, int index)
{
    cats_[index] = cat_;
}
Customers Game::getCustomers(int index)
{
    return customers_[index];
}
void Game::setCustomers(Customers customer_, int index)
{
    customers_[index] = customer_;
}
int Game::getTime()
{
    return time;
}

// time changes based on the players movements
int Game::changeTime(int numMoves)
{
  // for every 25 moves, the time goes up an hour
    if (numMoves % 25 == 0 && numMoves != 0)
    {
        time += 100;

        return time;
    }

    return time;
}
