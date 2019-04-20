#include<bits/stdc++.h>
using namespace std;
 
const int ha=998244353;
 
int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}
 
int main()
{
    int theta,n;
    cin>>theta>>n;
    int bad=1ll*(n-1)*Pow(180-theta,n-2)%ha;
    int all=Pow(360-theta,n-2);
    cout<<1ll*(all-bad+ha)*Pow(all,ha-2)%ha<<endl;
    return 0;
}