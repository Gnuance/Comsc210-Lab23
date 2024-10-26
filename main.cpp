/*
    OBJECTIVES
    Task One: See Goat.h
    Task Two: Write a GM3K1 engine that loops on this menu.
        Write a main_menu() function that outputs this and then obtains, validates, and returns the user's choice.
    Task Three: Write functions to add a goat to the trip, delete a goat from the trip, and display the current trip.
        When you're adding a goat, randomly select a name and color from main()'s arrays and select a random age between 0 and MAX_AGE.
        When you're asking the user to select a certain goat, display a submenu in this format (see assignment),
            allowing the user to input an integer to reference the correct goat.
    Task Four: Polish your output so it looks neatly laid out and flows intuitively.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string[], string[]);
void display_trip(list<Goat> trip);
int main_menu();                      // outputs prompt and collects user selection
bool isValidOption(string, int, int); // helper function to validate user input

int main()
{
    list<Goat> trip = {};
    srand(static_cast<unsigned int>(time(nullptr)));
    bool again;
    int userSelectedOption = 0; // represents user option chosen from menu

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++])
        ;
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++])
        ;
    fin1.close();

    // prompt user for selection and input
    // user selection 4 is the program exit code
    do
    {
        userSelectedOption = main_menu();
        switch (userSelectedOption)
        {
        case 1:
            add_goat(trip, names, colors);
            break;
        case 2:
            delete_goat(trip);
            break;
        case 3:
            display_trip(trip);
            break;
        default:
            break;
        }
    } while (userSelectedOption != 4);

    return 0;
}

// main menu fuction for Task 2
int main_menu()
{
    string userInput = "";

    do
    {
        // output prompt
        cout << "*** GOAT MANAGER 3001 ***" << endl
             << "[1] Add a goat" << endl
             << "[2] Delete a goat" << endl
             << "[3] List goats" << endl
             << "[4] Quit" << endl
             << "Choice --> ";
        getline(cin, userInput); // get user input as string and test
        cout << endl;
    } while (!isValidOption(userInput, 1, 4));

    // if isValidOption passed, stoi(userInput) has already been tested and is safe
    return stoi(userInput);
}

// return t/f if userInput is a valid int between min and max
// helper function for main_menu and delete_goat
// WARNING: stoi() will convert a double to an int or any string following an int.
// Ex: stoi("2.9") will return 2 and so will stoi("2tGznso"), etc.
bool isValidOption(string userInput, int minOption, int maxOption)
{
    int selectedOption = 0;
    try
    {
        selectedOption = stoi(userInput);
    }
    catch (const std::exception &e)
    {
        cout << "Invalid input: Please enter a valid integer." << endl;
        return false;
    }

    // if userInput is an int but outside expected range
    if (selectedOption < minOption || selectedOption > maxOption)
    {
        cout << "Invalid input: Please enter an integer between " << minOption << " and " << maxOption << "." << endl;
        return false;
    }

    return true;
}

// adds random goat to trip
void add_goat(list<Goat> &trip, string names[], string colors[])
{
    string name = names[rand() % SZ_NAMES];
    int age = rand() % MAX_AGE + 1;
    string color = colors[rand() % SZ_COLORS];

    trip.push_back(Goat(name, age, color));
}

// directly outputs trip to console
void display_trip(list<Goat> trip)
{
    if (trip.size() < 1)
    {
        cout << endl << "No goats in current trip." << endl;
        return;
    }
    
    int count = 0;
    cout << endl
         << "Trip:" << endl;
    for (auto it = trip.begin(); it != trip.end(); it++)
    {
        cout << "\t[" << ++count << "] " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")" << endl;
    }
}

// lets user select a Goat to delete
void delete_goat(list<Goat> &trip)
{
    // guard statement in case of empty list
    if (trip.size() < 1)
    {
        cout << endl << "Trip is empty, no goats to delete." << endl;
        return;
    }

    string userInput = "";
    auto it = trip.begin(); // iterator to first element

    // display Goats in current trip available for selection
    // prompt user for index to delete
    // WARNING: index DISPLAYED TO USER begins at 1
    do
    {
        display_trip(trip);
        cout << "Please enter index to delete --> ";
        getline(cin, userInput); // get user input as string
        // make sure user value is valid and delete
        if (isValidOption(userInput, 1, trip.size()))
        {
            advance(it, stoi(userInput) - 1); // -1 because index displayed to users starts at 1
            trip.erase(it);
            cout << endl
                 << "Updated Trip After Deletion";
            display_trip(trip);
            break;
        }
    } while (true);
}
