#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int N=1010;
int G[N][N],n,m;
ULL f[N],ans=0;

int main()
{
    scanf("%d%d",&n,&m);
    int u,v,tp=n+1;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        u++;v++;G[u][v]=G[v][u]=1;
    }
    for(int i=0;i<=n;i++)
        G[i][tp]=G[tp][i]=1;
    f[0]=1;
    for(int i=1,k=tp;i<=n;i++,k=tp)
        for(int j=i-1;j>=0;j--)
            if(!G[i][j]&&(G[i][k]||G[j][k]))
                f[i]+=f[j],k=j;
    for(int i=n,k=tp;i>=1;i--)
        if(G[i][k]) ans+=f[i],k=i;
    cout<<ans<<endl;
    return 0;
}