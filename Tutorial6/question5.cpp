#include <bits/stdc++.h>
using namespace std;


struct EKResult {
    int maxflow;
    vector<vector<int>> residual; 
    vector<vector<int>> augmenting_paths; 
    vector<int> bottlenecks;
};

EKResult edmondsKarpLog(vector<vector<int>> capacity, int s, int t) {
    int n = capacity.size();
    vector<vector<int>> residual = capacity;
    int maxflow = 0;
    vector<vector<int>> paths;
    vector<int> bottlenecks;

    while (true) {
        vector<int> parent(n, -1);
        queue<int>q;
        parent[s] = s;
        q.push(s);

        while (!q.empty() && parent[t] == -1) {
            int u = q.front(); q.pop();
            for (int v = 0; v < n; ++v) {
                if (parent[v] == -1 && residual[u][v] > 0) {
                    parent[v] = u;
                    q.push(v);
                    if (v == t) break;
                }
            }
        }

        if (parent[t] == -1) break; 

        vector<int> path;
        int v = t;
        int bottleneck = INT_MAX;
        while (v != s) {
            int u = parent[v];
            path.push_back(v);
            bottleneck = min(bottleneck, residual[u][v]);
            v = u;
        }
        path.push_back(s);
        reverse(path.begin(), path.end());

        v = t;
        while (v != s) {
            int u = parent[v];
            residual[u][v] -= bottleneck;
            residual[v][u] += bottleneck;
            v = u;
        }

        maxflow += bottleneck;
        paths.push_back(path);
        bottlenecks.push_back(bottleneck);
    }

    return {maxflow, residual, paths, bottlenecks};
}

vector<int> minCutFromResidual(const vector<vector<int>>& residual, int s) {
    int n = residual.size();
    vector<int> vis(n, 0);
    queue<int> q;
    q.push(s); vis[s]=1;
    while (!q.empty()) {
        int u=q.front(); q.pop();
        for (int v=0; v<n; ++v) {
            if (!vis[v] && residual[u][v]>0) {
                vis[v]=1; q.push(v);
            }
        }
    }
    return vis; 
}


vector<pair<int,int>> bipartiteMatchingExample() {
    int U = 3, V = 2;
    int source = 0, sink = U+V+1;
    int n = sink+1;
    vector<vector<int>> cap(n, vector<int>(n,0));

    for (int i=1;i<=U;i++) cap[source][i]=1;
    cap[1][U+1]=1; 
    cap[1][U+2]=1; 
    cap[2][U+1]=1; 
    cap[3][U+2]=1; 
    for (int j=U+1;j<=U+V;j++) cap[j][sink]=1;

    EKResult res = edmondsKarpLog(cap, source, sink);

    vector<pair<int,int>> matches;
    for (int i=1;i<=U;i++) {
        for (int j=U+1;j<=U+V;j++) {
            if (cap[i][j]>0 && res.residual[i][j]==0) { 
                matches.push_back({i, j-U});
            }
        }
    }
    return matches;
}


struct MC_Edge {
    int to;
    int rev;  
    int cap;
    int cost;
};

struct MinCostMaxFlow {
    int n;
    vector<vector<MC_Edge>> adj;
    MinCostMaxFlow(int n):n(n), adj(n){}
    void addEdge(int u,int v,int cap,int cost){
        MC_Edge a={v,(int)adj[v].size(),cap,cost};
        MC_Edge b={u,(int)adj[u].size(),0,-cost};
        adj[u].push_back(a);
        adj[v].push_back(b);
    }

    pair<int,int> minCostMaxFlow(int s,int t,int maxf = INT_MAX){
        int flow=0, flowCost=0;
        vector<int> dist(n), pv(n), pe(n), inq(n);
        while (flow < maxf) {
            fill(dist.begin(), dist.end(), INT_MAX);
            fill(inq.begin(), inq.end(),0);
            dist[s]=0;
            queue<int> q;
            q.push(s); inq[s]=1;
            while(!q.empty()){
                int u=q.front(); q.pop(); inq[u]=0;
                for (int i=0;i<(int)adj[u].size();++i) {
                    MC_Edge &e = adj[u][i];
                    if (e.cap>0 && dist[u]+e.cost < dist[e.to]) {
                        dist[e.to] = dist[u]+e.cost;
                        pv[e.to]=u; pe[e.to]=i;
                        if(!inq[e.to]){ inq[e.to]=1; q.push(e.to); }
                    }
                }
            }
            if (dist[t]==INT_MAX) break;
            int addf = maxf - flow;
            int v=t;
            while (v!=s) {
                MC_Edge &e = adj[pv[v]][pe[v]];
                addf = min(addf, e.cap);
                v = pv[v];
            }
            v = t;
            while (v!=s) {
                MC_Edge &e = adj[pv[v]][pe[v]];
                e.cap -= addf;
                adj[v][e.rev].cap += addf;
                v = pv[v];
            }
            flow += addf;
            flowCost += addf * dist[t];
        }
        return {flow, flowCost};
    }
};


void printMatrix(const vector<vector<int>>& mat, const string& title) {
    cout << title << "\n";
    int n = mat.size();
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            cout << setw(4) << mat[i][j];
        }
        cout << "\n";
    }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "=== (A) Max Flow: Edmonds-Karp demo ===\n\n";
    int nA = 6;
    vector<vector<int>> capA(nA, vector<int>(nA,0));
    capA[0][1]=16; capA[0][2]=13;
    capA[1][2]=10; capA[2][1]=4;
    capA[1][3]=12; capA[3][2]=9;
    capA[2][4]=14; capA[4][3]=7;
    capA[3][5]=20; capA[4][5]=4;

    EKResult resA = edmondsKarpLog(capA, 0, 5);
    cout << "Max flow value = " << resA.maxflow << "\n\n";

    cout << "Augmenting paths and bottlenecks (in order):\n";
    for (size_t i=0;i<resA.augmenting_paths.size();++i) {
        for (size_t j=0;j<resA.augmenting_paths[i].size();++j) {
            cout << resA.augmenting_paths[i][j] << (j+1<resA.augmenting_paths[i].size() ? " -> " : "");
        }
        cout << "   bottleneck = " << resA.bottlenecks[i] << "\n";
    }
    cout << "\nFinal residual capacity matrix (rows = from, cols = to):\n";
    printMatrix(resA.residual, "Residual capacities:");

    auto Sset = minCutFromResidual(resA.residual, 0);
    cout << "\nMin-cut partitions: S = { ";
    for (int i=0;i<nA;i++) if (Sset[i]) cout << i << " ";
    cout << "}  T = { ";
    for (int i=0;i<nA;i++) if (!Sset[i]) cout << i << " ";
    cout << "}\n";
    int cutCap=0;
    for (int u=0;u<nA;u++) for (int v=0;v<nA;v++) {
        if (Sset[u] && !Sset[v]) cutCap += capA[u][v];
    }
    cout << "Min-cut capacity = " << cutCap << "\n\n";

    cout << "=== (B) Bipartite Matching via Max Flow ===\n\n";
    vector<pair<int,int>> matches = bipartiteMatchingExample();
    cout << "Matched pairs (left_index, right_index):\n";
    for (auto p: matches) cout << "(" << p.first << "," << p.second << ")\n";
    cout << "Matching size = " << matches.size() << "\n\n";

    cout << "=== (C) Minimum-Cost Maximum Flow demo ===\n\n";
    int nC = 5;
    MinCostMaxFlow mcmf(nC);
    mcmf.addEdge(0,1,3,1);
    mcmf.addEdge(0,2,2,2);
    mcmf.addEdge(1,2,1,0);
    mcmf.addEdge(1,3,2,3);
    mcmf.addEdge(2,3,2,1);
    mcmf.addEdge(3,4,4,1);

    pair<int,int> resC = mcmf.minCostMaxFlow(0,4);
    cout << "Max flow (min-cost) value = " << resC.first << "\n";
    cout << "Total minimum cost = " << resC.second << "\n";

    cout << "\nFinal flows on edges (u -> v : flow/capacity, cost):\n";
    for (int u=0;u<nC; ++u) {
        for (size_t i=0; i<mcmf.adj[u].size(); ++i) {
            MC_Edge &e = mcmf.adj[u][i];
            int v = e.to;
            int flowSent = mcmf.adj[v][e.rev].cap; 
            int totalCap = flowSent + e.cap; 
            if (totalCap>0 && !(u==v)) {
                if (mcmf.adj[v][e.rev].cap > 0) {
                    cout << u << " -> " << v << " : flow = " << flowSent << ", cap = " << totalCap 
                         << ", cost = " << e.cost << "\n";
                }
            }
        }
    }

    cout << "\nDone.\n";
    return 0;
}
