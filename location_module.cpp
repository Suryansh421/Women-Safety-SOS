#include <iostream>
#include <vector>
#include <string>
#include "../include/location_module.h"

using namespace std;

int detectLocation(const vector<string> &locationNames)
{
    cout << "Location Detection Module\n";
    cout << "Available locations:\n";

    for (int i = 0; i < (int)locationNames.size(); i++)
    {
        cout << i << " -> " << locationNames[i] << endl;
    }

    int currentLocation;
    cout << "Enter current location node number: ";
    cin >> currentLocation;

    if (currentLocation < 0 || currentLocation >= (int)locationNames.size())
    {
        cout << "Invalid location entered. Defaulting to node 0.\n";
        return 0;
    }

    cout << "Detected Location: " << locationNames[currentLocation] << "\n\n";
    return currentLocation;
}