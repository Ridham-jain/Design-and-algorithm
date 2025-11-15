# include <iostream>
# include <climits>
using namespace std;

int* rod_cutting(int *p,int n)
{
    int *r=new int[5];
    r[0]=0;
    int q;
    for(int j=1;j<n;j++)
    {
        q=INT_MIN;
        for(int i=1;i<=j;i++)
        {
            if(q<p[i]+r[j-i])
            {
                q=p[i]+r[j-i];
            }
        }
        r[j]=q;
    }
    return r;
}

int main()
{
    int p[5]={0,1,5,8,9};
    int s;
    cout<<"Enter the size of rod required :";
    cin>>s;
    int *r=new int[5];
    r=rod_cutting(p,5);
    cout<<"The price for rod of length i = "<<r[s];
    delete[] r;
    return 0;
}