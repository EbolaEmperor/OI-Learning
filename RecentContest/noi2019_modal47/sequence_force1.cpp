// O(2^n)
#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=25;
int n,p[N],ans=0;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void dfs(int d,int pb,int sum,int v)
{
    if(d==n+1)
    {
        ans=(ans+1ll*pb*sum*sum)%ha;
        return;
    }
    dfs(d+1,1ll*pb*p[d]%ha,sum+v+1,v+1);
    dfs(d+1,1ll*pb*(1-p[d]+ha)%ha,sum,0);
}

int main()
{
    scanf("%d",&n);
    int inv=Pow(100,ha-2);
    for(int i=1;i<=n;i++)
        scanf("%d",p+i),p[i]=1ll*p[i]*inv%ha;
    dfs(1,1,0,0);
    cout<<ans<<endl;
    return 0;
}