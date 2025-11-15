#include <iostream>
using namespace std;
void merge(int *, int, int, int);
void mergesort(int *arr, int left, int right)
{
    if (left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    mergesort(arr, left, mid);
    mergesort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}
void merge(int *arr, int left, int mid, int right)
{
    int size = right -left + 1;
    int *B = new int[size];
    int i = left;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= right)
    {
        if (arr[i] < arr[j])
        {
            B[k] = arr[i];
            i++;
        }
        else
        {
            B[k] = arr[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        B[k] = arr[i];
        i++;
        k++;
    }
    while (j <= right)
    {
        B[k] = arr[j];
        k++;
        j++;
    }
    for (k = 0; k < size; k++)
    {
        arr[left+k] = B[k];
    }
    delete[] B;
}
int main()
{
    int n, i, k;
    cout << "Enter the size of the array : ";
    cin >> n;
    int *arr=new int[n];
    cout << "Enter the elements of the array : " << endl;
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int left, right;
    left = 0;
    right = n - 1;
    mergesort(arr, left, right);
    cout << "Enter the value of the k : ";
    cin >> k;
    cout << arr[k-1] << endl;
    delete[] arr;
    return 0;
}