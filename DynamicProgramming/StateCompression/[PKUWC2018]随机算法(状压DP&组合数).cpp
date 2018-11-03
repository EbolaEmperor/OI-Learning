#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=21;
int cant[N],n,m;
int f[N][1<<N];
int cnt[1<<N];
int fac[N],ifac[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void Init(int lim)
{
    fac[0]=1;
    for(int i=1;i<=lim;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[lim]=Pow(fac[lim],ha-2);
    for(int i=lim-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

int A(int n,int m){return 1ll*fac[n]*ifac[n-m]%ha;}

int main()
{
    scanf("%d%d",&n,&m);Init(n);
    for(int i=1;i<1<<n;i++)
        cnt[i]=cnt[i^(i&-i)]+1;
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        cant[u]|=1<<v-1;
        cant[v]|=1<<u-1;
    }
    f[0][0]=1;
    for(int i=0;i<=n;i++)
        for(int s=0;s<1<<n;s++)
        {
            if(!f[i][s]) continue;
            for(int j=1;j<=n;j++)
            {
                if(s&(1<<j-1)) continue;
                (f[i+1][s|cant[j]|(1<<j-1)]+=1ll*f[i][s]*A(n-cnt[s]-1,cnt[cant[j]^(cant[j]&s)])%ha)%=ha;
            }
        }
    for(int i=n;i>=0;i--)
    {
        if(!f[i][(1<<n)-1]) continue;
        int ans=1ll*f[i][(1<<n)-1]*ifac[n]%ha;
        printf("%d\n",ans);break;
    }
    return 0;
}