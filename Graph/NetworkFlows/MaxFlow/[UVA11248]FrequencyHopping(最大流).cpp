#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next,flow;} e[2000000],ee[2000000];
struct Ans{int x,y;} ans[2000000];
int h[5000];
int d[5000];
int cur[5000];
bool vis[5000];
int sum,s,t,c;

bool operator < (Ans a,Ans b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}

void AddEdge(int u,int v,int w)
{
    sum++;
    e[sum].from=u;
    e[sum].to=v;
    e[sum].capa=w;
    e[sum].flow=0;
    e[sum].next=h[u];
    h[u]=sum;
}

void add_edge(int u,int v,int w)
{
    AddEdge(u,v,w);
    AddEdge(v,u,0);
}

bool BFS()
{
    memset(vis,0,sizeof(vis));
    vis[s]=1;d[s]=0;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int o=q.front();
        for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
            if(e[tmp].capa>e[tmp].flow&&vis[e[tmp].to]==0)
            {
                vis[e[tmp].to]=1;
                d[e[tmp].to]=d[o]+1;
                q.push(e[tmp].to);
            }
        q.pop();
    }
    return vis[t];
}

int DFS(int u,int a)
{
    if(u==t||a==0) return a;
    int flow=0,f;
    for(int &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
        if(d[e[tmp].to]==d[u]+1)
        {
            f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
            if(f>0)
            {
                flow+=f;
                a-=f;
                e[tmp].flow+=f;
                e[tmp^1].flow-=f;
                if(a==0) break;
            }
        }
    return flow;
}

int Dinic(int init)
{
    int flow=init;
    while(BFS())
    {
        for(int i=s;i<=t;i++) cur[i]=h[i];
        flow+=DFS(s,INF);
        if(flow>=c) break;
    }
    return flow;
}

int main()
{
    int n,m,x,y,z,T=0;
    while(~scanf("%d%d%d",&n,&m,&c)&&(n+m+c))
    {
        T++;
        sum=-1;
        s=0;t=n+1;
		for(int i=s;i<=t;i++) h[i]=-1;
		add_edge(s,1,INF);
		add_edge(n,t,INF);
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&x,&y,&z);
            add_edge(x,y,z);
        }
        int flow=Dinic(0);
        if(flow>=c) {printf("Case %d: possible\n",T);continue;}
        for(int i=0;i<=sum;i++) ee[i]=e[i];
        int cnt=0;
        for(int i=0;i<=sum;i+=2)
            if(ee[i].flow==ee[i].capa)
            {
                for(int j=0;j<=sum;j++) e[j]=ee[j];
                e[i].capa=c;
                int flowtmp=Dinic(flow);
                if(flowtmp>=c) ans[cnt].x=e[i].from,ans[cnt++].y=e[i].to;
            }
        if(cnt>0)
        {
            sort(ans,ans+cnt);
            printf("Case %d: possible option:",T);
            for(int i=0;i<cnt-1;i++) printf("(%d,%d),",ans[i].x,ans[i].y);
            printf("(%d,%d)\n",ans[cnt-1].x,ans[cnt-1].y);
        }
        if(cnt==0) printf("Case %d: not possible\n",T);
    }
    return 0;
}
