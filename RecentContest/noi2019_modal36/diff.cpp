#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=310,M=100010;
int ch[N][26],tot=0;
int trie[M][26],dep[M],fa[M],chr[M],trien=0;
vector<pii> edg[N];
char s[N];
int n;

int insert(int x,int c)
{
    if(!trie[x][c])
    {
        trie[x][c]=++trien;
        dep[trien]=dep[x]+1;
        chr[trien]=c;
        fa[trien]=x;
    }
    return trie[x][c];
}

void output(int x)
{
    static char ans[N];
    int len=0;
    for(;x;x=fa[x])
        ans[len++]=(chr[x]+'a');
    reverse(ans,ans+len);
    ans[len]='\0';
    puts(ans);
}

void bfs(int id)
{
    queue<pii> q;q.push(pii(0,0));
    while(!q.empty())
    {
        pii tmp=q.front();q.pop();
        int u=tmp.first,p=tmp.second;
        if(dep[p]) edg[id].emplace_back(pii(dep[p],p));
        if(edg[id].size()>=n) return;
        for(int i=0;i<26;i++)
        {
            int v=ch[u][i];
            if(!v) continue;
            q.push(pii(v,insert(p,i)));
        }
    }
}

struct Edge{int to,next,capa,flow;} e[1000000];
int h[N+M],cur[N+M],dpe[N+M],sum,S,T;
bool vis[N+M];

void add_edge(int u,int v,int w)
{
    e[++sum]={v,h[u],w,0};h[u]=sum;
    e[++sum]={u,h[v],0,0};h[v]=sum;
}

bool BFS()
{
    memset(vis,0,sizeof(vis));
    queue<int> q;q.push(S);
    vis[S]=1;dep[S]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int t=h[u];~t;t=e[t].next)
        {
            int v=e[t].to;
            if(!vis[v]&&e[t].capa>e[t].flow)
            {
                vis[v]=1;
                q.push(v);
                dep[v]=dep[u]+1;
            }
        }
    }
    return vis[T];
}

int DFS(int u,int a)
{
    if(u==T||a==0) return a;
    int res=0;
    for(int t=cur[u];~t;t=e[t].next)
    {
        int v=e[t].to;
        if(dep[v]!=dep[u]+1) continue;
        int f=DFS(v,min(a,e[t].capa-e[t].flow));
        if(f)
        {
            res+=f;a-=f;
            e[t].flow+=f;
            e[t^1].flow-=f;
            if(!a) break;
        }
    }
    return res;
}

int Dinic()
{
    int res=0;
    while(BFS())
    {
        memcpy(cur,h,sizeof(h));
        res+=DFS(S,INT_MAX);
    }
    return res;
}

bool check(int m)
{
    sum=-1;
    memset(h,-1,sizeof(h));
    for(int i=1;i<=n;i++)
    {
        for(auto p : edg[i])
            if(p.first<=m) add_edge(i,n+p.second,1);
        add_edge(S,i,1);
    }
    for(int i=1;i<=trien;i++)
        add_edge(n+i,T,1);
    return Dinic()==n;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        int len=strlen(s);
        memset(ch,0,sizeof(ch));tot=0;
        for(int j=0;j<len;j++)
        {
            int c=s[j]-'a';tot++;
            for(int k=0;k<tot;k++)
                if(!ch[k][c]) ch[k][c]=tot;
        }
        bfs(i);
    }
    S=0;T=n+trien+1;
    int l=1,r=n,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(check(mid)) r=mid-1;
        else l=mid+1;
    }
    if(l>n) return puts("-1"),0;
    printf("%d\n",l);check(l);
    for(int u=1;u<=n;u++)
        for(int t=h[u];~t;t=e[t].next)
            if(e[t].to>n&&e[t].flow==1)
                output(e[t].to-n);
    return 0;
}