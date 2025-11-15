#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int l = 0; l < t; l++)
    {
        int n;
        cin >> n;
        vector<int> a(n);

        for (int i = 0; i < n; i++)
            cin >> a[i];

        vector<int> evens, odds;
        for (int x : a)
        {
            if (x % 2 == 0)
                evens.push_back(x);
            else
                odds.push_back(x);
        }

        sort(evens.begin(), evens.end());
        sort(odds.begin(), odds.end());

        int e = 0, o = 0;
        vector<int> result;

        for (int i = 0; i < n; i++)
        {
            if (!evens.empty() && !odds.empty())
            {
                if (evens[e] < odds[o])
                {
                    result.push_back(evens[e++]);
                }
                else
                {
                    result.push_back(odds[o++]);
                }
            }
            else if (!evens.empty())
            {
                result.push_back(evens[e++]);
            }
            else
            {
                result.push_back(odds[o++]);
            }
        }

        for (int x : result)
            cout << x << " ";
        cout << endl;
    }

    return 0;
}
