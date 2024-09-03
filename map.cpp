#include <iostream>
#include "Cafe.h"

using namespace std;

    Cafe::Cafe()
    {
        int your_position[2] = {0,0}; // player position (row,col)
        int kitchen_location[2] = {6,0};
        int exit_location[2] = {6,12};
        int cat_count = 0; // stores number of cats in the cafe
        int customer_count = 0; // stores number of customers in the cafe
    }
    void Cafe::resetCafe()
    {
        
    }

    // getters
    int Cafe::getPlayerRow()
    {
        return your_position[0];
    }
    int Cafe::getPlayerCol()
    {
        return your_position[1];
    }
    int Cafe::getKitchenRow()
    {
        return kitchen_location[0];
    }
    int Cafe::getKitchenCol()
    {
        return kitchen_location[1];
    }
    int Cafe::getExitRow()
    {
        return exit_location[0];
    }
    int Cafe::getExitCol()
    {
        return exit_location[1];
    }
    int Cafe::getCatCount()
    {
        return cat_count;
    }
    int Cafe::getCustomers()
    {
        return customer_count;
    }
    int Cafe::getNumRows()
    {
        return num_rows;
    }
    int Cafe::getNumCols()
    {
        return num_cols;
    }


    bool Cafe::onMap(int row, int col)
    {

    }

    /*
    1. If on customer, 
    2. Do this for each pair of adjacent elements, starting with the first two and ending with the last two. At this point the last element should be the greatest. 
    3. Repeat the steps for all elements except the last one. 4. Repeat again from the beginning for one less element each time, until there are no more pairs to compare. 
    */
    bool Cafe::onCustomer(int row, int col)
    {

    }
    bool Cafe::onKitchen(int row, int col)
    {
        if(row == kitchen_location[0] && col == kitchen_location[1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    bool Cafe::onNormal(int row, int col)
    {

    }
    bool Cafe::onCat(int row, int col)
    {

    }
    bool Cafe::onExit(int row, int col)
    {
        if(row == exit_location[0] && col == exit_location[1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    

    // setters
    void Cafe::setYourPosition(int row, int col)
    {
        if(row > 0 && row <= 12)
        {
            your_position[0] = row; 
        }
        if(col > 0 && col <=12)
        {
            your_position[1] = col;
        }
    }
    void Cafe::setExit(int row, int col)
    {
        if(row > 0 && row <= 12)
        {
            exit_location[0] = row; 
        }
        if(col > 0 && col <=12)
        {
            exit_location[1] = col;
        }
    }
    void Cafe::setKitchen(int row, int col)
    {
        if(row > 0 && row <= 12)
        {
            kitchen_location[0] = row; 
        }
        if(col > 0 && col <=12)
        {
            kitchen_location[1] = col;
        }
    }

    // other

    /*
    1. If on customer, 
    2. Do this for each pair of adjacent elements, starting with the first two and ending with the last two. At this point the last element should be the greatest. 
    3. Repeat the steps for all elements except the last one. 4. Repeat again from the beginning for one less element each time, until there are no more pairs to compare. 
    */
    void displayMap();
    bool move(char);
    bool addCustomer(int row, int col);
    bool catChance(int row, int col);
    bool addCat(int row, int col);
    bool customerLeave(int row, int col);
    bool removeCat(int row, int col);
