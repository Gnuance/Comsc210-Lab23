/*
    OBJECTIVES
    Task One: See Goat.h
    Task Two: Write a GM3K1 engine that loops on this menu.
        Write a main_menu() function that outputs this and then obtains, validates, and returns the user's choice.
    Task Three: Write functions to add a goat to the trip, delete a goat from the trip, and display the current trip.
        When you're adding a goat, randomly select a name and color from main()'s arrays and select a random age between 0 and MAX_AGE.
        When you're asking the user to select a certain goat, display a submenu in this format (see assignment),
            allowing the user to input an integer to reference the correct goat.
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
    srand(time(0));
    bool again;

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

    cout << main_menu();

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
    } while (!isValidOption(userInput, 1, 4));

    // if isValidOption passed, stoi(userInput) has already been tested and is safe
    return stoi(userInput);
}

// return t/f if userInput is a valid int between min and max
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
}

void display_trip(list<Goat> trip)
{
}
