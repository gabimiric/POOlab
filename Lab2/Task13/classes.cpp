#include <bits/stdc++.h> // Includes all standard libraries

using namespace std;

// Class representing a display/monitor with characteristics like height, width, PPI, and model
class Display {
private:
    int height; // Display height in pixels
    int width; // Display width in pixels
    float ppi; // Pixels per inch (sharpness measure)
    string model; // Model name of the display

public:
    // Constructor to initialize the display object with height, width, ppi, and model
    Display(int height, int width, float ppi, string model)
        : height(height), width(width), ppi(ppi), model(model) {}

    // Overloaded equality operator to compare two Display objects based on their properties
    bool operator==(const Display &other) const
    {
        return height == other.height &&
               width == other.width &&
               ppi == other.ppi &&
               model == other.model;
    }

    // Function to return a string representing the display's specifications
    string printDisplay()
    {
        return "Model: " + model + "\n"
               "Height: " + to_string(height) + "\n"
               "Width: " + to_string(width) + "\n"
               "PPI: " + to_string(int(ppi)) + "\n";
    }

    // Method to compare the sizes of two displays and output the result
    void compareSize(Display name)
    {
        // Convert height and width from pixels to inches
        float widthInInches1 = width / ppi;
        float heightInInches1 = height / ppi;
        float widthInInches2 = name.width / name.ppi;
        float heightInInches2 = name.height / name.ppi;

        // Calculate the display area in square inches
        float area1 = widthInInches1 * heightInInches1;
        float area2 = widthInInches2 * heightInInches2;

        // Variables to store result details
        float winArea, lossArea;
        string winModel, lossModel;

        // Compare areas to determine which display is larger
        if (area1 != area2)
        {
            if (area1 > area2) // If current display is larger
            {
                winArea = area1;
                lossArea = area2;
                winModel = model;
                lossModel = name.model;
            }
            else // If the other display is larger
            {
                winArea = area2;
                lossArea = area1;
                winModel = name.model;
                lossModel = model;
            }

            // Print the result in square inches and percentage difference
            printf("The monitor %s has a larger screen size than the model %s. "
                   "\nIt is larger by %.2f in^2 or %.2f%%."
                   "\nThe monitor %s has an area of %.2f in^2 and %s - %.2f in^2.\n",
                   winModel.c_str(), lossModel.c_str(), winArea - lossArea, (lossArea / winArea) * 100,
                   winModel.c_str(), winArea, lossModel.c_str(), lossArea);
        }
        else // If displays are the same size
        {
            printf("The monitors %s and %s have the exact same size. "
                   "\nEach has an area of %.2f in^2.\n",
                   name.model.c_str(), model.c_str(), area1);
        }
    }

    // Method to compare the sharpness (PPI) of two displays
    void compareSharpness(Display name)
    {
        // Initialize sharpness values for each display
        int sharp1 = ppi;
        int sharp2 = name.ppi;

        // Variables to store result details
        int winSharp, lossSharp;
        string winModel, lossModel;

        // Compare sharpness to determine which display has higher PPI
        if (sharp1 != sharp2)
        {
            if (sharp1 > sharp2) // If current display is sharper
            {
                winSharp = sharp1;
                lossSharp = sharp2;
                winModel = model;
                lossModel = name.model;
            }
            else // If the other display is sharper
            {
                winSharp = sharp2;
                lossSharp = sharp1;
                winModel = name.model;
                lossModel = model;
            }

            // Print the result showing the PPI difference
            printf("The monitor %s has a sharper image than the model %s."
                   "\nTheir difference is %d ppi.\n"
                   , winModel.c_str(), lossModel.c_str(), winSharp - lossSharp);
        }
        else // If displays have the same sharpness
        {
            printf("The monitors %s and %s have the same sharpness."
                   "\nTheir ppi is %d.\n"
                   , model.c_str(), name.model.c_str(), ppi);
        }
    }

    // Method to compare both size and sharpness of two displays
    void compareWithMonitor(Display name)
    {
        cout << endl;
        compareSize(name); // Compare size
        compareSharpness(name); // Compare sharpness
    }
};

// Class to manage a collection of display objects and assist with comparisons
class Assistant {
private:
    string assistantName; // Name of the assistant
    vector<Display> assignedDisplays; // Collection of assigned displays

public:
    // Method to add a display to the assistant's collection
    void assignDisplay(Display d)
    {
        assignedDisplays.push_back(d);
    }

    // Method to compare all assigned displays in pairs
    void assist()
    {
        // Compare each display with every other display in the collection
        for (int i = 0; i < assignedDisplays.size(); i++)
            for (int j = i + 1; j < assignedDisplays.size(); j++)
            {
                assignedDisplays[i].compareWithMonitor(assignedDisplays[j]);
            }
    }

    // Method to 'buy' a display by removing it from the collection
    Display buyDisplay(Display d)
    {
        // Find the display in the collection
        auto it = find(assignedDisplays.begin(), assignedDisplays.end(), d);
        if (it != assignedDisplays.end())
        {
            Display boughtDisplay = *it; // Copy the found display
            assignedDisplays.erase(it); // Remove it from the collection
            return boughtDisplay;
        }

        throw runtime_error("Display doesn't exist"); // Display not found
    }
};

int main()
{
    // Instantiate the Assistant object
    Assistant assistant;

    // Create multiple display objects with different specifications
    Display monitor1(1440, 2560, 93, "LG 32GN650-B");
    Display monitor2(1080, 1920, 92, "Samsung F24T350FHI");
    Display monitor3(2160, 3840, 163, "Dell UltraSharp U2720Q");
    Display monitor4(1080, 2560, 140, "ASUS ProArt PA32UCX");
    Display monitor5(1440, 2560, 109, "BenQ PD3220U");

    // Assign the displays to the assistant
    assistant.assignDisplay(monitor1);
    assistant.assignDisplay(monitor2);
    assistant.assignDisplay(monitor3);
    assistant.assignDisplay(monitor4);
    assistant.assignDisplay(monitor5);

    // Perform comparisons between all assigned displays
    assistant.assist();

    // Buy a display from the assistant's collection and print its details
    Display boughtDisplay = assistant.buyDisplay(monitor1);
    cout << "\nBought display:\n" << boughtDisplay.printDisplay() << endl;

    return 0;
}
