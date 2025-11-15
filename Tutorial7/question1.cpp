# include <iostream>
# include <cmath>
# include <vector>
using namespace std;

void printk(int n,vector<int>&x)
{
    for(int i=0;i<n;i++)
    {
        cout<<x[i]<<" ";
    }
    cout<<endl;
}

bool issafe(int k,vector<int>& x)
{
    for(int i=0;i<k;i++)
    {
        if((x[i]==x[k]) || (abs(x[i]-x[k])==abs(i-k)))
        {
            return false;
        }
    }
    return true;
}

void nqueen(int n,int k,vector<int>& x)
{
    for(int j=0;j<n;j++)
    {
        x[k]=j;
        if(issafe(k,x))
        {
            if(k==n-1)
            {
                printk(n,x);
            }
            else 
            {
                nqueen(n,k+1,x);
            }
        }
    }
}

int main()
{
    int n;
    cout<<"Enter the size of chess board : ";
    cin>>n;

    vector<int> x(n);
    nqueen(n,0,x);
    return 0;
}