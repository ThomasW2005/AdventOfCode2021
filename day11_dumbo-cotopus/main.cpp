#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>
#include <string>

#define SIZE 10

struct octopus
{
    int energy = 0;
    bool hasFlashed = false;
};

void evolve(std::array<std::array<octopus, SIZE>, SIZE> &grid);
void displayArray(std::array<std::array<octopus, SIZE>, SIZE> grid);
void incrementNeighbors(std::array<std::array<octopus, SIZE>, SIZE> &grid, int i, int j);
void incrementEnergy(std::array<std::array<octopus, SIZE>, SIZE> &grid, int i, int j);
void flashCountToZero(std::array<std::array<octopus, SIZE>, SIZE> &grid);
bool isAllZero(std::array<std::array<octopus, SIZE>, SIZE> grid);

int flashes = 0;
int step = 0;

int main(int argc, char const *argv[])
{
    // read file into array
    std::array<std::array<octopus, SIZE>, SIZE> grid{};
    std::ifstream file("input.txt");
    std::string line;
    for (auto &x : grid)
    {
        std::getline(file, line);
        for (int i = 0; i < line.size(); i++)
            x[i].energy = line[i] - '0';
    }
    // puzzle 1:
    for (int i = 0; i < 100; i++)
        evolve(grid);
    std::cout << "total amount of flashes: " << flashes << '\n';
    // puzzle 2:
    while (!isAllZero(grid))
        evolve(grid);
    std::cout << "amount of steps after which all flashes syncronized: " << step << '\n';
    system("pause");
    return 0;
}

bool isAllZero(std::array<std::array<octopus, SIZE>, SIZE> grid)
{
    auto x = std::find_if(grid.begin(), grid.end(), [](std::array<octopus, SIZE> row)
                          { return std::find_if(row.begin(), row.end(), [](octopus octopus)
                                                { return octopus.energy != 0; }) != row.end(); });
    if (x != grid.end())
        return false;
    else
        return true;
}

void flashCountToZero(std::array<std::array<octopus, SIZE>, SIZE> &grid)
{
    std::for_each(grid.begin(), grid.end(), [](std::array<octopus, SIZE> &row)
                  { std::for_each(row.begin(), row.end(), [](octopus &cell)
                                  { cell.hasFlashed = false; }); });
}

void evolve(std::array<std::array<octopus, SIZE>, SIZE> &grid)
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            incrementEnergy(grid, i, j);
    flashCountToZero(grid);
    step++;
}

void incrementEnergy(std::array<std::array<octopus, SIZE>, SIZE> &grid, int i, int j)
{
    octopus &me = grid[i][j];
    if (me.hasFlashed)
        return;
    if (++me.energy > 9)
    {
        me.hasFlashed = true;
        me.energy = 0;
        flashes++;
        incrementNeighbors(grid, i, j);
    }
}

void incrementNeighbors(std::array<std::array<octopus, SIZE>, SIZE> &grid, int i, int j)
{
    for (int k = -1; k < 2; k++)
    {
        for (int l = -1; l < 2; l++)
        {
            if (k == 0 && l == 0)
                continue;
            if (i + k < 0 || i + k >= grid.size())
                continue;
            if (j + l < 0 || j + l >= grid[i].size())
                continue;
            incrementEnergy(grid, i + k, j + l);
        }
    }
}

void displayArray(std::array<std::array<octopus, SIZE>, SIZE> grid)
{
    std::cout << "\033[2J\033[1;1H";
    for (auto x : grid)
    {
        for (auto y : x)
            std::cout << y.energy << " ";
        std::cout << '\n';
    }
}
