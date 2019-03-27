#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL a,b,k,ans=0;

LL Sqrt(LL x)
{
    LL res=sqrt(x);
    if(res*res>x) res--;
    return res;
}

int main()
{
    cin>>a>>b>>k;
    LL tmp=cbrt(a);
    if(tmp*tmp*tmp<a) tmp++;
    for(LL x=tmp;x*x*x<=b;x++)
        ans+=Sqrt(min(b,x*x*x+k))-Sqrt(max(a-1,x*x*x-k-1));
    cout<<ans<<endl;
    return 0;
}