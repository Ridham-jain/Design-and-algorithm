# include <iostream>
# include <vector>
# include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> memo;

    int dp(int k, int n) {
        if (n == 0 || n == 1) return n;
        if (k == 1) return n; 

        if (memo[k][n] != -1) return memo[k][n];

        int low = 1, high = n, res = n;

        while (low <= high) {
            int mid = (low + high) / 2;

            int broken = dp(k - 1, mid - 1);     
            int notBroken = dp(k, n - mid);      

            int worst = 1 + max(broken, notBroken);
            res = min(res, worst);

            if (broken > notBroken) {
                high = mid - 1; 
            } else {
                low = mid + 1;  
            }
        }

        return memo[k][n] = res;
    }

    int superEggDrop(int k, int n) {
        memo = vector<vector<int>>(k + 1, vector<int>(n + 1, -1));
        return dp(k, n);
    }
};

int main() {
    Solution sol;
    int k = 2; 
    int n = 10; 
    cout << "Minimum attempts needed: " << sol.superEggDrop(k, n) << endl;
    return 0;
}
