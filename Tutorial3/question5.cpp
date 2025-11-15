# include <iostream>
using namespace std;
void swap(int *a,int *b)
{
    int temp=*a;
    *a=*b;
    *b=temp;
}
void dual_quick_sort(int *arr,int low,int high)
{
    if(low<high)
    {
        if(arr[low]>arr[high])
        {
            swap((arr+low),(arr+high));
        }
        int p1=arr[low];
        int p2=arr[high];
        int j=low+1,k=low +1,g= high-1;

        while(k<=g)
        {
            if(arr[k]<p1)
            {
                swap((arr+k),(arr+j));
                j++;
            }
            else if(arr[k]>p2)
            {
                swap((arr+k),(arr+g));
                g--;
            }
            k++;
        }
        j--;
        g++;
        swap((arr+j),(arr+low));
        swap((arr+g),(arr+high));
        dual_quick_sort(arr,low,j-1);
        dual_quick_sort(arr,j+1,g--);
        dual_quick_sort(arr,g+1,high);
    }
}
int main(){
    int n;
    cout<<"Enter the size of the array : ";
    cin>>n;
    int *arr=new int[n];
    int i;
    cout<<"Enter the elements of the array : "<<endl;
    for(i=0;i<n;i++)
    {
        cin>>arr[i];
    }
    int low=0;
    int high=n-1;
    dual_quick_sort(arr,low,high);
    cout<<"Elements of sorted array : ";
    for(i=0;i<n;i++)
    {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    delete[] arr;
    return 0;
}