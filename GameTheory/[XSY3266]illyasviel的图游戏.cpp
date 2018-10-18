#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

typedef long long LL;
const int N=100010;
struct Edge{int to,capa,next;} e[N<<2];
int h[N],sum=0,n,m;
LL ans=0,cnt[2]={0};
bool vis[N];

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int a,bool parity)
{
    vis[u]=1;
    if(u==n){cnt[parity]+=a;return;}
    for(int t=h[u];t;t=e[t].next)
        if(!vis[e[t].to]||e[t].to==n)
            dfs(e[t].to,min(a,e[t].capa),parity^1);
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read(),w;
        ans+=(w=read());
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    dfs(1,INT_MAX,0);
    if(ans&1) puts(cnt[0]>=cnt[1]?"Yes":"No");
    else puts(cnt[0]<=cnt[1]?"Yes":"No");
    return 0;
}