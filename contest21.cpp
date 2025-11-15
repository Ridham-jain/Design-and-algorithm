#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        string m;
        cin >> m;

        long long A_count = count(m.begin(), m.end(), 'A');
        long long B_count = n - A_count;

        vector<long long> a(q);
        for (int i = 0; i < q; i++) cin >> a[i];

        for (int i = 0; i < q; i++) {
            long long x = a[i];
            long long steps = 0;

            while (x > 0) {
                if (x > A_count) {
                    long long tmp = x;
                    // Apply full cycle
                    for (char c : m) {
                        if (tmp == 0) break;
                        if (c == 'A') tmp -= 1;
                        else tmp /= 2;
                    }
                    if (tmp >= x) break; // safety check, shouldn't happen
                    x = tmp;
                    steps += n;
                } else {
                    for (char c : m) {
                        if (x == 0) break;
                        if (c == 'A') x -= 1;
                        else x /= 2;
                        steps++;
                    }
                }
            }

            cout << steps << "\n";
        }
    }
}
