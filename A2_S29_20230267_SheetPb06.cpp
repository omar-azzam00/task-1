// Omar Mostafa Saad - 20230267 - S29
// OOP A2 Task1.2 Problem 6
// 2024 - 11 - 23

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

#define DEAD '.'
#define ALIVE '*'

class Universe
{
private:
    vector<vector<char>> array;
    int currentStep, ROWS, COLUMNS;

    int getInteger(string prompt);
    void initializeRandom();
    void initializeFromFile();
    void reset();
    int count_neighbors(int row, int column);
    char determineCell(int row, int column);
    void next_generation();
    void removeArray();
    bool display(bool init);

public:
    void run();
    Universe();
    ~Universe();
};

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
    array.resize(ROWS);
    for (int i = 0; i < ROWS; i++)
    {
        array[i].resize(COLUMNS);
        for (int j = 0; j < COLUMNS; j++)
        {
            array[i][j] = DEAD;
        }
    }
}

Universe::Universe()
{
}

Universe::~Universe()
{
}

void Universe::initializeRandom()
{
    int t = time(NULL);
    srand(t);

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            bool true_or_false = ((double)rand() / RAND_MAX) <= (1.0 / 3);
            array[i][j] = true_or_false ? ALIVE : DEAD;
        }
    }
}

void Universe::initializeFromFile()
{
    string line;
    ifstream file;

    while (true)
    {
        cout << "Enter the name of the file: ";
        getline(cin, line);
        file.open(line);

        if (!file)
        {
            cout << "Error in opening file \"" << line << "\", try again" << endl;
        }
        else
        {
            break;
        }
    }

    if (!getline(file, line))
    {
        cout << "Error in the format of the file!" << endl;
        exit(1);
    }

    stringstream ss(line);

    if (!(ss >> ROWS))
    {
        cout << "Error in the format of the file!" << endl;
        exit(1);
    };

    if (!(ss >> COLUMNS))
    {
        cout << "Error in the format of the file!" << endl;
        exit(1);
    };

    reset();

    cout << COLUMNS << endl;
    cout << ROWS << endl;

    int i = 0;
    while (getline(file, line))
    {
        if (line.length() != COLUMNS || i == array.size())
        {
            cout << "Error in the format of the file!" << endl;
            exit(1);
        }

        for (int j = 0; j < COLUMNS; j++)
        {
            if (line[j] == '0')
            {
                array[i][j] = DEAD;
            }
            else if (line[j] == '1')
            {
                array[i][j] = ALIVE;
            }
            else
            {
                cout << "Error in the format of the file!" << endl;
                exit(1);
            }
        }
        i++;
    }

    if (i != ROWS)
    {
        cout << "Error in the format of the file!" << endl;
        exit(1);
    }
};

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

bool Universe::display(bool init = false)
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
        cout << "THIS IS THE THE START UP UNIVERSE" << endl;
    }
    else
    {
        cout << "STEP " << currentStep << endl;
    }

    cout << "WRITE Q TO EXIT OR ANY OTHER THING TO CONTINUE: ";
    string input;
    getline(cin, input);
    if (input.length() == 1 && tolower(input[0]) == 'q')
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Universe::run()
{
    system("cls");

    reset();

    cout << "WELCOME TO GAME OF LIFE\n";
    cout << "note that '" << DEAD << "' means a dead cell while '" << ALIVE << "' means a liv one.\n"
         << endl;

    int choice;

    while (true)
    {
        choice = getInteger("Do you want a (1)random pattern or (2)one from a file (1 or 2):  ");
        if (choice < 1 || choice > 2)
        {
            cout << "Invalid, choice must be only 1 or 2." << endl;
        }
        else
        {
            break;
        }
    }
    currentStep = 0;
    cout << endl;
    bool cont;
    if (choice == 1)
    {
        while (true)
        {
            choice = getInteger("Do you want (1)20x20, (2)30x30 or (3)20x50: ");
            if (choice == 1)
            {
                ROWS = 20;
                COLUMNS = 20;
                break;
            }
            else if (choice == 2)
            {
                ROWS = 30;
                COLUMNS = 30;
                break;
            }
            else if (choice == 3)
            {
                ROWS = 20;
                COLUMNS = 50;
                break;
            }
            else
            {
                cout << "Invalid, choice must be only 1, 2 or 3." << endl;
            }
        }
        reset();
        initializeRandom();
        cont = display(true);
    }
    else
    {
        initializeFromFile();
        cont = display(true);
    }

    if (!cont)
    {
        return;
    }

    do
    {
        next_generation();
        currentStep++;
    } while (display());
}

int main()
{
    Universe universe;

    universe.run();
}