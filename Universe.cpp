#include <iostream>
#include "Universe.h"
#include <sstream>

using namespace std;

int Universe::getInteger(std::string prompt)
{
    int value;
    std::string line;
    while (true)
    {
        std::cout << prompt;
        getline(std::cin, line);
        std::istringstream stream(line);
        stream >> value;
        if (!stream.fail() && stream.eof())
            break;
        std::cout << "Illegal integer format. Try again." << std::endl;
        if (prompt == "")
            prompt = "Enter an integer: ";
    }
    return value;
}

void Universe::reset()
{
    fill_n(&array[0][0], ROWS * COLUMNS, DEAD);
}

Universe::Universe()
{
    reset();
}

Universe::~Universe()
{
}

void Universe::initialize()
{
    int t = time(NULL);
    srand(t);

    for (int i = ROWS / 2.5; i < ROWS / 2.5 + 4; i++)
    {
        for (int j = COLUMNS / 2.5; j < COLUMNS / 2.5 + 4; j++)
        {
            bool true_or_false = rand() >= (RAND_MAX / 2);
            array[i][j] = true_or_false ? ALIVE : DEAD;
        }
    }
}

int Universe::count_neighbors(int row, int column)
{
    int neighbors = 0;
    if (row > 0 && column > 0 && array[row - 1][column - 1] == ALIVE)
    {
        neighbors++;
    }
    if (row > 0 && array[row - 1][column] == ALIVE)
    {
        neighbors++;
    }
    if (row > 0 && column < COLUMNS - 1 && array[row - 1][column + 1] == ALIVE)
    {
        neighbors++;
    }
    if (column > 0 && array[row][column - 1] == ALIVE)
    {
        neighbors++;
    }
    if (column < COLUMNS - 1 && array[row][column + 1] == ALIVE)
    {
        neighbors++;
    }
    if (row < ROWS - 1 && column > 0 && array[row + 1][column - 1] == ALIVE)
    {
        neighbors++;
    }
    if (row < ROWS - 1 && array[row + 1][column] == ALIVE)
    {
        neighbors++;
    }
    if (row < ROWS - 1 && column < COLUMNS - 1 && array[row + 1][column + 1] == ALIVE)
    {
        neighbors++;
    }
    return neighbors;
}

char Universe::determineCell(int row, int column)
{
    if (array[row][column] == ALIVE)
    {
        if (count_neighbors(row, column) == 2 || count_neighbors(row, column) == 3)
        {
            return ALIVE;
        }
        else
        {
            return DEAD;
        }
    }
    else
    {
        if (count_neighbors(row, column) == 3)
        {
            return ALIVE;
        }
        else
        {
            return DEAD;
        }
    }
}

void Universe::next_generation()
{
    char new_array[ROWS][COLUMNS];

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            new_array[i][j] = determineCell(i, j);
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            array[i][j] = new_array[i][j];
        }
    }
}

void Universe::display(bool init = false)
{
    system("CLS");

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            cout << array[i][j] << " ";
        }
        cout << '\n';
    }
    cout << '\n';

    if (init)
    {
        cout << "This is the start up universe." << endl;
        cout << "PRESS ENTER TO CONTINUE";
    }
    else
    {
        cout << "Step " << currentStep << " from " << steps << " steps." << endl;
        cout << "PRESS ENTER TO CONTINUE";
    }

    string input;
    getline(cin, input);
}

void Universe::run()
{
    system("cls");

    reset();

    cout << "WELCOME TO GAME OF LIFE\n";
    cout << "note that '.' means a dead cell while '*' means a live one.\n"
         << endl;

    while (true)
    {
        steps = getInteger("How many steps you want: ");
        if (steps <= 0)
        {
            cout << "Steps must be bigger than 0." << endl;
        }
        else
        {
            break;
        }
    }
    currentStep = 1;
    cout << endl;

    initialize();
    display(true);
    while (currentStep <= steps)
    {
        next_generation();
        display();
        currentStep++;
    }
}