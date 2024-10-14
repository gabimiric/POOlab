#include <iostream>
#include <string>
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
    bool isHumanoid = 0;
    string planet = " ";
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

int main() {
    cout << "Harro World" << endl;

    // Creating a passport object
    passport pass;
    pass.id = 2;
    pass.isHumanoid = true;
    pass.planet = "EARTH";
    pass.age = 18;
    pass.trait = BULKY;

    // Outputting of the details of the passport object
    cout << pass.id << ": Is this " << pass.traitToString() << " "
    << pass.age << " year old creature from " << pass.planet
    << " humanoid? " << (pass.isHumanoid ? "Yes" : "No") << endl;

    return 0;

    // ifstream f("example.json");
    // json data = json::parse(f);
    // string str = data.dump(1);
    // cout<< str << endl;
}