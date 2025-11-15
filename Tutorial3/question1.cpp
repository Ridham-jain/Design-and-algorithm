#include <iostream>
using namespace std;
void merge(int *, int, int, int);
long long count_inversions(int *, int, int, int);
void mergesort(int *arr, int left, int right,int& count)
{
    if (left >= right)
    {
        return;
    }
    int mid = (left + right) / 2;
    mergesort(arr, left, mid,count);
    mergesort(arr, mid + 1, right,count);
    (count)+=count_inversions(arr, left, mid, right);
    merge(arr, left, mid, right);
}
void merge(int *arr, int left, int mid, int right)
{
    int size = right - left + 1;
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
        arr[left + k] = B[k];
    }
    delete[] B;
}
long long count_inversions(int *arr, int left, int mid, int right)
{
    long long inv = 0;
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int *L = new int[n1];
    int *R = new int[n2];
    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }
    int i=0;
    int j=0;
    while(i<n1 && j<n2)
    {
        if(L[i]<=R[j])
        {
            i++;
        }
        else
        {
            inv+=(n1-i);
            j++;
        }
    }
    delete[] L;
    delete[] R;
    return inv;
}
int main()
{
    int n, i,count=0;
    cout << "Enter the size of the array : ";
    cin >> n;
    int *arr = new int[n];
    cout << "Enter the elements of the array : " << endl;
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int left = 0;
    int right = n - 1;
    mergesort(arr, left, right,count);
    cout << "Total inversions = " << count << endl;

    delete[] arr;

    return 0;
}