#include <iostream>
#include <vector>
using namespace std;

void subsetSum(vector<int>& S, vector<int>& subset, int index, int currentSum, int remainingSum, int T) {
    if (currentSum == T) {
        cout << "{ ";
        for (int x : subset) cout << x << " ";
        cout << "}" << endl;
        return;
    }

    if (currentSum > T || currentSum + remainingSum < T)
        return;

    if (index == S.size()) return;

    subset.push_back(S[index]);
    subsetSum(S, subset, index + 1, currentSum + S[index], remainingSum - S[index], T);

    subset.pop_back();
    subsetSum(S, subset, index + 1, currentSum, remainingSum - S[index], T);
}

int main() {
    vector<int> S = {3, 4, 5, 6, 7};
    int T = 12;

    int totalSum = 0;
    for (int x : S) totalSum += x; 
    vector<int> subset;
    cout << "Subsets of {3, 4, 5, 6, 7} that sum to 12:\n";
    subsetSum(S, subset, 0, 0, totalSum, T);

    return 0;
}
