#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1010,ha=323232323;
int qwq,m,n,q,a[N];
LL h[N],f[N],g[2][N];

void prework()
{
    f[0]=1;f[1]=0;f[2]=m-1;
    h[0]=1;h[1]=0;h[2]=m-1;
    for(int i=3;i<=60;i++)
    {
        g[0][0]=g[0][i]=0;
        for(int j=1;j<i;j++) g[0][j]=h[j];
        int p=0;
        h[i]=f[i]=pow((LL)m-2,i-2)*(m-1);
        for(int t=0;t<=i;t++,p^=1)
        {
            f[i]+=g[p][i];
            memset(g[p^1],0,sizeof(LL)*(i+1));
            for(int j=0;j<=i;j++)
                for(int k=1;k<i;k++)
                    g[p^1][j+k]+=g[p][j]*h[k];
        }
    }
}

int main()
{
    freopen("data.in","r",stdin);
    scanf("%d%d%d%d",&qwq,&m,&n,&q);
    prework();
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    int opt,l,r,k;
    while(q--)
    {
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1)
        {
            LL ans=0;
            for(int i=l;i<=r;i++)
                ans=__gcd(ans,a[i]>=0?f[a[i]]:0);
            printf("%lld\n",ans%ha);
        }
        if(opt==2) reverse(a+l,a+r+1);
        if(opt==3)
        {
            scanf("%d",&k);
            for(int i=l;i<=r;i++)
                a[i]+=k;
        }
    }
    return 0;
}
