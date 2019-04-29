#include<bits/stdc++.h>
using namespace std;

const int N=155;
struct Edge{int u,v,w;} e[5010];
int f[N][N][N],n,m,q;

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    sort(e+1,e+1+m,[](Edge a,Edge b){return a.w<b.w;});
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++)
    {
        f[i][i][0]=0;
        for(int k=1;k<=m;k++)
        {
            int u=e[k].u,v=e[k].v;
            for(int j=0;j<n;j++)
                f[i][v][j+1]=min(f[i][v][j+1],f[i][u][j]+e[k].w);
        }
        for(int v=1;v<=n;v++)
            for(int j=1;j<=n;j++)
                f[i][v][j]=min(f[i][v][j],f[i][v][j-1]);
    }
    int a,b,c;
    while(q--)
    {
        scanf("%d%d%d",&a,&b,&c);
        int ans=f[a][b][min(c,n)];
        if(ans>=0x3f3f3f3f) ans=-1;
        printf("%d\n",ans);
    }
    return 0;
}