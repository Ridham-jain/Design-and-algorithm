# include <iostream>
# include <string>
# include <iomanip>
# include <algorithm>
using namespace std;
int main()
{
    int T;
    cin>>T;
    for(int l=0;l<T;l++)
    {
        int n;
        cin>>n;
        cin.ignore();  
        string s(n,' ');
        string t(n,' ');
        cin>>s>>t;

        sort(s.begin(),s.end());
        sort(t.begin(),t.end());

        if(s==t)
        {
            cout<<"YES"<<endl;
        }
        else
        {
            cout<<"NO"<<endl;
        }
    }
    return 0;
}