#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char const *argv[])
{
    int horizontalPostion = 0;
    int depth = 0;
    // puzzle 1:
    std::ifstream file("input.txt");
    std::string line;
    while (std::getline(file, line))
    {
        switch (line[0])
        {
        case 'd':
            depth += line.at(5) - '0';
            break;
        case 'u':
            depth -= line.at(3) - '0';
            break;
        case 'f':
            horizontalPostion += line.at(8) - '0';
            break;
        }
    }
    std::cout << "Puzzle 1:\nFinal horizontal position: " << horizontalPostion << std::endl;
    std::cout << "Final depth: " << depth << std::endl;
    std::cout << "Product: " << depth * horizontalPostion << std::endl;
    // puzzle 2:
    file.clear();
    file.seekg(0, std::ios::beg);
    int aim = 0;
    horizontalPostion = 0;
    depth = 0;
    while (std::getline(file, line))
    {
        switch (line[0])
        {
        case 'd':
            aim += line.at(5) - '0';
            break;
        case 'u':
            aim -= line.at(3) - '0';
            break;
        case 'f':
            int num = line.at(8) - '0';
            horizontalPostion += num;
            depth += aim * num;
            break;
        }
    }
    std::cout << "Puzzle 2:\nFinal horizontal position: " << horizontalPostion << std::endl;
    std::cout << "Final depth: " << depth << std::endl;
    std::cout << "Final aim: " << aim << std::endl;
    std::cout << "Product: " << depth * horizontalPostion << std::endl;
    system("pause");
    return 0;
}