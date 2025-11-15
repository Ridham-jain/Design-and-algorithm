#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (!(cin >> t)) {
        cerr << "Failed to read t\n";
        return 1;
    }

    while (t--) {
        int n;
        if (!(cin >> n)) {
            cerr << "Failed to read n\n";
            return 1;
        }

        vector<vector<int>> arrays(n);
        int maxLength = 0;

        for (int i = 0; i < n; i++) {
            int k;
            if (!(cin >> k)) {
                cerr << "Failed to read k at array " << i << "\n";
                return 1;
            }

            arrays[i].resize(k);
            for (int j = 0; j < k; j++) {
                if (!(cin >> arrays[i][j])) {
                    cerr << "Failed to read element " << j << " of array " << i << "\n";
                    return 1;
                }
            }
            maxLength = max(maxLength, k);
        }

        sort(arrays.begin(), arrays.end(), [](const vector<int> &a, const vector<int> &b) {
            return a.size() < b.size();
        });

        vector<int> bottomRow(maxLength);

        for (int col = 0; col < maxLength; col++) {
            for (int i = 0; i < n; i++) {
                if (col < (int)arrays[i].size()) {
                    bottomRow[col] = arrays[i][col];
                    break;
                }
            }
        }

        for (int i = 0; i < maxLength; i++) {
            cout << bottomRow[i] << (i == maxLength - 1 ? '\n' : ' ');
        }
    }

    return 0;
}
