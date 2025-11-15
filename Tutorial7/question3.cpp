#include <iostream>
#include <vector>
using namespace std;

#define N 6

int graph[N + 1][N + 1] = {
    {0},
    {0, 0, 1, 1, 0, 0, 1},
    {0, 1, 0, 1, 0, 1, 0},
    {0, 1, 1, 0, 1, 0, 0},
    {0, 0, 0, 1, 0, 1, 0},
    {0, 0, 1, 0, 1, 0, 1},
    {0, 1, 0, 0, 0, 1, 0}
};

int path[N + 1];   

bool isSafe(int v, int pos) {
    if (graph[path[pos - 1]][v] == 0)
        return false;

    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool hamiltonianCycle(int pos) {
    if (pos == N) {

        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    for (int v = 2; v <= N; v++) { 
        if (isSafe(v, pos)) {
            path[pos] = v;
            if (hamiltonianCycle(pos + 1))
                return true;
            path[pos] = -1; 
        }
    }

    return false;
}

int main() {
    for (int i = 0; i <= N; i++)
        path[i] = -1;

    path[0] = 1;

    if (hamiltonianCycle(1)) {
        cout << "Hamiltonian Cycle found: ";
        for (int i = 0; i < N; i++)
            cout << path[i] << " ";
        cout << path[0] << endl; 
    } else {
        cout << "none" << endl;
    }

    return 0;
}
