// Cafe.cpp

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#include <iostream>
#include "Cafe.h"
#include "Game.h"
#include "Cats.h"

using namespace std;

    // Constructor
    Cafe::Cafe()
    {
        player_position[0] = 6;
        player_position[1] = 10;
        exit_location[0] = 6;
        exit_location[1] = 11;
        kitchen_location[0] = 6;
        kitchen_location[1] = 0;
        customer_count = 0;
        cat_count = 0;

        for (int i = 0; i < max_customers; i++)
        {
            customer_positions[i][0] = -1;
            customer_positions[i][1] = -1;
        }
        for (int i = 0; i < max_cats; i++)
        {
            cat_positions[i][0] = -1;
            cat_positions[i][1] = -1;
        }
    }

    // getters
    int Cafe::getPlayerRow()
    {
        return player_position[0];
    }
    int Cafe::getPlayerCol()
    {
        return player_position[1];
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
    int Cafe::getCustomerRow(int index)
    {
        return customer_positions[index][0];
    }
    int Cafe::getCustomerCol(int index)
    {
        return customer_positions[index][1];
    }
    bool Cafe::onMap(int row, int col)
    {
        return false;
    }
     /**
     * Algorithim: Finds the index of the customer located at a certain index
     * 1. Accepts a row and column
     * 2. Goes through all of the customer's positions.
     * 3. If the customer has that row and column, return the index. 
     * 3. Otherwise, return -1
     * Parameters: row (int), col(int)
     * Returns: int
     */
    int Cafe::getCustomerPosition(int row, int col)
    {
        for (int i = 0; i < max_customers; i++)
        {
            if (customer_positions[i][0] == row && customer_positions[i][1] == col)
            {
                return i;
            }
        }

        return -1;
    }
    bool Cafe::onKitchen(int row, int col)
    {
        if (row == kitchen_location[0] && col == kitchen_location[1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Algorithim: Finds the index of the cat located at a certain index
     * 1. Accepts a row and column
     * 2. Goes through all of the cat's positions.
     * 3. If the cat has that row and column, return the index. 
     * 3. Otherwise, return -1
     * Parameters: row (int), col(int)
     * Returns: int
     */
    int Cafe::getCatPosition(int row, int col)
    {
        for (int i = 0; i < max_cats; i++)
        {
            if (cat_positions[i][0] == row && cat_positions[i][1] == col)
            {
                return i;
            }
        }

        return -1;
    }

    /**
     * Algorithim: Checks if a space is where the exit is 
     * 1. Accepts a row and column
     * 2. If the row equals the exit row and the column equals the exit column, return true
     * 3. Otherwise, return false
     * Parameters: row (int), col(int)
     * Returns: bool
     */
    bool Cafe::onExit(int row, int col)
    {
        if (row == exit_location[0] && col == exit_location[1])
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /**
     * Algorithim: Checks if a space is where a cat is 
     * 1. Accepts a row and column
     * 2. If the row equals the cat's row and the column equals the cat's column, return true
     * 3. Otherwise, return false
     * Parameters: row (int), col(int)
     * Returns: bool
     */
    bool Cafe::onCat(int row, int col)
    {
        for (int i = 0; i < max_cats; i++)
        {
            if (cat_positions[i][0] == row && cat_positions[i][1] == col)
            {
                return true;
            }
        }

        return false;
    }

    /**
     * Algorithim: Checks if a space is where a customer is 
     * 1. Accepts a row and column
     * 2. If the row equals the customer's row and the column equals the customer's column, return true
     * 3. Otherwise, return false
     * Parameters: row (int), col(int)
     * Returns: bool
     */
    bool Cafe::onCustomer(int row, int col)
    {
        for (int i = 0; i < max_customers; i++)
        {
            if (customer_positions[i][0] == row && customer_positions[i][1] == col)
            {
                return true;
            }
        }

        return false;
    }

    // Setters
    void Cafe::setYourPosition(int row, int col)
    {
        player_position[0] = row;
        player_position[1] = col;
    }
    void Cafe::setExit(int row, int col)
    {
        exit_location[0] = row;
        exit_location[1] = col;
    }
    void Cafe::setKitchen(int row, int col)
    {
        kitchen_location[0] = row;
        kitchen_location[1] = col;
    }

    // Cafe functions

    /**
     * Algorithim: Displays the map
     * 1. Accepts a game_
     * 2. Checks if there are cats or customers on a space
     * 3. Checks for special spaces, and prints out one line of map at a time
     * Parameters: game_ (Game)
     * Returns: void
     */
    void Cafe::displayMap(Game game_)
    {
        
        for (int i = 0; i < num_rows; i++)
        {
            for (int j = 0; j < num_cols; j++)
            {
                bool customer_position = false;
                bool cat_position = false;

                for (int k = 0; k < max_customers; k++)
                {
                    if(i == customer_positions[k][0] && j == customer_positions[k][1])
                    {
                        customer_position = true;
                    }
                }

                for (int k = 0; k < max_cats; k++)
                {
                    Cats temp_cat = game_.getCats(k);
                    if(i == cat_positions[k][0] && j == cat_positions[k][1] && temp_cat.getMetCount() > 0)
                    {
                        cat_position = true;
                    }
                }

                if (i == player_position[0] && j == player_position[1])
                {
                    cout << YOU;
                }
                else if (customer_position == true)
                {
                
                    cout << CUSTOMER;

                }
                else if (cat_position == true)
                {
                    cout << CAT;
                }
                else if(i == kitchen_location[0] && j == kitchen_location[1])
                {
                    cout << KITCHEN;
                }
                else if (i == exit_location[0] && j == exit_location[1])
                {
                    cout << EXIT;
                }
                else
                {
                    cout << NORMAL;
                }
        
            }
            cout << endl;
        }
    }

    /**
     * Algorithim: Updates the user's position
     * 1. Accepts a move_key
     * 2. Depending on whether key is a or d or w or s, update the position array of the user
     * 3. If space is successfully updated, return true. Otherwise, if the move is invalid, return false
     * Parameters: move_key (char)
     * Returns: bool
     */
    bool Cafe::move(char move_key)
    {
        if(move_key == 'a')
        {
            if(player_position[1] > 0 && player_position[1] <= 11)
            {
                player_position[1] -= 1;
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (move_key == 'd')
        {
            if(player_position[1] >= 0 && player_position[1] < 11)
            {
                player_position[1] += 1;
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (move_key == 's')
        {
            if(player_position[0] >= 0 && player_position[0] < 11)
            {
                player_position[0] += 1;
                return true;
            }
            else
            {
                return false;
            }
        }
        else if (move_key == 'w')
        {
            if(player_position[0] > 0 && player_position[0] <= 11)
            {
                player_position[0] -= 1;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            cout << "Please enter a valid move key (w, a, s, d)." << endl;
            return false;
        }

        return false;
    }

    /**
     * Algorithim: Adds a customer
     * 1. Accepts the row and column
     * 2. Checks if the row and column are where the player, kitchen, and exit are. If they are, return false
     * 3. If not, add the customer position to the row and column, and return true. 
     * Parameters: row (int), col (int)
     * Returns: bool
     */
    bool Cafe::addCustomer(int row, int col)
    {
        if((row == player_position[0] && col == player_position[1]) && (row == kitchen_location[0] && col == kitchen_location[1]) && (row == exit_location[0] && col == exit_location[1]))
        {

            return false;
        }
        else
        {
            customer_positions[customer_count][0] = row;
            customer_positions[customer_count][1] = col;
            customer_count++;

            return true;;
        }

        return false;

    }

    /**
     * Algorithim: Adds a cat
     * 1. Accepts the row and column
     * 2. Checks if the row and column are where the player, kitchen, and exit are. If they are, return false
     * 3. If not, add the cat position to the row and column, and return true. 
     * Parameters: row (int), col (int)
     * Returns: bool
     */
    bool Cafe::addCat(int row, int col)
    {
        if((row == player_position[0] && col == player_position[1]) && (row == kitchen_location[0] && col == kitchen_location[1]) && (row == exit_location[0] && col == exit_location[1]))
        {

            return false;
        }
        else
        {
            cat_positions[cat_count][0] = row;
            cat_positions[cat_count][1] = col;
            cat_count++;

            return true;
        }

        return false;
    }

    /**
     * Algorithim: Removes a customer
     * 1. Accepts an index 
     * 2. Changes the row and column of the customer at that index to -1.
     * 3. Return true
     * Parameters: index(int)
     * Returns: bool
     */
    bool Cafe::customerLeave(int index)
    {
        customer_positions[index][0] = -1;
        customer_positions[index][1] = -1;

        return true;
    }

    /**
     * Algorithim: Removes a cat
     * 1. Accepts an index 
     * 2. Changes the row and column of the cat at that index to -1.
     * 3. Return true
     * Parameters: index(int)
     * Returns: bool
     */
    bool Cafe::removeCat(int index)
    {
        cat_positions[index][0] = -1;
        cat_positions[index][1] = -1;

        return true;
    }
    
    /**
     * Algorithim: Update's a cat's position
     * 1. Accepts the row and column
     * 2. Checks if the row and column are where the player, kitchen, and exit are. If they are, return false
     * 3. If not, update the cat position to the row and column, and return true. 
     * Parameters: row (int), col (int)
     * Returns: bool
     */
    bool Cafe::updateCatPosition(int index, int row, int col)
    {
        if((row == player_position[0] && col == player_position[1]) && (row == kitchen_location[0] && col == kitchen_location[1]) && (row == exit_location[0] && col == exit_location[1]))
        {

            return false;
        }
        else
        {
            cat_positions[index][0] = row;
            cat_positions[index][1] = col;

            return true;
        }

        return false;
    }