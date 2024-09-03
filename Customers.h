// Customers.h

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <iostream>
#include <vector>
#include "Order.h"
using namespace std;

class Customers
{
private:
	string name;
	int num_orders;
	vector<Order> orders;
	int patience;
	int tips;
	bool order_taken;

public:
	// Constructors
	Customers();
	Customers(string newName, int newPatience, Order newOrders[3], int newNumOrders);

	// Getters and setters
	string getName();
	void setName(string newName);

	int getNumOrders();
	void setNumOrders(int new_num_orders);

	int getPatience();
	void setPatience(int newPatience);
  //patience changes based on players movement
	void setPatienceTurns(int numMoves);

	int getTip();
	void setTip(int amount);

	void addOrder(Order order_);
	Order getOrder(int order_number);
	void setOrder(int index, Order order_);

	void setOrderTaken();
	bool getOrderTaken();
};

#endif