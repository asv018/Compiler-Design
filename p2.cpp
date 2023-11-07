// Write a program to search the number of occurrences of any word , string and subsequence in the given string
#include <iostream>
#include <string>
using namespace std;

int countOccurrences(const std::string &text, const std::string &target)
{
    int occurrences = 0;
    size_t pos = 0;

    while ((pos = text.find(target, pos)) != std::string::npos)
    {
        occurrences++;
        pos += target.length();
    }

    return occurrences;
}

int main()
{
    std::string inputString;
    std::cout << "Enter the input string: ";
    std::getline(std::cin, inputString);

    std::string word;
    std::cout << "Enter the word to search: ";
    std::cin >> word;

    int wordOccurrences = countOccurrences(inputString, word);
    std::cout << "Occurrences of the word '" << word << "': " << wordOccurrences << std::endl;

    std::string subsequence;
    std::cout << "Enter the subsequence to search: ";
    std::cin >> subsequence;

    int subsequenceOccurrences = countOccurrences(inputString, subsequence);
    std::cout << "Occurrences of the subsequence '" << subsequence << "': " << subsequenceOccurrences << std::endl;

    return 0;
}
