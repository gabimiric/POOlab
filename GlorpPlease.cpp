#include <bits/stdc++.h>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

// Enum definition
enum trait {
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
class passport {
    public:

    int id = 0;
    bool isHumanoid = false;
    string planet = "Unknown";
    int age = 0;
    trait trait = BLONDE;

    // Function to map trait enum to string
    string traitToString() const {
        switch(trait) {
            case BLONDE: return "BLONDE";
            case BULKY: return "BULKY";
            case EXTRA_ARMS: return "EXTRA_ARMS";
            case EXTRA_HEAD: return "EXTRA_HEAD";
            case GREEN: return "GREEN";
            case HAIRY: return "HAIRY";
            case POINTY_EARS: return "POINTY_EARS";
            case SHORT: return "SHORT";
            case TALL: return "TALL";
            default: return "UNKNOWN";
        }
    }
};

class JsonReader {
    public:
    json data;
    string filename;

    // Constructor that accepts the filename
    JsonReader(const string filename) : filename(filename) {}

    // Function to read the JSON file and store the content
    bool read() {
        // Open the JSON file
        ifstream inputFile(filename);
        if (!inputFile.is_open()) {
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
    void print() const {
        cout << data.dump(2) << endl; // Pretty print with 4 spaces indentation
    }

    // Function to print details of an alien by ID
    void printAlienById(int id) const {
        for (const auto& alien : data["input"]) {
            if (alien["id"] == id) {
                cout << "Alien Details (ID: " << id << "):" << endl;
                cout << "Is Humanoid: " << (alien.value("isHumanoid", false) ? "Yes" : "No") << endl;
                cout << "Planet: " << alien.value("planet", "Unknown") << endl;
                cout << "Age: " << alien.value("age", 0) << endl;
                cout << "Traits: ";
                if (alien.contains("traits")) {
                    for (const auto& trait : alien["traits"]) {
                        cout << trait << " ";
                    }
                }
                cout << endl; // New line after printing traits
                return; // Exit after printing the found alien
            }
        }
        cout << "No alien found with ID: " << id << endl; // If no alien is found
    }
};

int main() {
    JsonReader reader("input.json");

    // Read the JSON data
    if (reader.read()) {
        // Print the JSON data only if read was successful
        reader.print();
    }

    // Access the filename directly if needed
    cout << "Reading from: " << reader.filename << endl;
    reader.printAlienById(2);

    return 0;
}