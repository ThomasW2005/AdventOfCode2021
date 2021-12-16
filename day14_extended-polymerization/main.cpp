#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>

struct rule
{
    char before;
    char after;
    char insert;
};

void showRules(std::vector<rule> rules);
void polyStep(std::vector<rule> rules, std::string &polyTemplate);
int mostAndLeastCommonElemenSubtracted(std::string polyTemplate);

int main(int argc, char const *argv[])
{
    // read in rules and polymer template
    std::vector<rule> rules;
    std::string polyTemplate = "";
    std::ifstream file("input_example.txt");
    std::getline(file, polyTemplate);
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line))
        rules.push_back({line[0], line[1], line[6]});
    // puzzle 1:
    for (int i = 0; i < 12; i++)
    {
        polyStep(rules, polyTemplate);
        std::cout << polyTemplate << '\n';
        mostAndLeastCommonElemenSubtracted(polyTemplate);
        // std::cout << "Puzzle 1:\ndifference between most and least common elements: " << mostAndLeastCommonElemenSubtracted(polyTemplate) << '\n';
        system("pause");
        // system("cls");
    }
    system("pause");
    return 0;
}

int mostAndLeastCommonElemenSubtracted(std::string polyTemplate)
{
    // The trick: The std::map::operator[] inserts an element if the key is not yet there. So, there are two cases: The key is not yet there: The element is created as { key, 0 } and the value (.second of the element) is incremented immediately which results in { key, 1 }. The key is already there: The value (.second of the element) is incremented again.
    std::map<char, int> elements;
    for (auto c : polyTemplate)
        ++elements[c];
    // print out the elements
    for (auto element : elements)
        std::cout << element.first << ": " << element.second << '\n';

    auto minmax = std::minmax_element(elements.begin(), elements.end(), [](const std::pair<char, int> &a, const std::pair<char, int> &b)
                                      { return a.second < b.second; });
    std::cout << "sol:" << minmax.second->second - minmax.first->second << '\n';
    return minmax.second->second - minmax.first->second;
}

void showRules(std::vector<rule> rules)
{
    for (auto rule : rules)
        std::cout << rule.before << ":" << rule.after << "->" << rule.insert << '\n';
}

void polyStep(std::vector<rule> rules, std::string &polyTemplate)
{
    // string for the keys to insert
    std::string newPoly = "";

    int size = polyTemplate.size();
    // match every char against the rules, if it matches, insert the key, if none mathc insert a space
    for (int i = 0; i < size - 1; i++)
    {
        bool foundRule = false;
        for (auto rule : rules)
        {
            if (polyTemplate[i] == rule.before && polyTemplate[i + 1] == rule.after)
            {
                newPoly += rule.insert;
                foundRule = true;
            }
        }
        if (!foundRule)
            newPoly += " ";
    }
    // merge the keys into the polymer
    long double durSum = 0;
    for (int i = 0; i < size - 1; i++)
        polyTemplate.insert(2 * i + 1, 1, newPoly[i]);

    // remove the spaces
    polyTemplate.erase(std::remove_if(polyTemplate.begin(), polyTemplate.end(), isspace), polyTemplate.end());
}