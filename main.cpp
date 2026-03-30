#include <iostream>
#include <vector>
#include "../include/sos_module.h"
#include "../include/location_module.h"
#include "../include/trusted_location_module.h"
#include "../include/safe_route_module.h"
#include "../include/alert_module.h"
#include "../include/route_guidance_module.h"

using namespace std;

int main()
{
    activateSOS();

    vector<string> locationNames =
        {
            "College Road", "Main Market", "Bus Stand",
            "Police Station", "Hospital", "Girls Hostel", "Pharmacy"};

    int currentLocation = detectLocation(locationNames);

    vector<SafeLocation> trustedLocations =
        {
            {3, "Police Station"},
            {4, "Hospital"},
            {5, "Girls Hostel"},
            {6, "Pharmacy"}};

    identifyTrustedLocations(trustedLocations);

    int V = 7;
    vector<vector<Edge>> graph(V);

    addEdge(graph, 0, 1, 4, 2);
    addEdge(graph, 0, 2, 6, 5);
    addEdge(graph, 1, 3, 5, 1);
    addEdge(graph, 1, 4, 7, 2);
    addEdge(graph, 2, 4, 3, 4);
    addEdge(graph, 2, 5, 5, 3);
    addEdge(graph, 4, 6, 2, 1);
    addEdge(graph, 5, 6, 3, 2);
    addEdge(graph, 3, 4, 2, 1);

    vector<int> bestPath;
    int bestSafeLocation = findBestTrustedLocation(graph, currentLocation, trustedLocations, bestPath);

    if (bestSafeLocation != -1)
    {
        sendAlert("Parent", "+91-9876543210", currentLocation, bestSafeLocation, locationNames);
        showRouteGuidance(bestPath, locationNames);
    }
    else
    {
        cout << "No safe route found.\n";
    }

    return 0;
}