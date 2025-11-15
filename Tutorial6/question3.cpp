#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>
using namespace std;

struct Edge {
    int u, v, w;
};

struct DisjointSet {
    vector<int> parent;
    DisjointSet(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a != b)
            parent[b] = a;
    }
};

pair<vector<Edge>, int> kruskal(int n, vector<Edge>& edges) {
    DisjointSet ds(n);
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.w < b.w;
    });

    vector<Edge> mst;
    int totalWeight = 0;

    for (auto e : edges) {
        if (ds.find(e.u) != ds.find(e.v)) {
            ds.unite(e.u, e.v);
            mst.push_back(e);
            totalWeight += e.w;
        }
    }

    return make_pair(mst, totalWeight);
}

pair<vector<Edge>, int> prim(int n, vector<vector<pair<int, int>>>& adj, int start = 0) {
    vector<bool> visited(n, false);
    vector<Edge> mst;
    int totalWeight = 0;

    typedef tuple<int, int, int> T; 
    priority_queue<T, vector<T>, greater<T>> pq;

    visited[start] = true;

    for (size_t i = 0; i < adj[start].size(); i++) {
        int v = adj[start][i].first;
        int w = adj[start][i].second;
        pq.push(make_tuple(w, start, v));
    }

    while (!pq.empty() && mst.size() < n - 1) {
        T top = pq.top();
        pq.pop();
        int w = get<0>(top);
        int u = get<1>(top);
        int v = get<2>(top);

        if (visited[v]) continue;
        visited[v] = true;

        Edge e;
        e.u = u;
        e.v = v;
        e.w = w;
        mst.push_back(e);
        totalWeight += w;

        for (size_t i = 0; i < adj[v].size(); i++) {
            int next = adj[v][i].first;
            int weight = adj[v][i].second;
            if (!visited[next])
                pq.push(make_tuple(weight, v, next));
        }
    }

    return make_pair(mst, totalWeight);
}

int main() {
    int n = 5;
    vector<Edge> edges = {
        {0, 1, 1},
        {1, 2, 1},
        {2, 3, 2},
        {0, 2, 3},
        {3, 4, 3},
        {1, 3, 4},
        {2, 4, 5}
    };

    pair<vector<Edge>, int> resultKruskal = kruskal(n, edges);
    vector<Edge> mstKruskal = resultKruskal.first;
    int weightKruskal = resultKruskal.second;

    cout << "Kruskal's MST:\n";
    for (size_t i = 0; i < mstKruskal.size(); i++) {
        cout << char('A' + mstKruskal[i].u) << " - "
             << char('A' + mstKruskal[i].v) << " : "
             << mstKruskal[i].w << "\n";
    }
    cout << "Total Weight = " << weightKruskal << "\n\n";

    vector<vector<pair<int, int>>> adj(n);
    for (size_t i = 0; i < edges.size(); i++) {
        adj[edges[i].u].push_back(make_pair(edges[i].v, edges[i].w));
        adj[edges[i].v].push_back(make_pair(edges[i].u, edges[i].w));
    }

    pair<vector<Edge>, int> resultPrim = prim(n, adj, 0);
    vector<Edge> mstPrim = resultPrim.first;
    int weightPrim = resultPrim.second;

    cout << "Prim's MST:\n";
    for (size_t i = 0; i < mstPrim.size(); i++) {
        cout << char('A' + mstPrim[i].u) << " - "
             << char('A' + mstPrim[i].v) << " : "
             << mstPrim[i].w << "\n";
    }
    cout << "Total Weight = " << weightPrim << "\n";

    return 0;
}
