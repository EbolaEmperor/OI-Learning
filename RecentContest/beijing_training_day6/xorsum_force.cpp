#include<bits/stdc++.h>
using namespace std;

int main()
{
    int T,n,l,r,cnt=0;
    cin>>T>>n>>l>>r;
    for(int s=l;s<=r<<1;s++)
    {
        bool flag=0;
        for(int i=l;i<=r;i++)
            for(int j=l;j<=r;j++)
                if((i|j)==s) flag=1;
        if(flag) cout<<s<<endl,cnt++;
    }
    cout<<"ans="<<cnt<<endl;
    return 0;
}
