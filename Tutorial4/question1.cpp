# include <iostream>
# include <climits>
void merge(float *, int, int, int);
void mergesort(float *arr, int left, int right)
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
void merge(float *arr, int left, int mid, int right)
{
    int size = right -left + 1;
    float *B = new float[size];
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
float greedy(int (*arr)[2],int n,int total)
{
    float *r=new float[n];
    int i;
    int sum=0;
    float profit=0;
    for(i=0;i<n;i++)
    {
        r[i]=((float)arr[i][0])/arr[i][1];
    }
    int left=0;
    int right=n-1;
    mergesort(r,left,right);

    i=n-1;
    while(i>=0)
    {
        if(sum<total && sum+arr[i][1]<=total)
        {
            sum+=arr[i][1];
            profit+=arr[i][0];
        }
        else if(sum<total && sum+arr[i][1]>total)
        {
            profit+=(total-sum)*r[i];
            sum=total;
        }
        else
        {
            break;
        }
    }
    delete[] r;
    return profit;
}
using namespace std;
int main()
{
    int n;
    cout<<"Enter the total products : ";
    cin>>n;
    int (*arr)[2]=new int[n][2];

    cout<<"Enter the elements of the array : "<<endl;

    int i;
    for(i=0;i<n;i++)
    {
        cout<<"Enter the value : ";
        cin>>arr[i][0];
        cout<<"Enter the weight : ";
        cin>>arr[i][1];
    }
    int total;
    cout<<"Enter the total weight required : ";
    cin>>total;
    float profit = greedy(arr,n,total);
    cout<<"The total profit is : "<<profit<<endl;
    delete [] arr;
    return 0;
}