// Inventory.cpp

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#include <iostream>
#include "Inventory.h"

using namespace std;

// Constructors
Inventory::Inventory()
{
	cup = 0;
	total_money = 50;
	total_item = 0;
	for (int i = 0; i < 4; i++)
	{
		boba[i] = 0;
		tea[i] = 0;
		milk[i] = 0;
	}
}
Inventory::Inventory(int newBoba[], int newMilk[], int newTea[], int newCup)
{
	total_money = 50;
	total_item = 0;
	for (int i = 0; i < size; i++)
	{
		boba[i] = 0;
		tea[i] = 0;
		milk[i] = 0;
	}
	for (int i = 0; i < size; i++)
	{
		boba[i] = newBoba[i];
		milk[i] = newMilk[i];
		tea[i] = newTea[i];
	}
	cup = newCup;
}

// Getters and setters
//gets amount of boba from a specific index (pearl, popping, etc.)
int Inventory::getBoba(int index)
{
	return boba[index];
}
// adds number of boba into a specific index
void Inventory::setBoba(int index, int amount)
{
	boba[index] += amount;
}
//gets/adds total amount of milk from a specific index (whole, almond, etc.)
int Inventory::getMilk(int index)
{
	return milk[index];
}
void Inventory::setMilk(int index, int amount)
{
	milk[index] += amount;
}
//gets/adds total amount of tea from a specific index (black, matcha, etc.)
int Inventory::getTea(int index)
{
	return tea[index];
}
void Inventory::setTea(int index, int amount)
{
	tea[index] += amount;
}
// gets total amount of cups
int Inventory::getCup()
{
	return cup;
}
// adds to total amount of cups
void Inventory::setCup(int amount)
{
	cup += amount;
}

double Inventory::getTotalMoney()
{
	return total_money;
}
void Inventory::setTotalMoney(double amount)
{
	total_money = amount;
}
double Inventory::getSize()
{
	return size;
}
double Inventory::getBobaPrice()
{
	return boba_price;
}
double Inventory::getCupPrice()
{
	return cup_price;
}
double Inventory::getMilkPrice()
{
	return milk_price;
}
double Inventory::getTeaPrice()
{
	return tea_price;
}
void Inventory::setTotalItems(int num_items)
{
	total_item += num_items;
}
int Inventory::getTotalItems()
{
	return total_item;
}