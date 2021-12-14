#include <iostream>
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
    std::array<std::array<octopus, SIZE>, SIZE> grid{{{8, false, 5, false, 4, false, 8, false, 3, false, 3, false, 5, false, 6, false, 4, false, 4, false},
                                                      {6, false, 5, false, 7, false, 6, false, 5, false, 2, false, 1, false, 7, false, 8, false, 2, false},
                                                      {1, false, 2, false, 2, false, 3, false, 6, false, 7, false, 7, false, 7, false, 6, false, 2, false},
                                                      {1, false, 2, false, 8, false, 4, false, 7, false, 1, false, 3, false, 1, false, 1, false, 3, false},
                                                      {6, false, 1, false, 2, false, 5, false, 6, false, 5, false, 4, false, 7, false, 7, false, 8, false},
                                                      {6, false, 4, false, 3, false, 5, false, 7, false, 2, false, 6, false, 8, false, 4, false, 2, false},
                                                      {5, false, 6, false, 6, false, 4, false, 1, false, 7, false, 5, false, 5, false, 5, false, 6, false},
                                                      {1, false, 4, false, 4, false, 5, false, 7, false, 3, false, 6, false, 5, false, 5, false, 6, false},
                                                      {2, false, 2, false, 4, false, 8, false, 4, false, 7, false, 3, false, 5, false, 6, false, 8, false},
                                                      {6, false, 4, false, 5, false, 1, false, 4, false, 7, false, 3, false, 5, false, 2, false, 6, false}}};

    while (1)
    {
        evolve(grid);
        step++;
        if (isAllZero(grid))
            break;
    }
    displayArray(grid);
    std::cout << "All flashes are gone after " << step << " steps";
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
