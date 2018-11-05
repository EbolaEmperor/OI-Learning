#include<bits/stdc++.h>
using namespace std;

const int N=18,ha=998244353;
struct Edge{int to,next;} e[N*N];
int h[N],sum=0,n,m;
int f[N][1<<N],dp[N][1<<N];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

int F(int u,int stu)
{
    int &res=f[u][stu];
    if(res) return res;
    res=stu;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(stu&(1<<v)) continue;
        res|=F(v,1<<v|stu);
    }
    return res;
}

int DP(int u,int stu)
{
    int &res=dp[u][stu];
    if(res) return res;
    if(stu==f[u][stu]) return res=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(stu&(1<<v)) continue;
        int x=DP(v,1<<v|stu);
        int y=DP(u,stu|f[v][1<<v|stu]);
        res=(res+1ll*x*y)%ha;
    }
    return res;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        u--; v--;
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int i=0;i<n;i++)
        for(int s=0;s<(1<<n);s++)
            if(!f[i][s]) f[i][s]=F(i,s);
    int ans=0;
    for(int i=0;i<n;i++)
        ans=(ans+DP(i,1<<i))%ha;
    printf("%d\n",ans);
    return 0;
}