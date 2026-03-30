#include <iostream>
#include <vector>
#include <string>
#include "../include/route_guidance_module.h"

using namespace std;

void showRouteGuidance(const vector<int> &path, const vector<string> &locationNames)
{
    cout << "Route Guidance Module\n";

    if (path.empty())
    {
        cout << "No route available.\n";
        return;
    }

    cout << "Safest Route:\n";
    for (int i = 0; i < (int)path.size(); i++)
    {
        cout << locationNames[path[i]];
        if (i != (int)path.size() - 1)
        {
            cout << " -> ";
        }
    }
    cout << "\n";
}