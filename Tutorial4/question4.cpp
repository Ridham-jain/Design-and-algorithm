#include <iostream>
using namespace std;
int main()
{

    int n;
    cout << "Enter the total number of houses : ";
    cin >> n;
    int *arr = new int[n];
    int i, k = 0;
    cout<<"Enter the points where the housess are available : "<<endl;

    int distance=0,j=0,dir=0;
    int *stop = new int[n];

    for (i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    while(k<n)
    {
        stop[k]=0;
        k++;
    }

    k=0;

    for (i = 0; i < n - 1; i++)
    {
        distance = distance + arr[i+1] - arr[i];
        if (distance > 4 && dir==0)
        {
            stop[k] = arr[i];
            k++;
            distance = arr[i+1] - arr[i];
            dir=1;
        }
        if(distance>4 && dir==1)
        {
            distance= arr[i+1] - arr[i];
            dir=0;
        }
    }
    
    cout << "The tower will be at points : " << endl;
    for (k = 0; k < n; k++)
    {
        if (stop[k] != 0)
        {
            cout << stop[k] << " ";
        }
    }

    delete[] arr;
    delete[] stop;
    return 0;
}
