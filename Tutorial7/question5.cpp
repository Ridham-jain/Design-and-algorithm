#include <bits/stdc++.h>
using namespace std;

struct Item {
    int profit, weight;
    double ratio;
};

struct Node {
    int level;
    int profit;
    int weight;
    double bound;
    vector<int> taken;
};

struct cmp {
    bool operator()(const Node& a, const Node& b) {
        return a.bound < b.bound;
    }
};

double bound(Node u, int n, int C, vector<Item>& items) {
    if (u.weight >= C) return 0;

    double result = u.profit;
    int j = u.level;
    int totWeight = u.weight;

    while (j < n && totWeight + items[j].weight <= C) {
        totWeight += items[j].weight;
        result += items[j].profit;
        j++;
    }

    if (j < n)  
        result += (C - totWeight) * items[j].ratio;

    return result;
}

int main() {
    int C = 9;
    vector<Item> items = {{20,2}, {30,5}, {35,7}, {12,3}, {3,1}};
    int n = items.size();

    for (auto &it : items)
        it.ratio = (double)it.profit / it.weight;

    sort(items.begin(), items.end(),
         [](Item& a, Item& b) { return a.ratio > b.ratio; });

    priority_queue<Node, vector<Node>, cmp> pq;

    Node u, v;
    int nodesExpanded = 0, nodesPruned = 0;
    double maxProfit = 0;
    vector<int> bestTaken;

    v.level = 0;
    v.profit = 0;
    v.weight = 0;
    v.taken = vector<int>(n, 0);
    v.bound = bound(v, n, C, items);

    pq.push(v);

    while (!pq.empty()) {
        v = pq.top();
        pq.pop();
        nodesExpanded++;

        if (v.bound <= maxProfit) {
            nodesPruned++;
            continue;
        }

        u.level = v.level + 1;

        if (u.level < n) {
            u.weight = v.weight + items[u.level].weight;
            u.profit = v.profit + items[u.level].profit;
            u.taken = v.taken;
            u.taken[u.level] = 1;

            if (u.weight <= C && u.profit > maxProfit) {
                maxProfit = u.profit;
                bestTaken = u.taken;
            }

            u.bound = bound(u, n, C, items);
            if (u.bound > maxProfit)
                pq.push(u);
            else
                nodesPruned++;

            u.weight = v.weight;
            u.profit = v.profit;
            u.taken = v.taken;
            u.taken[u.level] = 0;
            u.bound = bound(u, n, C, items);

            if (u.bound > maxProfit)
                pq.push(u);
            else
                nodesPruned++;
        }
    }

    cout << "Optimal profit = " << maxProfit << endl;
    cout << "Items taken (in sorted ratio order): ";
    for (int i = 0; i < n; i++)
        if (bestTaken[i])
            cout << "(p=" << items[i].profit << ", w=" << items[i].weight << ") ";
    cout << endl;

    cout << "Nodes expanded: " << nodesExpanded << endl;
    cout << "Nodes pruned: " << nodesPruned << endl;

    return 0;
}
