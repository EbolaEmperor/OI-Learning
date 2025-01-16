#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
string opt;
int n;

int main()
{
    cin>>n;
    int k=1,ans=2,cnt=2;
    for(int i=1;i<n;i++)
    {
        cin>>opt;
        if(opt=="&&") cnt++;
        else k=1ll*k*(cnt-1)%ha,cnt=2;
        ans=(ans+k)%ha;
    }
    cout<<ans<<endl;
    return 0;
}