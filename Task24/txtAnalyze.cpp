#include <bits/stdc++.h> // Include standard libraries for input/output and other utilities

using namespace std;

// Class to perform various quality-of-life text analysis functions
class qol {
public:
    // Check if a character is a vowel
    static bool isVowel(char letter)
    {
        const string vowels = "aeiou"; // Define vowels
        // Return true if the letter is in the vowels string (case insensitive)
        return vowels.find(tolower(letter)) != string::npos;
    }

    // Count the number of sentences in a given text
    static int findSentences(string text)
    {
        int sentences = 0; // Initialize sentence counter
        const string sentencePunctuator = ".!?"; // Define sentence punctuation
        // Iterate through each character in the text
        for (char c: text)
        {
            // Check if the character is a sentence-ending punctuation
            if (sentencePunctuator.find(c) != string::npos)
                sentences++; // Increment sentence counter
        }
        return sentences; // Return the total count of sentences
    }

    // Find the longest word in the given text
    static string findLongestWord(string text)
    {
        string longestWord = ""; // Variable to hold the longest word
        string currentWord = ""; // Variable to build the current word
        // Loop through each character in the text
        for (int i = 0; i <= text.length(); i++)
        {
            // Check if the character is alphabetic
            if (isalpha(text[i]))
            {
                currentWord += text[i]; // Add to the current word
            } else
            {
                // If the current word is longer than the longest found, update it
                if (currentWord.length() >= longestWord.length())
                {
                    longestWord = currentWord;
                }
                currentWord = ""; // Reset current word
            }
        }
        return longestWord; // Return the longest word found
    }
};

// Class to handle reading files into a string
class FileReader {
public:
    // Read the entire content of the specified file into a string
    static string readFileIntoString(const string &fileName)
    {
        string data; // Variable to hold file content
        ifstream file(fileName); // Open file for reading
        if (!file)
        {
            cerr << "Error: Could not open file at " << fileName << endl; // Error handling if file fails to open
            return ""; // Return empty string on error
        }
        stringstream buffer;
        buffer << file.rdbuf(); // Read the entire file content into the stringstream
        return buffer.str(); // Return the content as a string
    }
};

// Class to hold and analyze text data
class TextData {
private:
    string fileName; // File name
    string text; // Text content
    int numberOfVowels; // Count of vowels
    int numberOfConsonants; // Count of consonants
    int numberOfLetters; // Count of letters
    int numberOfSentences; // Count of sentences
    string longestWord; // Longest word in the text

    // Analyze the text to populate the various statistics
    void analyzeText()
    {
        int vowelCounter = 0; // Initialize vowel counter
        int consonantCounter = 0; // Initialize consonant counter
        int letterCounter = 0; // Initialize letter counter
        // Loop through each character in the text
        for (char c: text)
        {
            if (qol::isVowel(c)) // Check if the character is a vowel
            {
                vowelCounter++; // Increment vowel counter
            } else if (isalpha(c)) // If it's a letter but not a vowel
            {
                consonantCounter++; // Increment consonant counter
            }

            if (isalpha(c)) // If it's an alphabetic character
            {
                letterCounter++; // Increment letter counter
            }
        }

        // Assign counted values to class members
        numberOfVowels = vowelCounter;
        numberOfConsonants = consonantCounter;
        numberOfLetters = letterCounter;
        numberOfSentences = qol::findSentences(text); // Get sentence count
        longestWord = qol::findLongestWord(text); // Get longest word
    }

public:
    // Constructor that initializes text and file name and analyzes the text
    TextData(string text, string fileName) : text(text), fileName(fileName)
    {
        analyzeText(); // Call analyzeText to populate statistics
    }

    // Getter functions to access private data members
    string getFilename() const { return fileName; }
    string getText() const { return text; }
    int getNumberOfVowels() const { return numberOfVowels; }
    int getNumberOfConsonants() const { return numberOfConsonants; }
    int getNumberOfLetters() const { return numberOfLetters; }
    int getNumberOfSentences() const { return numberOfSentences; }
    string getLongestWord() const { return longestWord; }
};

// Main function
int main(int argc, char *argv[])
{
    // Step 1: Check if file path argument is provided
    if (argc < 2)
    {
        cerr << "Usage: " << argv[0] << " <file_path>" << endl; // Print usage message if no argument is provided
        return 1; // Exit with error code
    }

    // Step 2: Read the file into a string
    for (int i = 1; i < argc; i++) { // Start at 1 to skip the program name
        string filePath = argv[i];
        string fileContent = FileReader::readFileIntoString(filePath); // Read file content

        if (fileContent.empty()) { // Check for empty content (read failure)
            cerr << "Failed to read the file at " << filePath << std::endl;
            continue; // Move to the next file if there's a read failure
        }

        // Step 3: Create TextData object and analyze text
        TextData textData(fileContent, filePath); // Create TextData object

        // Step 4: Output the results
        cout << "File Name: " << textData.getFilename() << endl; // Print file name
        cout << "Text Content: " << textData.getText() << endl; // Print text content
        cout << "\nNumber of Vowels: " << textData.getNumberOfVowels() << endl; // Print number of vowels
        cout << "Number of Consonants: " << textData.getNumberOfConsonants() << endl; // Print number of consonants
        cout << "Number of Letters: " << textData.getNumberOfLetters() << endl; // Print number of letters
        cout << "Number of Sentences: " << textData.getNumberOfSentences() << endl; // Print number of sentences
        cout << "Longest Word: " << textData.getLongestWord() << endl; // Print longest word
    }

    return 0; // Exit program
}
