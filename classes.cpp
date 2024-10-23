#include <bits/stdc++.h>

using namespace std;

class Display {
    private:
    int height;  // in pixels
    int width;   // in pixels
    float ppi;   // pixels per inch
    string model; // model name

    public:
    // Constructor to initialize the display object with height, width, ppi, and model
    Display(int height, int width, float ppi, string model) : height(height), width(width), ppi(ppi), model(model) {}

    // Method to compare the sizes of two displays
    void compareSize(Display name)
    {
        // Convert height and width from pixels to inches
        float widthInInches1 = width / ppi;
        float heightInInches1 = height / ppi;
        float widthInInches2 = name.width / name.ppi;
        float heightInInches2 = name.height / name.ppi;

        // Compute the area in square inches
        float area1 = widthInInches1 * heightInInches1;
        float area2 = widthInInches2 * heightInInches2;

        // Variables to store results
        float winArea, lossArea;
        string winModel, lossModel;

        // Compare areas and determine which monitor is larger
        if (area1 != area2)
        {
            if (area1 > area2)
            {
                winArea = area1;
                lossArea = area2;
                winModel = model;
                lossModel = name.model;
            } else
            {
                winArea = area2;
                lossArea = area1;
                winModel = name.model;
                lossModel = model;
            }

            // Print the result in square inches
            printf("The monitor %s has a larger screen size than the model %s. "
                   "\nIt is larger by %.2f in^2 or %.2f%%."
                   "\nThe monitor %s has an area of %.2f in^2 and %s - %.2f in^2.\n",
                   winModel.c_str(), lossModel.c_str(), winArea - lossArea, (lossArea/winArea) * 100,
                   winModel.c_str(), winArea, lossModel.c_str(), lossArea);
        } else
        {
            printf("The monitors %s and %s have the exact same size. "
                   "\nEach has an area of %.2f in^2.\n",
                   name.model.c_str(), model.c_str(), area1);
        }
    }

    // Method to compare the sharpness of two displays based on PPI
    void compareSharpness(Display name)
    {
        // Initialize variables
        int sharp1 = ppi;
        int sharp2 = name.ppi;

        // Variables to store results
        int winSharp, lossSharp;
        string winModel, lossModel;

        // Compare sharpness and determine which monitor is sharper
        if (sharp1 != sharp2)
        {
            if (sharp1 > sharp2)
            {
                winSharp = sharp1;
                lossSharp = sharp2;
                winModel = model;
                lossModel = name.model;
            } else
            {
                winSharp = sharp2;
                lossSharp = sharp1;
                winModel = name.model;
                lossModel = model;
            }

            printf("The monitor %s has a sharper image than the model %s."
                "\nTheir difference is %d ppi.\n"
                ,winModel.c_str(), lossModel.c_str(), winSharp-lossSharp);
        }else
        {
            printf("The monitors %s and %s have the same sharpness."
                "\nTheir ppi is %d.\n"
                ,model.c_str(), name.model.c_str(), ppi);
        }
    }

    // Method to compare both size and sharpness of two displays
    void compareWithMonitor(Display name)
    {
        cout<<endl;
        compareSize(name);     // Compare size
        compareSharpness(name); // Compare sharpness
    }
};

int main()
{
    // Instantiate display objects with dimensions in pixels and PPI
    Display monitor1(1440, 2560, 93, "LG 32GN650-B");
    Display monitor2(1080, 1920, 92, "Samsung F24T350FHI");
    Display monitor3(2160, 3840, 163, "Dell UltraSharp U2720Q");
    Display monitor4(1080, 2560, 140, "ASUS ProArt PA32UCX");
    Display monitor5(1440, 2560, 109, "BenQ PD3220U");

    // Compare monitors
    monitor1.compareWithMonitor(monitor2);
    monitor3.compareWithMonitor(monitor4);
    monitor5.compareWithMonitor(monitor1);
    monitor2.compareWithMonitor(monitor5);

    return 0;
}
