#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
struct END{~END(){flush();} } EENNDD;
template <class I>inline void print(I x)
{
    if(!x) putc('0');
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) putc(qu[qr--]);
}

const int N=1000010,M=20000010;
const int INF=0x3f3f3f3f;
struct Edge{int from,to,capa,flow,next;} e[M];
int h[N],d[N],cur[N],sum;
bool vis[N];
int n,m,s,t,val[N];

void add_edge(int u,int v,int c)
{
    e[++sum]={u,v,c,0,h[u]};h[u]=sum;
    e[++sum]={v,u,0,0,h[v]};h[v]=sum;
}

bool BFS()
{
    memset(vis,0,sizeof(vis));
    queue<int> q;
    q.push(s);
    d[s]=0;
    vis[s]=1;
    while(!q.empty())
    {
        int o=q.front();
        for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
        {
            if(e[tmp].capa>e[tmp].flow&&vis[e[tmp].to]==0)
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
        if(d[u]+1==d[e[tmp].to])
        {
            f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
            if(f>0)
            {
                e[tmp].flow+=f;
                e[tmp^1].flow-=f;
                flow+=f;
                a-=f;
                if(a==0) break;
            }
        }
    }
    return flow;
}

int MaxFlow()
{
    int flow=0;
    while(BFS())
    {
        for(int i=0;i<=n*m+1;i++) cur[i]=h[i];
        flow+=DFS(s,INF);
    }
    return flow;
}

int idx(int x,int y){return (x-1)*m+y;}

int _main_()
{
    scanf("%d%d",&n,&m);sum=-1;
    memset(h,-1,sizeof(int)*(n*m+2));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if((i+j)&1) continue;
            if(i>=3&&j>=2) add_edge(idx(i,j),idx(i-2,j-1),INF);
            if(i>=3&&j<=m-1) add_edge(idx(i,j),idx(i-2,j+1),INF);
            if(i>=2&&j>=3) add_edge(idx(i,j),idx(i-1,j-2),INF);
            if(i>=2&&j<=m-2) add_edge(idx(i,j),idx(i-1,j+2),INF);
            if(i<=n-1&&j>=3) add_edge(idx(i,j),idx(i+1,j-2),INF);
            if(i<=n-1&&j<=m-2) add_edge(idx(i,j),idx(i+1,j+2),INF);
            if(i<=n-2&&j>=2) add_edge(idx(i,j),idx(i+2,j-1),INF);
            if(i<=n-2&&j<=m-1) add_edge(idx(i,j),idx(i+2,j+1),INF);
            if(i>=4) add_edge(idx(i,j),idx(i-3,j),INF);
            if(i<=n-3) add_edge(idx(i,j),idx(i+3,j),INF);
            if(j>=4) add_edge(idx(i,j),idx(i,j-3),INF);
            if(j<=m-3) add_edge(idx(i,j),idx(i,j+3),INF);
        }
    s=0;t=n*m+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if((i+j)&1) add_edge(idx(i,j),t,1);
            else add_edge(s,idx(i,j),1);
    print(MaxFlow()*2);putc('\n');
    memset(val,0,sizeof(int)*(n*m+1));
    int tot=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if((i+j)&1) continue;
            int u=idx(i,j);
            for(int i=h[u];~i;i=e[i].next)
                if(e[i].flow>0) val[u]=val[e[i].to]=++tot;
        }
    for(int i=1;i<=n;i++,putc('\n'))
        for(int j=1;j<=m;j++)
            print(val[idx(i,j)]),putc(' ');
}

int main()
{
    int T;scanf("%d",&T);
    while(T--) _main_();
    return 0;
}