#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& st) {
    visited[node] = true;
    for (int nei : adj[node]) {
        if (!visited[nei])
            dfs(nei, adj, visited, st);
    }
    st.push(node);
}

int main() {
    int V = 6;
    vector<vector<int>> adj(V);

    adj[5] = {2, 0};
    adj[4] = {0, 1};
    adj[2] = {3};
    adj[3] = {1};

    vector<bool> visited(V, false);
    stack<int> st;

    for (int i = 0; i < V; i++) {
        if (!visited[i])
            dfs(i, adj, visited, st);
    }

    cout << "Topological Ordering: ";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << endl;

    return 0;
}
