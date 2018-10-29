#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=15;
int n,m,bgt;
int fa[N],ffa[N];
LL ans=INT64_MAX,sum;
LL dis[N][N];

int find(int x){return ffa[x]==x?x:ffa[x]=find(ffa[x]);}

void dfs(int u,int dep)
{
    for(int i=1;i<=n;i++)
    {
        if(fa[i]!=u) continue;
        sum+=dis[u][i]*dep;
        dfs(i,dep+1);
    }
}

int calc(int root)
{
    sum=0;
    dfs(root,1);
    ans=min(ans,sum);
    return sum;
}

bool check()
{
    for(int i=0;i<=n;i++) ffa[i]=i;
    for(int i=1;i<=n;i++)
    {
        if(find(i)==find(fa[i])) return 0;
        ffa[find(i)]=find(fa[i]);
    }
    return 1;
}

double RAND(){return (double)rand()/RAND_MAX;}
bool accept(double dta,double tem){return dta<0||RAND()<exp(-dta/tem);}
void anneal(int root,double tem,double delta,double end)
{
    int res=calc(root);
    while(tem>end)
    {
        int x=rand()%n+1,y=rand()%n+1;
        while(x==y||x==root) x=rand()%n+1,y=rand()%n+1;
        int pre=fa[x];fa[x]=y;
        if(!check()){fa[x]=pre;continue;}
        LL nxt=calc(root);
        if(accept(nxt-res,tem)) res=nxt;
        else fa[x]=pre;
        tem*=delta;
    }
}

void work()
{
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) fa[j]=i;
        fa[i]=0;
        anneal(i,1e5,0.99,1e-9);
    }
}

bool TLE()
{
    double now=clock()-bgt;
    now=now/CLOCKS_PER_SEC*1000;
    return now>950;
}

int main()
{
    bgt=clock();
    srand(time(0));
    scanf("%d%d",&n,&m);
    if(n==1) return puts("0"),0;
    memset(dis,3,sizeof(dis));
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        dis[u][v]=min(dis[u][v],(LL)w);
        dis[v][u]=min(dis[v][u],(LL)w);
    }
    for(int i=1;i<=n;i++) fa[i]=1;fa[1]=0;
    while(!TLE()) work();
    printf("%lld\n",ans);
    return 0;
}