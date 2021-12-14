#include <iostream>
#include <vector>
#include <fstream>
#include <string>

void printVector(std::vector<int> arr)
{
    for (auto x : arr)
        std::cout << x << '\n';
    std::cout << std::endl;
}

int main(int argc, char const *argv[])
{
    // read input into vector
    std::vector<int> input;
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file, line))
        input.push_back(std::stoi(line));
    // printVector(input);
    // puzzle 1:
    int count = 0;
    int last = input[0];
    for (auto x : input)
    {
        if (x > last)
            count++;
        last = x;
    }
    std::cout << "Puzzle 1: amount of measurements that are larger than the previous measurement: " << count << '\n';
    // puzzle 2:
    count = 0;
    last = input[0] + input[1] + input[2];
    for (int i = 0; i < input.size() - 2; i++)
    {
        int sum = input[i] + input[i + 1] + input[i + 2];
        if (sum > last)
            count++;
        last = sum;
    }
    std::cout << "Puzzle 2: amount of measurements that are larger than the previous measurement: " << count << '\n';
    getchar();
    return 0;
}