#include <iostream>
#include <vector>
#include "../include/trusted_location_module.h"

using namespace std;

void identifyTrustedLocations(const vector<SafeLocation> &trustedLocations)
{
    cout << "Trusted Location Identification Module" << endl;
    cout << "Trusted locations are:\n";
    for (const auto &loc : trustedLocations)
    {
        cout << loc.node << " -> " << loc.name << endl;
    }
    cout << endl;
}