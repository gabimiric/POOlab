#include <bits/stdc++.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// Enum definition
enum Trait {
    BLONDE,
    BULKY,
    EXTRA_ARMS,
    EXTRA_HEAD,
    GREEN,
    HAIRY,
    POINTY_EARS,
    SHORT,
    TALL
};

// Class definition
class Passport {
    public:

    int id = 0;
    bool isHumanoid = false;
    string planet = "Unknown";
    int age = 0;
    vector<Trait> traits;

    // Static function to create Passport from JSON object
    static Passport fromJson(const json& alien)
    {
        Passport passport;
        passport.id = alien["id"];
        passport.isHumanoid = alien.value("isHumanoid", false);
        passport.planet = alien.value("planet", "Unknown");
        passport.age = alien.value("age", 0);

        // Map traits from JSON to enum vector
        if (alien.contains("traits"))
        {
            for (const auto& trait : alien["traits"])
                passport.traits.push_back(stringToTrait(trait));
        }

        return passport;
    }

    // Function to convert traits vector to string representation
    vector<string> traitToString() const
    {
        vector<string> traitStrings; // To hold string representations of traits
        for (const auto& t : traits) { // Iterate over each trait
            switch (t) {
                case BLONDE: traitStrings.push_back("BLONDE"); break;
                case BULKY: traitStrings.push_back("BULKY"); break;
                case EXTRA_ARMS: traitStrings.push_back("EXTRA_ARMS"); break;
                case EXTRA_HEAD: traitStrings.push_back("EXTRA_HEAD"); break;
                case GREEN: traitStrings.push_back("GREEN"); break;
                case HAIRY: traitStrings.push_back("HAIRY"); break;
                case POINTY_EARS: traitStrings.push_back("POINTY_EARS"); break;
                case SHORT: traitStrings.push_back("SHORT"); break;
                case TALL: traitStrings.push_back("TALL"); break;
                default: traitStrings.push_back("UNKNOWN"); break; // Handle unknown traits
            }
        }
        return traitStrings; // Return the vector of trait strings
    }


    // Function to convert a string representation of a trait to the Trait enum
    static Trait stringToTrait(const string& trait)
    {
        if (trait == "BLONDE") return BLONDE;
        if (trait == "BULKY") return BULKY;
        if (trait == "EXTRA_ARMS") return EXTRA_ARMS;
        if (trait == "EXTRA_HEAD") return EXTRA_HEAD;
        if (trait == "GREEN") return GREEN;
        if (trait == "HAIRY") return HAIRY;
        if (trait == "POINTY_EARS") return POINTY_EARS;
        if (trait == "SHORT") return SHORT;
        if (trait == "TALL") return TALL;
        throw invalid_argument("Unknown trait: " + trait);
    }
};

class JsonReader
{
    public:
    json data;
    string filename;

    // Constructor that accepts the filename
    JsonReader(const string filename) : filename(filename) {}

    // Function to read the JSON file and store the content
    bool read()
    {
        // Open the JSON file
        ifstream inputFile(filename);
        if (!inputFile.is_open())
        {
            cerr << "Could not open the file: " << filename << endl;
            return false; // Indicate failure
        }

        // Parse the JSON file
        try {
            inputFile >> data; // Store the parsed JSON data
        } catch (const json::parse_error& e) {
            cerr << "JSON parse error: " << e.what() << endl;
            return false; // Indicate failure
        }

        // Close the file
        inputFile.close();
        return true; // Indicate success
    }

    // Function to print the stored JSON data
    void print() const
    {
        cout << data.dump(2) << endl; // Pretty print with 2 spaces indentation
    }

    // Function to print details of an alien by ID
    void printAlienById(int id) const
    {
        for (const auto& alien : data["input"])
        {
            if (alien["id"] == id)
                {
                cout << "Alien Details (ID: " << id << "):" << endl;
                cout << "Is Humanoid: " << (alien.value("isHumanoid", false) ? "Yes" : "No") << endl;
                cout << "Planet: " << alien.value("planet", "Unknown") << endl;
                cout << "Age: " << alien.value("age", 0) << endl;
                cout << "Traits: ";

                if (alien.contains("traits"))
                {
                    for (const auto& trait : alien["traits"])
                        cout << trait << " ";
                }
                cout << endl; // New line after printing traits
                return; // Exit after printing the found alien
            }
        }
        cout << "No alien found with ID: " << id << endl; // If no alien is found
    }
};

// Class to print Passports
class PassportPrinter {
public:
    /**
      * Prints passport IDs based on specified criteria.
      *
      * @param passports The vector of Passport objects to print IDs from.
      * @param printType Specifies the type of IDs to print:
      *                  0 - All IDs
      *                  1 - Odd IDs
      *                  2 - Even IDs
      * @param ascending If true, prints IDs in ascending order; if false, in descending order.
      */
    static void printIDs(const vector<Passport>& passports, int printType = 0, bool ascending = true)
    {
        vector<int> ids;

        // Collect relevant IDs based on printType
        for (const auto& passport : passports)
        {
            if (printType == 0 || (printType == 1 && passport.id % 2 != 0) || (printType == 2 && passport.id % 2 == 0))
                ids.push_back(passport.id);
        }

        // Sort IDs in ascending or descending order
        if (ascending) {
            sort(ids.begin(), ids.end());
        } else {
            sort(ids.rbegin(), ids.rend()); // Sort in descending order
        }

        // Print the collected IDs
        cout << "\nPassport IDs:" << endl;
        for (const auto& id : ids)
            cout << id << " ";
    }

};

int main() {
    JsonReader reader("input.json");

    // Read the JSON data
    if (reader.read()) {
        // Print the JSON data only if read was successful
        // reader.print();
    }

    // Access the filename directly if needed
    // cout << "Reading from: " << reader.filename << endl;

    vector<Passport> passports;
    // Map JSON data to Passport objects
    for (const auto& alien : reader.data["input"]) {
        passports.push_back(Passport::fromJson(alien)); // Create Passport and add to vector
    }

    // Print IDs
    PassportPrinter::printIDs(passports, 0, true);  // All IDs, ascending
    PassportPrinter::printIDs(passports, 0, false); // All IDs, descending
    PassportPrinter::printIDs(passports, 1, true);  // Odd IDs, ascending
    PassportPrinter::printIDs(passports, 1, false); // Odd IDs, descending
    PassportPrinter::printIDs(passports, 2, true);  // Even IDs, ascending
    PassportPrinter::printIDs(passports, 2, false); // Even IDs, descending


    return 0;
}