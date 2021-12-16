#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int mostCommonBitAtIndex(std::vector<int> array, int index, int length);

int main(int argc, char const *argv[])
{
    // read input
    std::ifstream file("input.txt");
    std::vector<int> input;
    char c;
    int numberLength = 0;
    while (file.peek() != EOF)
    {
        unsigned int num = 0;
        numberLength = 0;
        while (file.get(c))
        {
            numberLength++;
            if (c == '\n')
                break;
            num = num << 1 | (c - '0');
        }
        input.push_back(num);
    }
    // puzzle 1:
    unsigned int num = 0;
    for (int i = 0; i < numberLength; i++)
    {
        int mcbai = mostCommonBitAtIndex(input, i, numberLength);
        num = num << 1 | mcbai;
    }
    std::cout << num * (~num & ~(0xffffffff << numberLength)) << '\n';
    // puzzle 2:
    auto input2 = input;

    for (int i = 0; i < numberLength && input2.size() > 1; i++)
    {
        int mcn = mostCommonBitAtIndex(input, i, numberLength);
        input.erase(std::remove_if(input.begin(), input.end(), [&](int x)
                                   { if (((x & (1 << numberLength - i - 1)) == 0 ? 0 : 1) == !mcn) return 1; else return 0; }),
                    input.end());
    }

    for (int i = 0; i < numberLength && input2.size() > 1; i++)
    {
        int mcn = !mostCommonBitAtIndex(input2, i, numberLength);
        input2.erase(std::remove_if(input2.begin(), input2.end(), [&](int x)
                                    { if (((x & (1 << numberLength - i - 1)) == 0 ? 0 : 1) == !mcn) return 1; else return 0; }),
                     input2.end());
    }

    std::cout << input2[0] * input[0] << '\n';

    system("pause");
}

int mostCommonBitAtIndex(std::vector<int> array, int index, int length)
{
    int sum = 0;
    for (auto x : array)
        sum += (x & (1 << length - index - 1)) == 0 ? 0 : 1;
    if (array.size() == sum * 2)
        return 1;
    return (array.size() - sum < sum);
}