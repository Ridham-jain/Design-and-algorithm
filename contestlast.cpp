#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin>>t;
    for(int l=0;l<t;l++){

    int n;
    cin >> n;
    vector<long long> a(n), c(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> c[i];

    const long long INF = 1e18;
    vector<vector<long long>> dp(n, vector<long long>(2, INF));

    dp[0][0] = 0;        // not changed
    dp[0][1] = c[0];     // changed

    for (int i = 1; i < n; i++) {
        // Not change a[i]
        if (a[i-1] <= a[i]) dp[i][0] = min(dp[i][0], dp[i-1][0]);
        dp[i][0] = min(dp[i][0], dp[i-1][1]);  // previous changed

        // Change a[i]
        dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + c[i];
    }

    long long ans = min(dp[n-1][0], dp[n-1][1]);
    if (ans >= INF) ans = -1;
    cout << ans << "\n";}
    return 0;
}
