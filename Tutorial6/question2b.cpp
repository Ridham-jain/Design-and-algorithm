#include <bits/stdc++.h>
using namespace std;

void dfs1(int v, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[v] = true;
    for (int u : adj[v])
        if (!visited[u])
            dfs1(u, adj, visited, st);
    st.push(v);
}

void dfs2(int v, vector<vector<int>>& rev, vector<bool>& visited, vector<int>& comp) {
    visited[v] = true;
    comp.push_back(v);
    for (int u : rev[v])
        if (!visited[u])
            dfs2(u, rev, visited, comp);
}

int main() {
    int V = 5;
    vector<vector<int>> adj(V);
    adj[0] = {2, 3};
    adj[1] = {0};
    adj[2] = {1};
    adj[3] = {4};
    adj[4] = {};

    stack<int> st;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfs1(i, adj, visited, st);

    vector<vector<int>> rev(V);
    for (int v = 0; v < V; v++)
        for (int u : adj[v])
            rev[u].push_back(v);

    fill(visited.begin(), visited.end(), false);
    cout << "Strongly Connected Components:\n";
    while (!st.empty()) {
        int v = st.top(); st.pop();
        if (!visited[v]) {
            vector<int> comp;
            dfs2(v, rev, visited, comp);
            for (int x : comp) cout << x << " ";
            cout << endl;
        }
    }
    return 0;
}
