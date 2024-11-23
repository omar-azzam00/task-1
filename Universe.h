#include <string>
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
