// Order.cpp

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#include <iostream>
#include "Order.h"
#include "Player.h"
#include "Inventory.h"

using namespace std;

// Constructors
Order::Order()
{
	order_[0] = -2;
	order_[1] = -2;
	order_[2] = -2;
	made = false;
}
Order::Order(int boba, int milk, int tea)
{
	order_[0] = boba;
	order_[1] = milk;
	order_[2] = tea;
	made = false;
}

// Getters and setters
void Order::setBoba(int boba)
{
	order_[0] = boba;
}
int Order::getBoba()
{
	return order_[0];
}
void Order::setMilk(int milk)
{
	order_[1] = milk;
}
int Order::getMilk()
{
	return order_[1];
}
void Order::setTea(int tea)
{
	order_[2] = tea;
}
int Order::getTea()
{
	return order_[2];
}
double Order::getPrice()
{
	return order_price;
}
bool Order::getMade()
{
	return made;
}
int Order::getOrderNum()
{
	return order_number;
}
void Order::setOrderNum(int order_num_)
{
	order_number = order_num_;
}
string Order::getOrderName()
{
	return order_name;
}
void Order::setOrderName(string order_name_)
{
	order_name = order_name_;
}

// Order functions

/**
 * Algorithim: Makes an order
 * 1. Accepts a player
 * 2. Declares variables.
 * 3. Checks if order has already been made 
 * 4. Prints out the details of the order that is currently being made
 * 5. Allows user to select the ingredients in the order
 * 6. If the ingredients match the order, guide the user through order-making process. Otherwise, reselect ingredients until they are right.
 * 7. Return the inventory
 * Parameters: player_ (Player)
 * Returns: temp_inventory (Inventory)
 */
Inventory Order::makeOrder(Player player_)
{
	cout << "=== Kitchen ===" << endl;
	cout << endl;
	Inventory temp_inventory = player_.getInventory();
	if (made == true)
	{
		cout << "This order has already been made." << endl;
		return temp_inventory;
	}
	else if (temp_inventory.getBoba(order_[0]) >= 1 && temp_inventory.getMilk(order_[1]) >= 1 && temp_inventory.getTea(order_[2]) >= 1 && temp_inventory.getCup() >= 1 && made == false)
	{
		string boba_input;
		string tea_input;
		string milk_input;
		int boba_choice;
		int milk_choice;
		int tea_choice;
		char try_again_choice;
		Inventory temp_inventory = player_.getInventory();

		cout << "You are currently making order #" << order_number << " for " << order_name << ": ";
		if (order_[0] == 0)
        {
            cout << "Pearl boba, ";
        }
        else if (order_[0] == 1)
        {
            cout << "Popping boba, ";
        }
        else if (order_[0] == 2)
        {
            cout << "Jelly, ";
        }
        else if (order_[0] == 3)
        {
            cout << "Crystal boba, ";
        }
        else
        {
            cout << "No boba, ";
        }

        if (order_[1] == 0)
        {
            cout << "whole milk, ";
        }
        else if (order_[1] == 1)
        {
            cout << "almond milk, ";
        }
        else if (order_[1] == 2)
        {
            cout << "coconut milk, ";
        }
        else if (order_[1] == 3)
        {
            cout << "oat milk, ";
        }
        else
        {
            cout << "no milk, ";
        }

        if (order_[2] == 0)
        {
            cout << "black tea" << endl;
        }
        else if (order_[2] == 1)
        {
            cout << "thai tea" << endl;
        }
        else if (order_[2] == 2)
        {
            cout << "brown sugar tea" << endl;
        }
        else if (order_[2] == 3)
        {
            cout << "matcha" << endl;
        }
        else
        {
            cout << "no milk" << endl;
        }
        cout << endl;

		do
		{
			boba_choice = -2;
			milk_choice = -2;
			tea_choice = -2;

			do
			{
				cout << "Let's make an order! Select your boba type: No Boba (-1), Pearl(0), Popping(1), Jelly(2), Crystal(3)" << endl;
				cin >> boba_choice;

				if(boba_choice != 0 && boba_choice != 1 && boba_choice != 2 && boba_choice != 3 && boba_choice != -1)
				{
					cout << "Please enter a valid choice (-1-3)." << endl;
				}

			}while(boba_choice != 0 && boba_choice != 1 && boba_choice != 2 && boba_choice != 3 && boba_choice != -1);

			do
			{
				cout << "Select your milk type: No milk (-1), Whole milk(0), Almond milk(1), Coconut milk(2), Oat milk(3)." << endl;
				cin >> milk_choice;

				if(milk_choice != 0 && milk_choice != 1 && milk_choice != 2 && milk_choice != 3 && milk_choice != -1)
				{
					cout << "Please enter a valid choice (-1-3)." << endl;
				}
			}while(milk_choice != 0 && milk_choice != 1 && milk_choice != 2 && milk_choice != 3 && milk_choice != -1);

			do
			{
				cout << "Select your tea type: No tea(-1), Black tea(0), Thai tea(1), Brown sugar(2), Matcha(3)." << endl;
				cin >> tea_choice;

				if(tea_choice != 0 && tea_choice != 1 && tea_choice != 2 && tea_choice != 3 && tea_choice != -1)
				{
					cout << "Please enter a valid choice (-1-3)." << endl;
				}

			}while(tea_choice != 0 && tea_choice != 1 && tea_choice != 2 && tea_choice != 3 && tea_choice != -1);	

			if (boba_choice != order_[0] || milk_choice != order_[1] || tea_choice != order_[2])
			{
			
				cout << "These ingredients don't match the order, you were trying to make. Let's try selecting them again" << endl;
			}


		} while (boba_choice != order_[0] || milk_choice != order_[1] || tea_choice != order_[2]);
		
		do
		{
			if(boba_choice >= 0)
			{
				if(temp_inventory.getBoba(boba_choice) <= 0)
				{
					cout << "This order doesn't seem to be going too well. You ran out of the required ingredients. Get some more and try again!" << endl;
					return temp_inventory;
				}
			}

			cout << "Let's add the boba! Type in the letter o five times." << endl;
			cin >> boba_input;
			
			if (boba_input != "ooooo")
			{
				cout << "You didn't quite make the boba right. Try again." << endl;
			}
			temp_inventory.setBoba(boba_choice, -1);
			temp_inventory.setTotalItems(-1);

		} while (boba_input != "ooooo");

		do
		{
			if(tea_choice >= 0)
			{
				if(temp_inventory.getTea(tea_choice) <= 0)
				{
					cout << "This order doesn't seem to be going too well. You ran out of the required ingredients. Get some more and try again!" << endl;
					return temp_inventory;
				}
		
			}

			cout << "Let's make the tea! Make a circle using your keyboard (uhnmk)." << endl;
			cin >> tea_input;

			if (tea_input != "uhnmk")
			{
				cout << "Let's try making the tea again." << endl;
			}
			temp_inventory.setTea(tea_choice, -1);
			temp_inventory.setTotalItems(-1);

		} while (tea_input != "uhnmk");

		do
		{
			if(milk_choice >= 0)
			{
				if(temp_inventory.getMilk(milk_choice) <= 0)
				{
					cout << "This order doesn't seem to be going too well. You ran out of the required ingredients. Get some more and try again!" << endl;
					return temp_inventory;
				}
			}

			cout << "Let's pour in our milk. Type 'mi' five times." << endl;
			cin >> milk_input;

			if (milk_input != "mimimimimi")
			{
				cout << "Uh oh. You spilled the milk everywhere. Try pouring it carefully this time." << endl;
			}
			temp_inventory.setMilk(milk_choice, -1);
			temp_inventory.setTotalItems(-1);

		} while (milk_input != "mimimimimi");

		temp_inventory.setCup(-1);
		temp_inventory.setTotalItems(-1);

		if(boba_choice == order_[0] && milk_choice == order_[1] && tea_choice == order_[2])
		{
			made = true;
			cout << "Great job!, you made the order!" << endl;
			return temp_inventory;
		}
	}
	else
	{
		cout << "You don't have the ingredients required to make this." << endl;
		return temp_inventory;
	}

	return temp_inventory;
}