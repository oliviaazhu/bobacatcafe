// mainGame.cpp

// CSCI 1300 Fall 2022
// Author: Olivia Zhu, Rachel Liang
// Recitation: 303 - Xuefei Sun, 304 - Nikkith Sannidhi
// Project 3

#include <iostream>
#include "Order.h"
#include "Game.h"
#include "Player.h"
#include "Cats.h"
#include "Cafe.h"
#include "Customers.h"
#include "Inventory.h"

using namespace std;

int main()
{
    // Declare variables
    srand(time(0));
    int choice;
    int num_turns = 0;
    char action_key;
    Game game1;
    Cafe cafe1;
    char order_choice;
    string name;
    int kitchen_choice;
    game1.readCat("cats.txt");
    int order_number = 0;
    char order_ready;
    bool new_game = true;
    int num_customers_served = 0;
    int num_current_orders = 0; 
    int num_current_customers = 0;
    Inventory shop_inventory;
    int momentos_collected = 0;

    // Spawn in the cats
    for (int i = 0; i < 10; i++)
    {
        int row = rand() % 12;
        int col = rand() % 12;

        if(cafe1.onExit(row, col) == false && cafe1.onKitchen(row, col) == false)
        {
            cafe1.addCat(row, col);
        }

    }

    // Read in the customers
    game1.readCustomers("customer.txt");

    // Spawn in 1-3 customers
    for(int i = 0; i < 3; i++)
    {
        int row = rand() % 12;
        int col = rand() % 12;

        if(cafe1.onCat(row, col) == false && cafe1.onCustomer(row, col) == false && cafe1.onKitchen(row, col) == false && cafe1.onExit(row, col) == false)
        {
           cafe1.addCustomer(row, col); 
           num_current_customers++;
        }
    }

    // Get the user's name
    cout << "Hi there, meow! (=＾● ⋏ ●＾=)" << endl;
    cout << "What's your name?" << endl;
    cin >> name;

    Player player1(name);

    cout << "Welcome in, " << player1.getName() << "! Please select a choice from the menu below" << endl;

    do
    {
        // Prints out menu and allows user to make a choice. 
        cout << "... =^._.^= ∫ ..." << endl;
        cout << "1. Play" << endl;
        cout << "2. How to play" << endl;
        cout << "3. Go to Shop" << endl;
        cout << "4. Storyline" << endl;
        cout << "5. Current Inventory" << endl;
        cout << "6. Quit Game" << endl;
        cin >> choice;
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Please enter a valid menu option (1-6)." << endl;
            cin >> choice;
        }

        switch (choice)
        {
            // Play the game
            case 1:
                // If this is their first time playing, open the shop.
                if(new_game == true)
                {
                    shop_inventory = game1.shopInventory(player1);
                    player1.setInventory(shop_inventory);
                    new_game = false;
                }
                cafe1.setYourPosition(6, 10);
                cafe1.onExit(cafe1.getPlayerRow(), cafe1.getPlayerCol());
                cafe1.displayMap(game1);

                while (cafe1.onExit(cafe1.getPlayerRow(), cafe1.getPlayerCol()) == false)
                {
                    cout << endl;
                    // Take in input
                    cout << "Move using wasd. If you would like to view your current orders, press 'c'. If you would like to see your stats and inventory, press 'i'. If you would like to rest and recover energy, press 'r'. To quit the game, press 'q' (This will completely shut down the game)." << endl;
                    cin >> action_key;

                    while(action_key != 'w' && action_key != 'a' && action_key != 's' && action_key != 'd' && action_key != 'c' && action_key != 'i' && action_key != 'r' && action_key != 'q')
                    {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input. Try again." << endl;
                        cin >> action_key;
                    }

                    Inventory check_money = player1.getInventory();
                    int time = game1.changeTime(num_turns);

                    // Check if any of the ending conditions are met 
                    if(time >= 1800)
                    {
                        cout << "It's time for the cafe to close. Congrats on making it through the day. Check results.txt to see how you did!" << endl;
                        player1.finalOutput();
                        return 0;
                    }
                    else if(num_customers_served == 7)
                    {
                        cout << "You served enough customers for the day. Congrats! Make sure to check results.txt to see how you did! " << endl;
                        player1.finalOutput();
                        return 0;
                    }
                    else if((check_money.getTotalMoney() == 0 && check_money.getTotalItems() == 0 && num_current_customers == 0) || check_money.getTotalMoney() < 0)
                    {
                        cout << "You ran out of money and ingrdients. Looks like you'll have to close the shop down early. Check results.txt to see how you did." << endl;
                        player1.finalOutput();
                        return 0;
                    }
                    // Set the customer's patience and check if any of them have no patience left
                    else
                    {
                        int counter = 0;
                        
                        for (int i = 0; i < 10; i++)
                        {
                            Customers check_customer_patience = game1.getCustomers(i);

                            if(!(cafe1.getCustomerRow(i) == -1 && cafe1.getCustomerCol(i) == -1))
                            {
                                check_customer_patience.setPatienceTurns(num_turns);
                            }

                            game1.setCustomers(check_customer_patience, i);

                            if(check_customer_patience.getPatience() <= 0)
                            {
                                if(!(cafe1.getCustomerRow(i) == -1 && cafe1.getCustomerCol(i) == -1))
                                {
                                    cafe1.customerLeave(i);
                                    cout << "A customer has left because their patience has run out. Don't get off task too much." << endl;
                                    for(int i = 0; i < check_customer_patience.getNumOrders(); i++)
                                    {
                                        Order delete_order = check_customer_patience.getOrder(i);
                                        
                                        int delete_order_num = delete_order.getOrderNum();

                                        player1.removeOrders(delete_order_num);
                                    }
                                    counter++;
                                }
                                
                            }
                            
                        }

                        num_current_customers = num_current_customers - counter;
                    }
                    
                    // If 25 turns have passed spawn in a new customer
                    if(num_turns % 25 == 0 && num_turns != 0)
                    {
                        int row = rand() % 12;
                        int col = rand() % 12;
                        if(cafe1.onCat(row,col) == false && cafe1.onCustomer(row,col) == false && cafe1.onKitchen(row,col) == false && cafe1.onExit(row, col) == false)
                        {
                            cout << "A new customer has arrived." << endl;
                            cafe1.addCustomer(row, col);
                            num_current_customers++;
                        }
                    }

                    // Allows the player to move
                    if (action_key == 'w' || action_key == 'a' || action_key == 's' || action_key == 'd')
                    {
                        if(cafe1.move(action_key) == true && player1.getEnergy() > 0)
                        {
                            // Prints out the map
                            cout << "Time: " << game1.getTime() << endl;
                            cout << "Energy: " << player1.getEnergy() << endl;
                            cafe1.displayMap(game1);
                            player1.setEnergy(-2);
                            num_turns++;

                            // Guides player through order making process, while they're on the kitchen, and updates order statuses. 
                            if (cafe1.onKitchen(cafe1.getPlayerRow(), cafe1.getPlayerCol()) == true)
                            {
                                cout << "I'm at the kitchen!" << endl;
                                cout << "Here is your current list of orders: " << endl;
                                player1.printOutCurrentOrders();
                                cout << "Which order would you like to fulfill? (Enter the order number. If you'd like to leave, enter -1)." << endl;
                                cin >> kitchen_choice;
                                while(kitchen_choice != -1 && !(kitchen_choice <= order_number))
                                {
                                    cout << "Invalid input. Try again." << endl;
                                    cin >> kitchen_choice;
                                }

                                if (kitchen_choice == -1)
                                {
                                    cout << "You've left the kitchen." << endl;
                                }
                                else if(kitchen_choice <= order_number)
                                {
                                    Order making_order; 
                                    for (int i = 0; i < player1.getNumOrders(); i++)
                                    {
                                        Order temp_order = player1.getOrder(i);

                                        if(temp_order.getOrderNum() == kitchen_choice)
                                        {
                                            making_order = temp_order;
                                            continue;
                                        }
                                    }
                                    Inventory temp_inventory = making_order.makeOrder(player1);
                                    player1.setInventory(temp_inventory);

                                    if(making_order.getMade() == true)
                                    {
                                        for (int i = 0; i < player1.getNumOrders(); i++)
                                        {
                                            Order temp_order = player1.getOrder(i);

                                            if(temp_order.getOrderNum() == making_order.getOrderNum())
                                            {
                                                player1.setOrder(i, making_order);
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    cout << "Please enter a valid order number." << endl;
                                }
                            }

                            // Randomly generates action a cat takes, when the player falls on a cat
                            else if (cafe1.onCat(cafe1.getPlayerRow(), cafe1.getPlayerCol()) == true)
                            {
                                int cat_position = cafe1.getCatPosition(cafe1.getPlayerRow(), cafe1.getPlayerCol());
                                Cats temp_cat = game1.getCats(cat_position);

                                if (temp_cat.getMetCount() == 0)
                                {
                                    cout << "I found a cat! Its name is " << temp_cat.getName() << "." << endl;
                                    temp_cat.setMetCount(1);
                                    temp_cat.metCat();
                                    game1.setCats(temp_cat, cat_position);
                                }
                                else if (temp_cat.getMetCount() >= 2)
                                {
                                    // Gives cat's momento to player
                                    int momento_chance = rand() % 4;

                                    if (momento_chance <= 2 && temp_cat.getMomentoReceived() == false && momentos_collected < 10)
                                    {
                                        cout << "Looks like " << temp_cat.getName() << " is really starting to like you. They've brought you a " << temp_cat.getMomentoName() << "." << endl;
                                        player1.setMomento(temp_cat.getMomentoName(), momentos_collected);
                                        temp_cat.setMomentoReceived(true);
                                        game1.setCats(temp_cat, cat_position);
                                        momentos_collected++;
                                    }

                                }
                                else
                                {
                                    cout << "You've already met " << temp_cat.getName() << "." << endl;
                                    temp_cat.setMetCount(1);
                                    game1.setCats(temp_cat, cat_position);
                                }

                                // Plays through quiz or guessing game, if it is the magical quiz cat
                                if (temp_cat.getName() == "Cosmo")
                                {
                                    cout << "Meow-ha-ha! You've encountered the magical game cat. You have a chance to strike it rich in a randomly selected mini game!" << endl;

                                    int game_chance = rand() % 11;
                                    if(game_chance <= 7)
                                    {
                                        bool result = temp_cat.guessingGame();

                                        if(result == true)
                                        {
                                            Inventory temp_inventory = player1.getInventory();
                                            int temp_money = temp_inventory.getTotalMoney();
                                            temp_inventory.setTotalMoney(temp_money + 10);
                                            player1.setInventory(temp_inventory);

                                            int momento_chance = rand() % 4;

                                            if (momento_chance <= 2 && temp_cat.getMomentoReceived() == false && momentos_collected < 10)
                                            {
                                                cout << "Cosmo, the magical game cat, really likes you! You've been gifted Cosmo's momento, a " << temp_cat.getMomentoName() << "." << endl;
                                                player1.setMomento(temp_cat.getMomentoName(), momentos_collected);  
                                                momentos_collected++;

                                            }
                                        }
                    
                                    }
                                    else
                                    {
                                        bool result = temp_cat.quiz();

                                        if(result == true)
                                        {
                                            Inventory temp_inventory = player1.getInventory();
                                            int temp_money = temp_inventory.getTotalMoney();
                                            temp_inventory.setTotalMoney(temp_money + 20);
                                            player1.setInventory(temp_inventory);

                                            int momento_chance = rand() % 4;

                                            if (momento_chance <= 2 && temp_cat.getMomentoReceived() == false && momentos_collected < 10)
                                            {
                                                cout << "Cosmo, the magical game cat, really likes you! You've been gifted Cosmo's momento, a " << temp_cat.getMomentoName() << "." << endl;
                                                player1.setMomento(temp_cat.getMomentoName(), momentos_collected);  
                                                momentos_collected++;

                                            }
                                        }
                                    }

                                    temp_cat.setMetCount(-1);
                                    game1.setCats(temp_cat, cat_position);

                                    cout << "Meow-ha-ha! Hope you had fun during our game." << endl;

                                    cafe1.removeCat(cat_position);
                                    int row = rand() % 12;
                                    int col = rand() % 12;
                                    if(cafe1.onCat(row, col) == false && cafe1.onCustomer(row, col) == false)
                                    {
                                        cafe1.updateCatPosition(cat_position, row, col);
                                    }

                                }
                                else
                                {
                                    // Cat either trips player, brings useless item, or brings ingredients.
                                    int trip_chance = rand() % 5;

                                    if (trip_chance <= 1)
                                    {
                                        Inventory trip_inventory = temp_cat.trip(player1); 
                                        player1.setInventory(trip_inventory);
                                        cout << temp_cat.getName() << " tripped you. You might have dropped some items. Check your inventory!" << endl;
                                    }
                                    else
                                    {
                                        int item_chance = rand() % 4;

                                        if(item_chance == 2)
                                        {
                                            cout << temp_cat.getName() << " brought you a crushed soda can. Thanks?" << endl;
                                        }
                                        else
                                        {
                                            Inventory bring_items_inventory = temp_cat.bring_item(player1);
                                            player1.setInventory(bring_items_inventory);
                                            cout << temp_cat.getName() << " brought some items. Check your inventory!" << endl;
                                        }
                                    }
                                }
                            }
                            // Interactions with customers, when player lands on a customer
                            else if (cafe1.onCustomer(cafe1.getPlayerRow(), cafe1.getPlayerCol()) == true)
                            {
                                int customer_position = cafe1.getCustomerPosition(cafe1.getPlayerRow(), cafe1.getPlayerCol());
                                Customers temp_customer = game1.getCustomers(customer_position);
                                cout << "I found a customer!" << endl;

                                // Takes their order, and updates the orders the player has
                                if (temp_customer.getOrderTaken() == false)
                                {
                                    cout << "Would you like to take " << temp_customer.getName() << "'s order(s)? They currently have " << temp_customer.getNumOrders() << " order(s). (Y/N)" << endl;
                                    cin >> order_choice;
                                    while(order_choice != 'Y' && order_choice != 'y' && order_choice != 'N' && order_choice != 'n')
                                    {
                                        cin.clear();
                                        cin.ignore(1000, '\n');
                                        cout << "Please enter valid input (Y/N)." << endl;
                                        cin >> order_choice;
                                    }


                                    if (order_choice == 'Y' || order_choice == 'y')
                                    {
                                        for (int i = 0; i < temp_customer.getNumOrders(); i++)
                                        {
                                            Order temp_order = temp_customer.getOrder(i);
                                            temp_order.setOrderNum(order_number);
                                            temp_order.setOrderName(temp_customer.getName());
                                            player1.addOrder(temp_order);
                                            temp_customer.setOrder(i, temp_order);
                                            num_current_orders++;
                                            order_number++;
                                        }

                                        temp_customer.setOrderTaken();
                                        game1.setCustomers(temp_customer, customer_position);
                                        cout << "You now have " << num_current_orders << " order(s) to fulfill." << endl;

                                    }
                                    // If player doesn't take order, the patience drops
                                    else if (order_choice == 'N' || order_choice == 'n')
                                    {
                                        cout << "Sounds like your hands are full. Be sure to come get their order later." << endl;
                                        temp_customer.setPatience(-5);
                                        game1.setCustomers(temp_customer, customer_position);
                                    }
                                
                                }
                                
                                // Serves their order
                                else
                                {
                                    cout << "You've already met " << temp_customer.getName() << ". Is their order ready to serve? (Y/N)" << endl;
                                    cin >> order_ready;

                                    while(order_choice != 'Y' && order_choice != 'y' && order_choice != 'N' && order_choice != 'n')
                                    {
                                        cin.clear();
                                        cin.ignore(1000, '\n');
                                        cout << "Please enter valid input (Y/N)." << endl;
                                        cin >> action_key;
                                    }

                                    if(order_ready == 'Y' || order_ready == 'y')
                                    {
                                        bool correct_order = false;
                                        int order_serve = -2;
                                        while(correct_order == false && order_serve != -1)
                                        {
                                            player1.printOutCurrentOrders();
                                            cout << "Which order would you like to serve? (Enter the order number. Enter -1 to exit)." << endl;
                                            cin >> order_serve;

                                            if(order_serve == -1)
                                            {
                                                continue;
                                            }

                                            // Checks if correct orders were selected
                                            for (int i = 0; i < player1.getNumOrders(); i++)
                                            {
                                                Order temp_order = player1.getOrder(i);

                                                if(correct_order == true)
                                                {
                                                    continue;
                                                }

                                                if(order_serve == temp_order.getOrderNum() && temp_order.getMade() == true)
                                                {
                                                    for(int j = 0; j < temp_customer.getNumOrders(); j++)
                                                    {
                                                        Order set_order = temp_customer.getOrder(j);

                                                        if(order_serve == set_order.getOrderNum())
                                                        {
                                                            temp_customer.setOrder(j, temp_order);
                                                            game1.setCustomers(temp_customer, customer_position);
                                                            correct_order = true;
                                                        }
                                                    }
                                                    continue;
                                                }
                                            }

                                            if(correct_order == false)
                                            {
                                                cout << "That's not " << temp_customer.getName() << "'s order. Try again!" << endl;
                                            }
                                        }

                                        // Gives players tips and payment, when correct order is served. Customer leaves when they are served
                                        if(player1.removeOrders(order_serve) == true)
                                        {
                                            cout << "Great job! " << temp_customer.getName() << " got their order!" << endl;
                                            Inventory temp_inventory = player1.getInventory();
                                            Order order_price = temp_customer.getOrder(0);
                                            int price = order_price.getPrice();
                                            int patience = temp_customer.getPatience();
                                            double tips = game1.tipsGiven(patience, price);
                                            cout << "They gave you $" << tips << " in tips." << endl;
                                            double temp_money = temp_inventory.getTotalMoney();
                                            temp_inventory.setTotalMoney(temp_money + price + tips);
                                            player1.setInventory(temp_inventory);
                                            num_current_orders--;

                                            int made_count = 0;

                                            // Checks if all of customer's orders have been received
                                            for (int i = 0; i < temp_customer.getNumOrders(); i++)
                                            {
                                                Order temp_order = temp_customer.getOrder(i);

                                                if(temp_order.getMade() == true)
                                                {
                                                    made_count++;
                                                }
                                                if(made_count == temp_customer.getNumOrders())
                                                {
                                                    game1.setCustomers(temp_customer, customer_position);
                                                    if(cafe1.customerLeave(customer_position) == true)
                                                    {
                                                        cafe1.customerLeave(customer_position);
                                                        cout << "You've served all of " << temp_customer.getName() << "'s orders. They've left the shop." << endl;
                                                        num_customers_served++;
                                                        num_current_customers--;
                                                    }
                                                }
                                            }
                                        }
                                
                                    }
                                    else if(order_ready == 'N' || order_ready == 'n')
                                    {
                                        cout << "Sounds like your hands are full. Be sure to come serve their order later." << endl;
                                        temp_customer.setPatience(-5);
                                        game1.setCustomers(temp_customer, customer_position);
                                    }
                                }
                            }
                        }
                        // If player runs out of energy, they must take a rest.
                        else if(player1.getEnergy() <= 0)
                        {
                            cout << "You've run out of energy. Rest for a turn and get back to work." << endl;
                            player1.setEnergy(15);
                            num_turns++;
                        }
                        // If player tries to move off map, print a warning out. 
                        else
                        {
                            cout << "You can't move in that direction!" << endl;
                        }
                        
                    }
                    // Prints out all of the player's orders
                    else if (action_key == 'c')
                    {
                        player1.printOutCurrentOrders();
                    }
                    // Prints out the player's inventory
                    else if (action_key == 'i')
                    {
                        player1.printOutInventory();
                    }
                    // Let's the player manually take a rest
                    else if(action_key == 'r')
                    {
                        cout << "You've restored 15 energy. " << endl;
                        num_turns++;
                        player1.setEnergy(15);
                    }
                    // Quits the game and prints out their results
                    else if(action_key == 'q')
                    {
                        cout << "See you later! Check results.txt for how great you did!" << endl;
                        player1.finalOutput();
                        return 0;
                    }
                    else
                    {
                        cout << "Please enter a valid choice." << endl;
                    }
                }
                cafe1.displayMap(game1);
                cout << "You've exited the cafe." << endl;
                break;

            // Prints out how to play the game
            case 2:
                cout << "How to play (=^･ｪ･^=))ﾉ:" << endl;
                cout << "1. Before you can start the day, you must buy inventories with your starting amount of $30." << endl;
                cout << "2. Use letters w(up), a(left), s(down), and d(right) and the enter key to move around the map." << endl;
                cout << "3. Meet and serve customers as you run the cafe for a day." 
                    << "\nWhen meeting a cusomter, you can choose to serve them or move on."<< endl;
                cout << "4. When you decide to serve the customers, their orders would be collected."
                    << "\nThen go to the kitchen (K) and follow instructions to make orders at the kitchen." << endl;
                cout << "5. As you move around the cafe, you have a chance to encounter regualar cats, they can be a blessing or a curse."
                    << "\nOr a magical quiz cat, which will give you a prize if you win, but lose and face the consquence." << endl;
                cout << "6. If you meet a cat enough times, you may have the chance to recieve a momento from them. Try to collect them all!" << endl;
                cout << "7.If you ever need to buy more ingredients or want to stop playing, travel to the cafe exit (E) to return to the main menu." << endl;
                cout << "Have fun!"<< endl;
                cout << endl;
                break;
            // Let's the player shop for more supplies
            case 3:
                shop_inventory = game1.shopInventory(player1);
                player1.setInventory(shop_inventory);
                break;
            // Prints out the game's backstory
            case 4:
                cout << "=== Story ===" << endl;
                cout << "Oh no! Your sister is sick, but she owns a boba cat cafe. You agree to help run her shop for a day while she recovers. Besides you're a student and need the money anyway.";
                break;
            // Prints out the player's inventory
            case 5:
                player1.printOutInventory();
                break;
            // Quits the game and prints out final results
            case 6:
                cout << "You sure? (Enter 6 again to confirm. 0 to go back)" << endl;
                cin >> choice;
                if (choice == 6) {
                    cout << "Click on the results.txt to see your final results. Bye!"
                        << endl;
                    player1.finalOutput();
                }
                break;
            // Input validation
            default:
                cout << "Please enter a valid menu option (1-6)." << endl;
                break;

        }

    } while (choice != 6);

    return 0;
}