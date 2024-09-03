// Cats.cpp

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#include "Cats.h"
#include "Inventory.h"
#include "Player.h"
#include <fstream>
#include <iostream>

using namespace std;

// Constructors
Cats::Cats()
{
	name = "";
	momento_name = "";
	momento_count = 0;
	met_count = 0;
	met = false;
	received_momento = false;
}

Cats::Cats(string cat_name, string momento_name_)
{
	name = cat_name;
	momento_name = momento_name_;
	momento_count = 0;
	met_count = 0;
	met = false;
	received_momento = false;
}

// Getters and setters
string Cats::getName() { return name; }
void Cats::setName(string cat_name) { name = cat_name; }

string Cats::getMomentoName() { return momento_name; }
void Cats::setMomentoName(string new_momento_name)
{
	momento_name = new_momento_name;
}

int Cats::getMomentoCount() { return momento_count; }
void Cats::setMomentoCount(int new_momento_count)
{
	momento_count = new_momento_count;
}

int Cats::getMetCount() { return met_count; }
void Cats::setMetCount(int met_count_) { met_count += met_count_; }
bool Cats::getMomentoReceived()
{
	return received_momento;
}
void Cats::setMomentoReceived(bool momento_recieved_)
{
	received_momento = momento_recieved_;
}

/**
 * Algorithim: Determines if a cat has been met
 * 1. If the met count is greater than one, set met equal to true
 * 2. Otherwise, return false
 * Parameters:
 * Returns: bool
 */
bool Cats::metCat()
{
	if (met_count >= 1)
	{
		met = true;
	}
	else
	{
		met = false;
	}

	return met;
}

/**
 * Algorithim: Give the user 10 chances to guess a number between 1 and 100
 * 1. Randomly generates a number
 * 2. If the user guesses it right, return true, otherwise, return false.
 * Parameters:
 * Returns: bool
 */

bool Cats::guessingGame()
{
	// variables that generate randon numbers from 0 to 100
	srand(time(0));
	int correct_answer = rand() % 101;
	int user_guess;
	int guess_count = 0;

	do
	{
		cout << "Guess a number between 0 and 100!" << endl;
		cin >> user_guess;
		while(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid guess." << endl;
            cin >> user_guess;
        }

		guess_count++;

		// input validation
		if (user_guess < 0 || user_guess > 100)
		{
			cout << "Are you kidding me right meow?! You just wasted a guess. Pick a "
					"valid number next time."
				 << endl;
		}
		// guess is too high
		if (user_guess > correct_answer)
		{
			cout << "Too high, meow." << endl;
		}
		// guess is too low
		else if (user_guess < correct_answer)
		{
			cout << "Too low, meow." << endl;
		}

	} while (correct_answer != user_guess && guess_count != 10);

	// after 10 guess player loses game else player wins
	if (guess_count == 10)
	{
		cout << "A-paw-logies. Looks like you couldn't guess the number." << endl;
		return false;
	}
	else
	{
		cout << "A-meow-zing! You guessed the right number!" << endl;
		return true;
	}

	return false;
}

/**
 * Algorithim: Take a random number of items from your inventory
 * 1. Accepts a player_
 * 2. Randomly generates a number of items between 1 and 3 to take, if player has items to take
 * Parameters: player_ (Player)
 * Returns: bool
 */

Inventory Cats::trip(Player player_)
{
	// variable to randomize
	srand(time(0));

	int num_items;
	int drop_item = rand() % 11;
	int chance = rand() % 4;
	int chance_item = rand() % 5;
	// variable for players inventory
	Inventory temp_inventory = player_.getInventory();

	// 30% chance each of dropping 1, 2, or 3 items
	// 25% chance of dropping boba, milk, tea, or cups
	// 25% chance of dropping a specific type of item
	// cat doesn't take anything if their are no items
	if (temp_inventory.getTotalItems() == 0)
	{
		return temp_inventory;
	}
	// if drop_item less than 3, one inventory is taken
	else if (drop_item <= 3)
	{
		num_items = 1;
		if (chance_item <= 1 && temp_inventory.getMilk(chance) >= 1)
		{
			temp_inventory.setMilk(chance, -1);
			temp_inventory.setTotalItems(-1);
		}
		else if (chance_item == 2 && temp_inventory.getBoba(chance) >= 1)
		{
			temp_inventory.setBoba(chance, -1);
			temp_inventory.setTotalItems(-1);
		}
		else if (chance_item == 3 && temp_inventory.getTea(chance) >= 1)
		{
			temp_inventory.setTea(chance, -1);
			temp_inventory.setTotalItems(-1);
		}
		else if (temp_inventory.getCup() >= 1)
		{
			temp_inventory.setCup(-1);
			temp_inventory.setTotalItems(-1);
		}
		else
		{
			return temp_inventory;
		}
	}
	// if drop_iten is from 3-6 drop two items
	else if (drop_item > 3 && drop_item <= 6)
	{
		num_items = 2;
		if (chance_item <= 1 && temp_inventory.getMilk(chance) >= 2)
		{
			temp_inventory.setMilk(chance, -2);
			temp_inventory.setTotalItems(-2);
		}
		else if (chance_item == 2 && temp_inventory.getBoba(chance) >= 2)
		{
			temp_inventory.setBoba(chance, -2);
			temp_inventory.setTotalItems(-2);
		}
		else if (chance_item == 3 && temp_inventory.getTea(chance) >= 2)
		{
			temp_inventory.setTea(chance, -2);
			temp_inventory.setTotalItems(-2);
		}
		else if (temp_inventory.getCup() >= 2)
		{
			temp_inventory.setCup(-2);
			temp_inventory.setTotalItems(-2);
		}
		else
		{
			return temp_inventory;
		}
	}
	// else drop_item is 6-10 drops 3 items
	else
	{
		num_items = 3;
		if (chance_item <= 1 && temp_inventory.getMilk(chance) >= 3)
		{
			temp_inventory.setMilk(chance, -3);
			temp_inventory.setTotalItems(-3);
		}
		else if (chance_item == 2 && temp_inventory.getBoba(chance) >= 3)
		{
			temp_inventory.setBoba(chance, -3);
			temp_inventory.setTotalItems(-3);
		}
		else if (chance_item == 3 && temp_inventory.getTea(chance) >= 3)
		{
			temp_inventory.setTea(chance, -3);
			temp_inventory.setTotalItems(-3);
		}
		else if (temp_inventory.getCup() >= 3)
		{
			temp_inventory.setCup(-3);
			temp_inventory.setTotalItems(-3);
		}
		else
		{
			return temp_inventory;
		}
	}

	return temp_inventory;
}

/**
 * Algorithim: Gives a random number of items to your inventory
 * 1. Accepts a player_
 * 2. Randomly generates a number of items between 1 and 3 to give
 * Parameters: player_ (Player)
 * Returns: bool
 */
Inventory Cats::bring_item(Player player_)
{
	srand(time(0));

	int num_items;
	int brought_item = rand() % 11;
	int which_item = rand() % 4;
	int item_chance = rand() % 5;
	Inventory temp_inventory = player_.getInventory();

	// 30% chance each of getting 1, 2, or 3 items
	// 25% chance of getting boba, milk, tea, or cups
	// 25% chance of getting a specific type of item
	// if brought_item is less than or 3 gives you 1 item
	if (brought_item <= 3)
	{
		num_items = 1;
		if (item_chance <= 1)
		{
			temp_inventory.setMilk(which_item, 1);
			temp_inventory.setTotalItems(1);
		}
		else if (item_chance == 2)
		{
			temp_inventory.setBoba(which_item, 1);
			temp_inventory.setTotalItems(1);
		}
		else if (item_chance == 3)
		{
			temp_inventory.setTea(which_item, 1);
			temp_inventory.setTotalItems(1);
		}
		else if (item_chance >= 4)
		{
			temp_inventory.setCup(1);
			temp_inventory.setTotalItems(1);
		}
		else
		{
			return temp_inventory;
		}
	}
	// if brought_item is 3-6 gives you 2 item
	else if (brought_item > 3 && brought_item <= 6)
	{
		num_items = 2;
		if (item_chance <= 1)
		{
			temp_inventory.setMilk(which_item, 2);
			temp_inventory.setTotalItems(2);
		}
		else if (item_chance == 2)
		{
			temp_inventory.setBoba(which_item, 2);
			temp_inventory.setTotalItems(2);
		}
		else if (item_chance == 3)
		{
			temp_inventory.setTea(which_item, 2);
			temp_inventory.setTotalItems(2);
		}
		else if (item_chance >= 4)
		{
			temp_inventory.setCup(2);
			temp_inventory.setTotalItems(2);
		}
		else
		{
			return temp_inventory;
		}
	}
	// if brought_item is 6-10 gives you 3 item
	else
	{
		num_items = 3;
		if (item_chance <= 1)
		{
			temp_inventory.setMilk(which_item, 3);
			temp_inventory.setTotalItems(3);
		}
		else if (item_chance == 2)
		{
			temp_inventory.setBoba(which_item, 3);
			temp_inventory.setTotalItems(3);
		}
		else if (item_chance == 3)
		{
			temp_inventory.setTea(which_item, 3);
			temp_inventory.setTotalItems(3);
		}
		else if (item_chance >= 4)
		{
			temp_inventory.setCup(3);
			temp_inventory.setTotalItems(3);
		}
		else
		{
			return temp_inventory;
		}
	}

	return temp_inventory;
}

/**
 * Algorithim: Gives the player a quiz to pass
 * 1. Give the user five tea related questions.
 * 2. If they guess three right, return true. Otherwise, return false.
 * Parameters:
 * Returns: bool
 */

bool Cats::quiz()
{
	bool result = true;
	char input;
	// tallies the correct answers
	int score = 0;
	cout << "Meow-come to the Boba Cat Quiz! You will need to get three "
			"questions correct to pass. Beware of trick answers!"
		 << endl;
	// question 1
	cout << "1. What type of cat is Garfield?"
		 << "\na. Persian Tabby"
		 << "\nb. Lasagna Cat"
		 << "\nc. British Shorthair"
		 << "\nd. Bengal Cat" << endl;
	cin >> input;
	while(input != 'a' && input != 'b' && input != 'c' && input != 'd')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please enter a valid menu option (a-d)." << endl;
		cin >> input;
	}
	// do-while for input validations
	do
	{
		switch (input)
		{
		case 'a':
			cout << "Correct!" << endl;
			score++;
			break;
		case 'b':
			cout << "Meow no! That's incorrect, but he does love lasagna." << endl;
			break;
		case 'c':
		case 'd':
			cout << "Meow no! That's incorrect b(₌ ᵕ̣̣̣̣̣ ᆽ ᵕ̣̣̣̣̣₌)" << endl;
			break;
		default:
			cout << "Oops! Invalid letter, please enter letters a-d." << endl;
			break;
		}
	} while (input != 'a' && input != 'b' && input != 'c' && input != 'd');

	// question 2
	cout << "2. Where does boba originate from?"
		 << "\na. Grandma's House"
		 << "\nb. Thailand"
		 << "\nc. Germany"
		 << "\nd. China" << endl;
	cin >> input;
	while(input != 'a' && input != 'b' && input != 'c' && input != 'd')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please enter a valid menu option (a-d)." << endl;
		cin >> input;
	}
	do
	{
		switch (input)
		{
		case 'a':
			cout << "Meow no! That's incorrect, but whatever grandma makes is "
					"delicious. "
				 << endl;
			break;
		case 'b':
			cout << "Correct!" << endl;
			score++;
			break;
		case 'c':
		case 'd':
			cout << "Meow no! That's incorrect (₌ ᵕ̣̣̣̣̣ ᆽ ᵕ̣̣̣̣̣₌)" << endl;
			break;
		default:
			cout << "Oops! Invalid letter, please enter letters a-d." << endl;
			break;
		}
	} while (input != 'a' && input != 'b' && input != 'c' && input != 'd');

	// question 3
	cout << "3. What is the main ingredient of pearl boba?"
		 << "\na. Flour"
		 << "\nb. Love"
		 << "\nc. Brown Sugar"
		 << "\nd. Tapioca Starch" << endl;
	cin >> input;
	while(input != 'a' && input != 'b' && input != 'c' && input != 'd')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please enter a valid menu option (a-d)." << endl;
		cin >> input;
	}
	do
	{
		switch (input)
		{
		case 'a':
			cout << "Meow no! That's incorrect (₌ ᵕ̣̣̣̣̣ ᆽ ᵕ̣̣̣̣̣₌)" << endl;
			break;
		case 'b':
			cout << "Meow no! That's incorrect but good boba is always made with "
					"love <3!"
				 << endl;
			break;
		case 'c':
			cout << "Meow no! That's incorrect (₌ ᵕ̣̣̣̣̣ ᆽ ᵕ̣̣̣̣̣₌)" << endl;
			break;
		case 'd':
			cout << "Correct!" << endl;
			score++;
			break;
		default:
			cout << "Oops! Invalid letter, please enter letters a-d." << endl;
			break;
		}
	} while (input != 'a' && input != 'b' && input != 'c' && input != 'd');

	// question 4
	cout << "4. What year did the first cat go to space?"
		 << "\na. 1950"
		 << "\nb. Never! Home is safe and cozy!"
		 << "\nc. 1963"
		 << "\nd. 2000" << endl;
	cin >> input;
	while(input != 'a' && input != 'b' && input != 'c' && input != 'd')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please enter a valid menu option (a-d)." << endl;
		cin >> input;
	}
	do
	{
		switch (input)
		{
		case 'a':
			cout << "Meow no! That's incorrect (₌ ᵕ̣̣̣̣̣ ᆽ ᵕ̣̣̣̣̣₌)" << endl;
			break;
		case 'b':
			cout << "Meow no! That's incorrect but would be nice though!" << endl;
			break;
		case 'c':
			cout << "Correct!" << endl;
			score++;
			break;
		case 'd':
			cout << "Meow no! That's incorrect (₌ ᵕ̣̣̣̣̣ ᆽ ᵕ̣̣̣̣̣₌)" << endl;
			break;
		default:
			cout << "Oops! Invalid letter, please enter letters a-d." << endl;
			break;
		}
	} while (input != 'a' && input != 'b' && input != 'c' && input != 'd');

	// question 5
	cout << "5. How many cat years is in 1 human year?"
		 << "\na. 15"
		 << "\nb. 7"
		 << "\nc. 10"
		 << "\nd. 3" << endl;
	cin >> input;
	while(input != 'a' && input != 'b' && input != 'c' && input != 'd')
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Please enter a valid menu option (a-d)." << endl;
		cin >> input;
	}
	do
	{
		switch (input)
		{
		case 'a':
			cout << "Correct!" << endl;
			score++;
			break;
		case 'b':
		case 'c':
		case 'd':
			cout << "Meow no! That's incorrect (₌ ᵕ̣̣̣̣̣ ᆽ ᵕ̣̣̣̣̣₌)" << endl;
			break;
		default:
			cout << "Oops! Invalid letter, please enter letters a-d." << endl;
			break;
		}
	} while (input != 'a' && input != 'b' && input != 'c' && input != 'd');

	// if failed return false
	if (score < 3)
	{
		result = false;
	}
	return result;
}