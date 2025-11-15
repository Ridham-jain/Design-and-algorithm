#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
using namespace std;

int minDiff = INT_MAX; 

void findMinDiff(vector<int>& arr, int i, int sum1, int sum2) {
    if (i == arr.size()) {
        int diff = abs(sum1 - sum2);
        if (diff < minDiff)
            minDiff = diff;
        return;
    }

    findMinDiff(arr, i + 1, sum1 + arr[i], sum2);

    findMinDiff(arr, i + 1, sum1, sum2 + arr[i]);
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    findMinDiff(arr, 0, 0, 0);

    cout << "The minimum difference between two subsets is: " << minDiff << endl;
    return 0;
}
