#include <iostream>
#include <vector>
#include <climits>
using namespace std;

double optimalBST(vector<double>& p, int n) {
    vector<vector<double>> cost(n + 2, vector<double>(n + 1, 0));
    vector<vector<double>> sum(n + 2, vector<double>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        sum[i][i] = p[i - 1];
        for (int j = i + 1; j <= n; ++j)
            sum[i][j] = sum[i][j - 1] + p[j - 1];
    }

    for (int len = 1; len <= n; ++len) {
        for (int i = 1; i <= n - len + 1; ++i) {
            int j = i + len - 1;
            cost[i][j] = INT_MAX;
            for (int r = i; r <= j; ++r) {
                double left = (r > i) ? cost[i][r - 1] : 0;
                double right = (r < j) ? cost[r + 1][j] : 0;
                double total = left + right + sum[i][j];
                cost[i][j] = min(cost[i][j], total);
            }
        }
    }

    return cost[1][n];
}

int main() {
    vector<double> p = {0.2, 0.5, 0.3}; 
    int n = p.size();
    cout << "Minimum expected search cost: " << optimalBST(p, n) << endl;
    return 0;
}
