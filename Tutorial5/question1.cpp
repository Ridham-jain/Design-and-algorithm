# include <iostream>
# include <vector>
# include <climits>
using namespace std;

vector<vector<int>> parenthesis(vector<int>& p)
{
    int n=p.size()-1;
    std::vector<std::vector<int>> m(n, std::vector<int>(n, 0));
    std::vector<std::vector<int>> s(n, std::vector<int>(n, 0));

    for(int l=2;l<n;l++)
    {
        for(int i=0;i<n-l;i++)
        {
            int j=l+i;
            m[i][j]=INT_MAX;
            for(int k=i;k<=j-1;k++)
            {
                int q=m[i][k]+m[k+1][j] + p[i]*p[k+1]*p[j+1];
                if(q<m[i][j])
                {
                    m[i][j]=q;
                    s[i][j]=k;
                }
            }
        }
    }
    return s;
}

void print(vector<vector<int>>& s,int i,int j)
{
    if(i==j)
    {
        cout<<"A"<<i+1<<" ";
    }
    else{
        cout<<"( ";
        print(s,i,s[i][j]);
        print(s,s[i][j]+1,j);
        cout<<") ";
    }
}

int main()
{
    vector<int> p={10,30,5,60};
    vector<vector<int>> s =parenthesis(p);
    print(s,0,p.size()-2);
    return 0;
}