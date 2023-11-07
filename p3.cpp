// Write a program to find the no of occurcences of any world in a file and replace that with another word

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    // Get the file name from the user.
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;

    // Open the file in read mode.
    fstream file(filename, ios::in);

    // Get the word to be replaced and the replacement word from the user.
    string word, replacement;
    cout << "Enter the word to be replaced: ";
    cin >> word;
    cout << "Enter the replacement word: ";
    cin >> replacement;

    // Initialize the number of occurrences to 0.
    int occurrences = 0;

    // Read the file line by line.
    string line;
    while (getline(file, line))
    {
        // Find the first occurrence of the word in the line.
        size_t pos = line.find(word);

        // If the word is found, increment the number of occurrences.
        if (pos != string::npos)
        {
            occurrences++;

            // Replace the word with the replacement word.
            line.replace(pos, word.length(), replacement);
        }
    }

    // Close the file.
    file.close();

    // Print the number of occurrences.
    cout << "The word '" << word << "' occurred " << occurrences << " times." << endl;

    return 0;
}
