#include <bits/stdc++.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// Enum definition
enum Trait {
    HAIRY,
    TALL,
    SHORT,
    BLONDE,
    EXTRA_ARMS,
    EXTRA_HEAD,
    GREEN,
    BULKY,
    POINTY_EARS
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

class Classifier {
    public:

    struct UniverseTraits {
        string name;
        string planet;
        int maxAge;
        bool isHumanoid;
        vector<string> requiredTraits;
    };

    // Function to classify individuals into a universe based on their age, planet, traits, and isHumanoid status
    static void classify(const vector<Passport>& passports)
    {
        // Reset existing files
        resetFiles();

        // Define the universes and their traits
        vector<UniverseTraits> universes =
        {
            {"starWars", "Kashyyyk", 400, false, {"HAIRY", "TALL"}},
            {"starWars", "Endor", 60, false, {"SHORT", "HAIRY"}},
            {"marvel", "Asgard", 5000, true, {"BLONDE", "TALL"}},
            {"hitchhiker", "Betelgeuse", 100, true, {"EXTRA_ARMS", "EXTRA_HEAD"}},
            {"hitchhiker", "Vogsphere", 200, false, {"GREEN", "BULKY"}},
            {"rings", "Earth", INT_MAX, true, {"BLONDE", "POINTY_EARS"}},
            {"rings", "Earth", 200, true, {"SHORT", "BULKY"}}
        };

        for (const auto& passport : passports)
        {
            string classification = classifyIndividual(passport, universes);
            if (classification != "Unknown Species")
                classifyJSON(passport, classification); // Classify and save to the appropriate universe file
        }
    }


    private:

    static string classifyIndividual(const Passport& passport, const vector<UniverseTraits>& universes)
    {
        for (const auto& universe : universes)
        {
            // Check if the passport meets the universe's criteria
            bool planetMatches = (passport.planet == universe.planet || passport.planet == "Unknown");
            bool ageMatches = (passport.age <= universe.maxAge || passport.age == 0);
            bool humanoidMatches = (passport.isHumanoid == universe.isHumanoid || passport.isHumanoid == false);
            bool traitsMatch = hasTraits(passport, universe.requiredTraits) || passport.traits.empty();

            // Classify if all criteria match
            if (planetMatches && ageMatches && humanoidMatches && traitsMatch) {
                return universe.name; // Return the universe name
            }
        }
        return "Unknown Species"; // Default case if no match found
    }


    // Helper function to check if the passport has at least one of the required traits
    static bool hasTraits(const Passport& passport, const vector<string>& requiredTraits) {
        vector<string> traitStrings = passport.traitToString();  // Get the string representation of traits
        for (const auto& trait : requiredTraits) {
            if (find(traitStrings.begin(), traitStrings.end(), trait) != traitStrings.end())
                return true;  // Return true if at least one required trait is present
        }
        return false;  // Return false if none of the required traits are found
    }


    // Function to append to the universe's JSON file
    static void classifyJSON(const Passport& passport, const string& universe)
    {
        string filename = universe + ".json";
        json jsonData;

        // Check if file exists
        ifstream infile(filename);
        if (infile.good()) {
            // File exists, read the existing data and append to it
            infile >> jsonData;
        }
        infile.close();

        // Create a JSON object for the current passport
        json passportData;
        passportData["id"] = passport.id;
        passportData["isHumanoid"] = passport.isHumanoid;
        passportData["planet"] = passport.planet;
        passportData["age"] = passport.age;
        passportData["traits"] = passport.traitToString();

        // Append the new passport to the existing universe data
        jsonData.push_back(passportData);

        // Write the updated data back to the file
        ofstream output(filename);
        output << jsonData.dump(2);  // Pretty print with 2 spaces indentation
        output.close();
    }

    // Function to delete/reset the files for the universes
    static void resetFiles() {
        // List of universe files to reset/delete
        const vector<string> universeFiles = {
            "starWars.json",
            "marvel.json",
            "hitchhiker.json",
            "rings.json"
        };

        // Iterate through the list and delete each file
        for (const auto& file : universeFiles) {
            if (remove(file.c_str()) == 0) {
                cout << "Deleted " << file << endl;
            } else {
                cout << "No existing file to delete: " << file << endl;
            }
        }
    }
};

int main() {
    JsonReader reader("input.json");

    // Read the JSON data
    if (reader.read()) {
        // Print the JSON data only if read was successful
        // reader.print();
    }

    vector<Passport> passports;
    // Map JSON data to Passport objects
    for (const auto& alien : reader.data["input"]) {
        passports.push_back(Passport::fromJson(alien)); // Create Passport and add to vector
    }

    Classifier::classify(passports);

    return 0;
}