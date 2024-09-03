// Game.h

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <cassert>
#include "Player.h"
#include "Order.h"
#include "Cats.h"
#include "Customers.h"
#include "Inventory.h"

class Game
{
private:
	static const int cust_size = 10;
	static const int cat_size = 10;
	Customers customers_[cust_size];
	Cats cats_[cat_size];
	int num_customers;
	int num_cats;
	int time;

public:
	Game();
	int getCustomerSize();
	int getCatSize();
	bool readCat(string filename);
	bool readCustomers(string filename);
	Inventory shopInventory(Player player_);
	Cats getCats(int index);
	void setCats(Cats cat_, int index);
	Customers getCustomers(int index);
	void setCustomers(Customers customer_, int index);
	double tipsGiven(int patience, int price);
	int getTime();
	int changeTime(int numMoves);
};
#endif
