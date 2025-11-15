#include <iostream>
using namespace std;
int main()
{
    int n;
    cout << "Enter the total Petrol Pumps : ";
    cin >> n;
    int *arr = new int[n];
    int i, k = 0;
    cout << "Enter the points at which the feul stations are available : " << endl;
    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int full;
    cout << "Enter the distance covered by full tank : ";
    cin >> full;
    int total;
    cout << "Enter the total distnce : ";
    cin >> total;

    int distance = arr[0];
    static int *stop = new int[n];
    for (i = 0; i < n-1; i++)
    {
        distance = distance + arr[i + 1] - arr[i];
        if (distance > full)
        {
            stop[k] = arr[i];
            k++;
            distance = arr[i + 1] - arr[i];
        }
    }
    if((total-arr[n-1]+distance)>10)
    {
        stop[k]=arr[n-1];
    }
    cout<<"The car will stop at distances : "<<endl;
    for(k=0;k<n;k++)
    {
        if(stop[k]!=0)
        {
            cout << stop[k]<<" ";
        }
    }

    delete[] arr;
    return 0;
}