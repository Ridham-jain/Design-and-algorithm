#include <iostream>
# include <vector>
using namespace std;
void swapRows(int arr[][2], int r1, int r2, int cols)
{
    for (int c = 0; c < cols; ++c)
        std::swap(arr[r1][c], arr[r2][c]);
}

void sortByColumn(int arr[][2], int rows, int cols)
{
    for (int i = 0; i < rows - 1; ++i)
    {
        for (int j = 0; j < rows - i - 1; ++j)
        {
            if (arr[j][1] > arr[j + 1][1])
            {
                swapRows(arr, j, j + 1, cols);
            }
        }
    }
}
int jobsequencing(int (*arr)[2], int n, int max)
{
    vector<int> d(max, 0);
    int sum = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = arr[i][0] - 1; j >= 0; j--)
        {
            if (d[j] == 0)
            {
                d[j] = 1;
                sum += arr[i][1];
                break;
            }
        }
    }
    return sum;
}
int main()
{
    int n;
    cout << "Enter the total jobs : ";
    cin >> n;
    int (*arr)[2] = new int[n][2];

    cout << "Enter the elements of the array : " << endl;

    int i;
    for (i = 0; i < n; i++)
    {
        cout << "Enter the deadline : ";
        cin >> arr[i][0];
        cout << "Enter the profit : ";
        cin >> arr[i][1];
    }
    int max = arr[0][0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i][0] > max)
        {
            max = arr[i][0];
        }
    }
    sortByColumn(arr, n, 2);
    int profit = jobsequencing(arr, n, max);
    cout << "Maximum profit is : " << profit << endl;
    delete[] arr;
    return 0;
}