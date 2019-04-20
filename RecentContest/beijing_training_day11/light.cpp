#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int to,capa,flow,next;} e[10500];
int h[210],sum=-1,s,t;
bool vis[210];
int d[210],cur[210];

void AddEdge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].flow=0;
    e[sum].capa=w;
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
    queue<int> q;
    q.push(s);
    d[s]=0;vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        for(int tmp=h[u];~tmp;tmp=e[tmp].next)
            if(e[tmp].capa>e[tmp].flow&&!vis[e[tmp].to])
            {
                vis[e[tmp].to]=1;
                d[e[tmp].to]=d[u]+1;
                q.push(e[tmp].to);
            }
        q.pop();
    }
    return vis[t];
}

int DFS(int u,int a)
{
    if(u==t||a==0) return a;
    int f,flow=0;
    for(int& tmp=cur[u];~tmp;tmp=e[tmp].next)
        if(d[e[tmp].to]==d[u]+1)
        {
            f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
            if(f>0)
            {
                flow+=f;a-=f;
                e[tmp].flow+=f;
                e[tmp^1].flow-=f;
                if(a==0) break;
            }
        }
    return flow;
}

int Maxflow()
{
    int flow=0;
    while(BFS())
    {
        for(int i=s;i<=t;i++) cur[i]=h[i];
        flow+=DFS(s,INF);
    }
    return flow;
}

const int N=10000000;
int lft[110],rht[110],num=0;
bool up[N+10],mark[N+10];
int prm[N],pn=0;

void seive()
{
    mark[1]=1;
    for(int i=2;i<=N;i++)
    {
        if(!mark[i]) prm[++pn]=i;
        for(int j=1;j<=pn&&i*prm[j]<=N;j++)
        {
            mark[i*prm[j]]=1;
            if(i%prm[j]==0) break;
        }
    }
}

int main()
{
    int T;
    scanf("%d",&T);
    seive();
    while(T--)
    {
        int n,x,tot=0;
        scanf("%d",&n);sum=-1;
        memset(h,-1,sizeof(h));
        static int pos[210];
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&x);
            up[x]=1;
            pos[++tot]=x;
            pos[++tot]=x+1;
        }
        tot=unique(pos+1,pos+1+tot)-(pos+1);
        int l=0,r=0;
        for(int i=1;i<=tot;i++)
            if(up[pos[i]]!=up[pos[i]-1])
                ((pos[i]&1)?lft[++l]:rht[++r])=pos[i];
        for(int i=1;i<=tot;i++) up[pos[i]]=0;
        s=0;t=l+r+1;
        for(int i=1;i<=l;i++) add_edge(s,i,1);
        for(int i=1;i<=r;i++) add_edge(l+i,t,1);
        for(int i=1;i<=l;i++)
            for(int j=1;j<=r;j++)
                if(!mark[abs(lft[i]-rht[j])])
                    add_edge(i,j+l,1);
        int falun=Maxflow(),dafa=falun;
        if(l>falun) dafa+=(l-falun)/2*2;
        if(r>falun) dafa+=(r-falun)/2*2;
        if((l-falun)&1) dafa+=3;
        printf("%d\n",dafa);
    }
    return 0;
}
