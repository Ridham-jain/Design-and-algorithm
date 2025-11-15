#include <iostream>
using namespace std;
int peak(int *arr , int left, int right)
{
    int mid = (left + right)/2;
    if((mid==left && arr[mid]>=arr[mid+1]) || (mid==right && arr[mid]>=arr[mid-1]) || (mid>left && mid<right && arr[mid]>=arr[mid+1] && arr[mid]>=arr[mid-1]))
    {
        return mid;
    }
    else if(mid>0 && arr[mid]<arr[mid-1])
    {
        return peak(arr,left,mid-1);
    }
    else
    {
        return peak(arr,mid+1,right);
    }
}
int main()
{
    int n, i, count = 0;
    cout << "Enter the size of the array : ";
    cin >> n;
    int *arr = new int[n];
    cout << "Enter the elements of the array : " << endl;
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int left=0;
    int right=n-1;
    int p = peak(arr,left,right);
    cout<<"Peak index = "<<p<<" Peak Value = "<<arr[p]<<endl;
    delete[] arr;
    return 0;
}