#include <string>

#define DEAD '.'
#define ALIVE '*'
#define ROWS 20
#define COLUMNS 20

class Universe
{
private:
    char array[ROWS][COLUMNS];
    int steps;
    int currentStep;

    int getInteger(std::string prompt);
    void initialize();
    void reset();
    int count_neighbors(int row, int column);
    char determineCell(int row, int column);
    void next_generation();
    void removeArray();
    void display(bool init);

public:
    void run();
    Universe();
    ~Universe();
};
