#ifndef CAFE_H
#define CAFE_H

#include <iostream>
#include "Game.h"

using namespace std;

class Cafe
{
private:
    // Space markers
    const char NORMAL = '-'; 
    const char KITCHEN = 'K'; 
    const char CUSTOMER = 'C'; 
    const char YOU = 'O'; 
    const string CAT = "ᨐ"; 
    const char EXIT = 'E'; 

    // Map information
    static const int num_rows = 12; 
    static const int num_cols = 12;
    static const int max_cats = 10; 
    static const int max_customers = 10; 

    // Special space locations
    int player_position[2]; 
    int kitchen_location[2];  
    int exit_location[2];
    int cat_positions[max_cats][2]; 
    int customer_positions[max_customers][2]; 

    int cat_count; 
    int customer_count; 
    
public:
    Cafe();

    // getters
    int getPlayerRow();
    int getPlayerCol();
    int getKitchenRow();
    int getKitchenCol();
    int getExitRow();
    int getExitCol();
    int getCatCount();
    int getCustomers();
    int getNumRows();
    int getNumCols();
    bool onMap(int row, int col);
    int getCustomerPosition(int row, int col);
    bool onKitchen(int row, int col);
    int getCatPosition(int row, int col);
    bool onExit(int row, int col);
    bool onCat(int row, int col);
    bool onCustomer(int row, int col);
    int getCustomerRow(int index);
    int getCustomerCol(int index);

    // setters
    void setYourPosition(int row, int col);
    void setExit(int row, int col);
    void setKitchen(int row, int col);

    // other
    void displayMap(Game game_);
    bool move(char move_key);
    bool addCustomer(int row, int col);
    bool addCat(int row, int col);
    bool customerLeave(int index);
    bool removeCat(int index);
    bool updateCatPosition(int index, int row, int col);
};

#endif