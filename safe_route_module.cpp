#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include "../include/safe_route_module.h"
using namespace std;

void addEdge(vector<vector<Edge>> &graph, int u, int v, int distance, int risk)
{
    graph[u].push_back({v, distance, risk});
    graph[v].push_back({u, distance, risk}); // this us undirected graph
}

pair<int, vector<int>> computeSafestRoute(const vector<vector<Edge>> &graph, int source, int destination) // to find safest
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

    int bestLocation = -1;
    int minCost = INT_MAX;

    for (const auto &loc : trustedLocations) // to find nearest trusted locn
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
        cout << "Total Safety Cost: " << minCost << "\n"
             << endl;
    }

    return bestLocation;
}