#include<bits/stdc++.h>
using namespace std;

const int N=110;
int f[2][N][N],g[2][N][N];
int T,n,m,a[N][N],sum[N];

int main()
{
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",a[i]+j);
        int k=1;
        memset(f[k],0,sizeof(f[k]));
        for(int i=1;i<=m;i++) f[k][i][i]=a[n][i];
        for(int i=n;i>1;i--,k^=1)
        {
            for(int j=1;j<=m;j++) sum[j]=sum[j-1]+a[i-1][j];
            for(int l=1;l<=m;l++)
                for(int r=m;r>=l;r--)
                {
                    f[k^1][l][r]=f[k][l][l];
                    if(l>1||r<m)
                    {
                        int mn=INT_MAX;
                        if(l>1) mn=min(mn,f[k^1][l-1][r]);
                        if(r<m) mn=min(mn,g[k^1][l][r+1]+sum[r]-sum[l]);
                        f[k^1][l][r]=max(f[k^1][l][r],mn);
                    }
                    f[k^1][l][r]+=a[i-1][l];
                    g[k^1][l][r]=f[k][r][r];
                    if(l>1||r<m)
                    {
                        int mn=INT_MAX;
                        if(l>1) mn=min(mn,f[k^1][l-1][r]+sum[r-1]-sum[l-1]);
                        if(r<m) mn=min(mn,g[k^1][l][r+1]);
                        g[k^1][l][r]=max(g[k^1][l][r],mn);
                    }
                    g[k^1][l][r]+=a[i-1][r];
                }
        }
        int res=INT_MAX;
        for(int i=1;i<=m;i++)
            res=min(res,f[k][i][i]);
        printf("%d\n",res);
    }
    return 0;
}