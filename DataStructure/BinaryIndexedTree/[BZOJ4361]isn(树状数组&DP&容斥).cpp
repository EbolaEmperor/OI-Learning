#include<bits/stdc++.h>
#define ha 1000000007
#define lowbit(x) (x&-x)
using namespace std;

typedef long long LL;
const int N=2010;
LL f[N][N],g[N],fac[N],n;
LL bit[N][N],Hash[N],a[N];
int pos[N];

void Add(int d,int p,LL x){for(int i=p;i<=n;i+=lowbit(i)) (bit[d][i]+=x)%=ha;}
LL Sum(int d,int p){LL res=0;for(int i=p;i;i-=lowbit(i)) (res+=bit[d][i])%=ha;return res;}

int main()
{
    scanf("%d",&n);
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%ha;
    for(int i=1;i<=n;i++) scanf("%lld",a+i),Hash[i]=a[i];
    sort(Hash+1,Hash+1+n);
    int hs=unique(Hash+1,Hash+1+n)-(Hash+1);
    for(int i=1;i<=n;i++)
        pos[i]=lower_bound(Hash+1,Hash+1+hs,a[i])-Hash;
    Add(0,1,1);
    for(int i=1;i<=n;i++)
        for(int j=i;j>=1;j--)
        {
            f[i][j]=Sum(j-1,pos[i]);
            Add(j,pos[i],f[i][j]);
        }
    for(int i=1;i<=n;i++)
        for(int j=i;j<=n;j++)
            (g[i]+=f[j][i])%=ha;
    LL ans=0;
    for(int i=1;i<=n;i++)
    {
        (ans+=fac[n-i]*g[i]%ha)%=ha;
        if(i<n) (ans-=fac[n-i-1]*g[i+1]%ha*(i+1)%ha-ha)%=ha;
    }
    printf("%lld\n",ans);
    return 0;
}