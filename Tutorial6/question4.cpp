#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>
using namespace std;

void dijkstra(int n, int src, const vector<vector<pair<int, int>>> &adj, int target = -1) {
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "\n(a) Dijkstra’s Shortest Paths (Non-Negative Weights):\n";
    for (int i = 0; i < n; i++) {
        cout << "Distance from " << src << " -> " << i << " = " << dist[i] << endl;
    }

    if (target != -1) {
        cout << "\nShortest Path to Target " << target << ": ";
        vector<int> path;
        for (int v = target; v != -1; v = parent[v])
            path.push_back(v);
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i];
            if (i) cout << " -> ";
        }
        cout << endl;
    }
}

void bellmanFord(int n, int src, const vector<tuple<int, int, int>> &edges) {
    vector<int> dist(n, INT_MAX);
    dist[src] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (auto e : edges) {
            int u, v, w;
            tie(u, v, w) = e;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    bool negCycle = false;
    for (auto e : edges) {
        int u, v, w;
        tie(u, v, w) = e;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            negCycle = true;
            break;
        }
    }

    cout << "\n(b) Bellman-Ford Shortest Paths (Handles Negative Weights):\n";
    if (negCycle) {
        cout << "Graph contains a negative weight cycle!\n";
    } else {
        for (int i = 0; i < n; i++) {
            cout << "Distance from " << src << " -> " << i << " = " << dist[i] << endl;
        }
    }
}

void floydWarshall(int n, vector<vector<int>> dist) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "\n(c) Floyd-Warshall All-Pairs Shortest Paths:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INT_MAX)
                cout << setw(6) << "INF";
            else
                cout << setw(6) << dist[i][j];
        }
        cout << endl;
    }

    bool negCycle = false;
    for (int i = 0; i < n; i++) {
        if (dist[i][i] < 0) {
            negCycle = true;
            break;
        }
    }

    if (negCycle)
        cout << "Negative weight cycle detected!\n";
    else
        cout << "No negative weight cycle detected.\n";
}

int main() {
    int n = 5;

    vector<vector<pair<int, int>>> adj(n);
    adj[0].push_back({1, 10});
    adj[0].push_back({4, 5});
    adj[1].push_back({2, 1});
    adj[4].push_back({1, 3});
    adj[4].push_back({2, 9});
    adj[4].push_back({3, 2});
    adj[3].push_back({2, 4});

    dijkstra(n, 0, adj, 3);

    vector<tuple<int, int, int>> edges = {
        {0, 1, 6}, {0, 2, 7},
        {1, 2, 8}, {1, 3, 5}, {1, 4, -4},
        {2, 3, -3}, {2, 4, 9},
        {3, 1, -2},
        {4, 0, 2}, {4, 3, 7}
    };

    bellmanFord(5, 0, edges);

    vector<vector<int>> matrix = {
        {0, 3, 8, INT_MAX, -4},
        {INT_MAX, 0, INT_MAX, 1, 7},
        {INT_MAX, 4, 0, INT_MAX, INT_MAX},
        {2, INT_MAX, -5, 0, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 6, 0}
    };

    floydWarshall(5, matrix);

    return 0;
}
