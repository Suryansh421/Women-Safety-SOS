#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <string>

using namespace std;

struct SafeLocation
{
    int node;
    string name;
};

struct Edge
{
    int to;
    int distance;
    int risk;
};

void activateSOS()
{
    // mod 1
    cout << "SOS Activated successfully.\n";
    cout << "Emergency response procss started.\n\n";
}

int detectLocation(const vector<string> &locationNames)
{
    // mod 2
    cout << "Available locations:\n";

    for (int i = 0; i < (int)locationNames.size(); i++)
    {
        cout << i << " -> " << locationNames[i] << endl;
    }

    int currentLocation;
    cout << "Enter current locn node number: ";
    cin >> currentLocation;

    if (currentLocation < 0 || currentLocation >= (int)locationNames.size())
    {
        cout << "Invalid location entered. Defaulting to node 0.\n";
        return 0;
    }

    cout << "Detected Location: " << locationNames[currentLocation] << "\n\n";
    return currentLocation;
}

void identifyTrustedLocations(const vector<SafeLocation> &trustedLocations)
{
    // mod 3
    cout << "Trusted locations are:\n";

    for (const auto &loc : trustedLocations)
    {
        cout << loc.node << " -> " << loc.name << endl;
    }

    cout << endl;
}

void addEdge(vector<vector<Edge>> &graph, int u, int v, int distance, int risk)
{
    graph[u].push_back({v, distance, risk});
    graph[v].push_back({u, distance, risk});
}

pair<int, vector<int>> computeSafestRoute(const vector<vector<Edge>> &graph, int source, int destination)
{
    int V = graph.size();
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        int currentCost = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (currentCost > dist[u])
            continue;

        for (const auto &edge : graph[u])
        {
            int v = edge.to;
            int safetyCost = edge.distance + edge.risk;

            if (dist[u] + safetyCost < dist[v])
            {
                dist[v] = dist[u] + safetyCost;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    vector<int> path;
    if (dist[destination] == INT_MAX)
    {
        return {INT_MAX, path};
    }

    for (int v = destination; v != -1; v = parent[v])
    {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return {dist[destination], path};
}

int findBestTrustedLocation(const vector<vector<Edge>> &graph, int currentLocation, const vector<SafeLocation> &trustedLocations, vector<int> &bestPath)
{
    // mod 4

    int bestLocation = -1;
    int minCost = INT_MAX;

    for (const auto &loc : trustedLocations)
    {
        auto result = computeSafestRoute(graph, currentLocation, loc.node);
        int cost = result.first;

        if (cost < minCost)
        {
            minCost = cost;
            bestLocation = loc.node;
            bestPath = result.second;
        }
    }

    if (bestLocation != -1)
    {
        cout << "Safest Trusted Location Found: Node " << bestLocation << endl;
        cout << "Total Safety Cost: " << minCost << "\n\n";
    }

    return bestLocation;
}

void sendAlert(const string &guardianName, const string &guardianContact, int currentLocation, int safeLocation, const vector<string> &locationNames)
{
    // mod 5
    cout << "Sending alert...\n\n";

    cout << "----- ALERT MESSAGE -----\n";
    cout << "To: " << guardianName << " (" << guardianContact << ")\n";
    cout << "Emergency Alert! User may be in danger.\n";
    cout << "Current Location: " << locationNames[currentLocation] << endl;
    cout << "Nearest Safe Location: " << locationNames[safeLocation] << endl;
    cout << "Please respond immediately.\n";
    cout << "-------------------------\n\n";
}

void showRouteGuidance(const vector<int> &path, const vector<string> &locationNames)
{
    // mod 6

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

int main()
{
    activateSOS();

    vector<string> locationNames = {
        "College Road", "Main Market", "Bus Stand",
        "Police Station", "Hospital", "Girls Hostel", "Pharmacy"};

    int currentLocation = detectLocation(locationNames);

    vector<SafeLocation> trustedLocations = {
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