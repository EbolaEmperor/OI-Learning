#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[3000],cur[3000],d[3000];
bool vis[3000];
int sum=-1;
int n,m,s,t;
int result[200][1000];
int num[200];

void add_edge(int u,int v,int c)
{
    sum++;
    e[sum].from=u;
    e[sum].to=v;
    e[sum].capa=c;
    e[sum].flow=0;
    e[sum].next=h[u];
    h[u]=sum;
}

int BFS()
{
    memset(vis,0,sizeof(vis));
    vis[s]=1;
    d[s]=0;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int o=q.front();
        for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
        {
            if(vis[e[tmp].to]==0&&e[tmp].capa>e[tmp].flow)
            {
                vis[e[tmp].to]=1;
                d[e[tmp].to]=d[o]+1;
                q.push(e[tmp].to);
            }
        }
        q.pop();
    }
    return vis[t];
}

int DFS(int u,int a)
{
    if(u==t||a==0) return a;
    int flow=0,f;
    for(int& tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
    {
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
    }
    return flow;
}

int Dinic()
{
    int flow=0;
    while(BFS())
    {
        for(int i=s;i<=t;i++) cur[i]=h[i];
        flow+=DFS(s,INF);
    }
    return flow;
}

int main()
{
    cin>>m>>n;
    s=0;
    t=m+n+1;
    for(int i=s;i<=t;i++) h[i]=-1;
    int tmp,cnt=0;
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&tmp);
        add_edge(s,i,tmp);
        add_edge(i,s,0);
        cnt+=tmp;
    }
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
        {
            add_edge(i,m+j,1);
            add_edge(m+j,i,0);
        }
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&tmp);
        add_edge(m+i,t,tmp);
        add_edge(t,m+i,0);
    }
    if(Dinic()<cnt)
        printf("0\n");
    else
    {
        printf("1\n");
        memset(num,0,sizeof(num));
        for(int i=0;i<=sum;i++)
        {
            if(e[i].flow>0&&e[i].from>s&&e[i].from<=m&&e[i].to>m&&e[i].to<t)
            {
                num[e[i].from]++;
                result[e[i].from][num[e[i].from]]=e[i].to-m;
            }
        }
        for(int i=1;i<=m;i++)
        {
            for(int j=1;j<=num[i];j++)
                printf("%d ",result[i][j]);
            printf("\n");
        }
    }
}
