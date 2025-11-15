#include <iostream>
#include <vector>
#include <string>
#include <climits>
using namespace std;

int minCut(string s) {
    int n = s.size();
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    vector<int> dp(n, 0);

    for (int end = 0; end < n; ++end) {
        for (int start = 0; start <= end; ++start) {
            if (s[start] == s[end] && (end - start <= 2 || isPal[start+1][end-1])) {
                isPal[start][end] = true;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (isPal[0][i]) {
            dp[i] = 0; 
        } else {
            int minCuts = INT_MAX;
            for (int j = 0; j < i; ++j) {
                if (isPal[j+1][i]) {
                    minCuts = min(minCuts, dp[j] + 1);
                }
            }
            dp[i] = minCuts;
        }
    }

    return dp[n-1];
}

int main() {
    string s;
    cout << "Enter string: ";
    cin >> s;

    int result = minCut(s);
    cout << "Minimum cuts needed: " << result << endl;

    return 0;
}
