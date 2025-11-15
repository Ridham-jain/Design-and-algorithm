#include <iostream>
# include <cmath>
using namespace std;
void merge(double *, int, int, int);
void mergesort(double *arr, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergesort(arr, low, mid);
        mergesort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
    else return;
}
void merge(double *arr,int low,int mid,int high)
{
    int size=high-low+1;
    double *C= new double[size];
    int i=low,j=mid+1,k=0;
    while(i<=mid && j<=high)
    {
        if(arr[i]>=arr[j])
        {
            C[k]=arr[i];
            i++;
        }
        else
        {
            C[k]=arr[j];
            j++;
        }
        k++;
    }
    while(i<=mid)
    {
        C[k]=arr[i];
        i++;
        k++;
    }
    while(j<=high)
    {
        C[k]=arr[j];
        j++;
        k++;
    }
    for(i=0;i<size;i++)
    {
        arr[i+low]=C[i];
    }

    delete[] C;
}
int main()
{
    int n;
    cout << "Enter the value for n : ";
    cin >> n;
    double *arr = new double[n];
    int i,j;
    double sum=0;
    cout << "Enter the rates in increase : "<<endl;
    for (int i=0; i < n; i++)
    {
        cin >> arr[i];
    }
    int low=0;
    int high=n-1;
    mergesort(arr,low,high);
    for(i=0;i<n;i++)
    {
        arr[i]=pow(arr[i],i);
        sum=sum+arr[i];
    }
    int min=1000*sum;
    cout<<"The minimum cost is : "<<min<<endl;

    delete[] arr;
    return 0;
}