#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> adj;
vector<int> color, disc, fin, parent;
int timer = 0;
bool hasCycle = false;

vector<int> BFS(int start)
{
    vector<bool> vis(n + 1, false);
    vector<int> order;
    queue<int> q;
    q.push(start);
    vis[start] = true;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u])
            if (!vis[v])
            {
                vis[v] = true;
                q.push(v);
            }
    }

    for (int i = 1; i <= n; ++i)
        if (!vis[i])
        {
            q.push(i);
            vis[i] = true;
            while (!q.empty())
            {
                int u = q.front();
                q.pop();
                order.push_back(u);
                for (int v : adj[u])
                    if (!vis[v])
                    {
                        vis[v] = true;
                        q.push(v);
                    }
            }
        }
    return order;
}

void DFS_visit(int u, bool directed)
{
    color[u] = 1;
    disc[u] = ++timer;

    for (int v : adj[u])
    {
        if (color[v] == 0)
        {
            cout << "Tree Edge: (" << u << " -> " << v << ")\n";
            parent[v] = u;
            DFS_visit(v, directed);
        }
        else if (color[v] == 1)
        {
            cout << "Back Edge: (" << u << " -> " << v << ")\n";
            if (directed)
                hasCycle = true;
            else if (parent[u] != v)
                hasCycle = true;
        }
        else if (color[v] == 2)
        {
            if (disc[u] < disc[v])
                cout << "Forward Edge: (" << u << " -> " << v << ")\n";
            else
                cout << "Cross Edge: (" << u << " -> " << v << ")\n";
        }
    }

    color[u] = 2;
    fin[u] = ++timer;
}

void DFS(bool directed)
{
    timer = 0;
    color.assign(n + 1, 0);
    disc.assign(n + 1, 0);
    fin.assign(n + 1, 0);
    parent.assign(n + 1, -1);
    hasCycle = false;

    for (int i = 1; i <= n; ++i)
        if (color[i] == 0)
            DFS_visit(i, directed);

    cout << "\nVertex : Discovery / Finish Time\n";
    for (int i = 1; i <= n; ++i)
        cout << i << " : " << disc[i] << " / " << fin[i] << "\n";
}

int main()
{
    cout << "Input format:\n";
    cout << "n m\nm lines: u v\nstart_vertex\ndirected_flag(0=undirected,1=directed)\n\n";

    if (!(cin >> n >> m))
        return 0;

    adj.assign(n + 1, {});
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    int start;
    cin >> start;
    int directed;
    cin >> directed;

    if (directed == 0)
    {
        vector<vector<int>> undirected(n + 1);
        for (int u = 1; u <= n; ++u)
            for (int v : adj[u])
            {
                undirected[u].push_back(v);
                undirected[v].push_back(u);
            }
        adj = undirected;
    }

    for (int i = 1; i <= n; ++i)
    {
        sort(adj[i].begin(), adj[i].end());
        adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
    }

    vector<int> bfs_order = BFS(start);
    cout << "\nBFS Order: ";
    for (int v : bfs_order)
        cout << v << " ";
    cout << "\n";

    cout << "\nDFS Traversal and Edge Classification:\n";
    DFS(directed);

    if (hasCycle)
        cout << "\nCycle detected in the graph.\n";
    else
        cout << "\nNo cycle detected in the graph.\n";

    return 0;
}
