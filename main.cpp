/*
    OBJECTIVES
    Task One: See Goat.h
    Task Two: Write a GM3K1 engine that loops on this menu.
        Write a main_menu() function that outputs this and then obtains, validates, and returns the user's choice.
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
int main_menu();

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

    main_menu();

    return 0;
}

// main menu fuction for Task 2
int main_menu()
{

    // output prompt
    cout << "*** GOAT MANAGER 3001 ***" << endl
        << "[1] Add a goat" << endl
        << "[2] Delete a goat" << endl
        << "[3] List goats" << endl
        << "[4] Quit" << endl
        << "Choice --> ";

    return 0;
}
