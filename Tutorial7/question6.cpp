#include <bits/stdc++.h>
using namespace std;

#define INF 999999
#define N 5

struct Node {
    vector<vector<int>> reducedMatrix;
    vector<int> path;
    int cost;
    int vertex;
    int level;
};

int reduceMatrix(vector<vector<int>>& mat) {
    int reduction = 0;
    int n = mat.size();

    for (int i = 0; i < n; i++) {
        int rowMin = INF;
        for (int j = 0; j < n; j++)
            if (mat[i][j] < rowMin)
                rowMin = mat[i][j];
        if (rowMin != INF && rowMin > 0) {
            reduction += rowMin;
            for (int j = 0; j < n; j++)
                if (mat[i][j] != INF)
                    mat[i][j] -= rowMin;
        }
    }

    for (int j = 0; j < n; j++) {
        int colMin = INF;
        for (int i = 0; i < n; i++)
            if (mat[i][j] < colMin)
                colMin = mat[i][j];
        if (colMin != INF && colMin > 0) {
            reduction += colMin;
            for (int i = 0; i < n; i++)
                if (mat[i][j] != INF)
                    mat[i][j] -= colMin;
        }
    }

    return reduction;
}

Node* newNode(vector<vector<int>> parentMatrix, vector<int> const &path,
              int level, int i, int j) {

    int n = parentMatrix.size();

    Node* node = new Node;
    node->reducedMatrix = parentMatrix;
    for (int k = 0; level != 0 && k < n; k++) {
        node->reducedMatrix[i][k] = INF; 
        node->reducedMatrix[k][j] = INF; 
    }
    node->reducedMatrix[j][0] = INF; 

    node->path = path;
    node->path.push_back(j);
    node->level = level;
    node->vertex = j;
    return node;
}

int calculateCost(Node* node, int costSoFar, int edgeCost) {
    int reductionCost = reduceMatrix(node->reducedMatrix);
    return costSoFar + edgeCost + reductionCost;
}

struct compare {
    bool operator()(Node* a, Node* b) {
        return a->cost > b->cost;
    }
};

void printPath(vector<int> const &path) {
    char cities[] = {'A', 'B', 'C', 'D', 'E'};
    for (int i : path)
        cout << cities[i] << " -> ";
    cout << cities[path[0]] << endl; 
}

int main() {
    vector<vector<int>> costMatrix = {
        {0, 10, 15, 20, 10},
        {10, 0, 35, 25, 17},
        {15, 35, 0, 30, 28},
        {20, 25, 30, 0, 22},
        {10, 17, 28, 22, 0}
    };

    priority_queue<Node*, vector<Node*>, compare> pq;
    vector<int> path = {0};

    Node* root = newNode(costMatrix, path, 0, -1, 0);
    root->cost = reduceMatrix(root->reducedMatrix);
    root->vertex = 0;

    pq.push(root);

    int nodesExpanded = 0;
    int bestCost = INF;
    vector<int> bestPath;

    while (!pq.empty()) {
        Node* minNode = pq.top();
        pq.pop();
        nodesExpanded++;

        int i = minNode->vertex;

        if (minNode->level == N - 1) {
            minNode->path.push_back(0);
            int totalCost = minNode->cost + costMatrix[i][0];
            if (totalCost < bestCost) {
                bestCost = totalCost;
                bestPath = minNode->path;
            }
            continue;
        }

        for (int j = 0; j < N; j++) {
            if (minNode->reducedMatrix[i][j] != INF) {
                Node* child = newNode(minNode->reducedMatrix, minNode->path,
                                      minNode->level + 1, i, j);
                child->cost = calculateCost(child, minNode->cost, costMatrix[i][j]);
                child->vertex = j;
                pq.push(child);
            }
        }
    }

    cout << "\nOptimal Tour: ";
    printPath(bestPath);
    cout << "Total Cost: " << bestCost << endl;
    cout << "Nodes Expanded: " << nodesExpanded << endl;
    return 0;
}
