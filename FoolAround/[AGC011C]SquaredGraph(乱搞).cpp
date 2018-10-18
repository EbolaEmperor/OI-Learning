#include<bits/stdc++.h>
#define MP make_pair
#define FR first
#define SE second
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

const int N=200010;
struct Edge{int to,next;} e[N<<1];
int fa[N],sz[N],n,m,h[N],sum=0;
pair<int,int> circle[N];
bool parity[N],odd[N];
int cnt[2];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int fa)
{
    parity[u]=parity[fa]^1;
    for(int t=h[u];t;t=e[t].next)
        if(e[t].to!=fa) dfs(e[t].to,u);
}

int main()
{
    int u,v,tot=0;
    n=read();m=read();
    for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
    for(int i=1;i<=m;i++)
    {
        u=read();v=read();
        if(find(u)!=find(v))
        {
            add_edge(u,v);
            add_edge(v,u);
            u=find(u);v=find(v);
            fa[u]=v;sz[v]+=sz[u];
        }
        else circle[++tot]=MP(u,v);
    }
    for(int i=1;i<=n;i++)
        if(fa[i]==i) dfs(i,0);
    for(int i=1;i<=tot;i++)
        if(parity[circle[i].FR]==parity[circle[i].SE])
            odd[find(circle[i].FR)]=1;
    int alone=0;
    long long ans=0;
    for(int i=1;i<=n;i++)
    {
        if(fa[i]!=i) continue;
        if(sz[i]==1) alone++,ans+=n;
        else cnt[odd[i]]++;
    }
    ans+=1ll*(n-alone)*alone;
    ans+=2ll*cnt[0]*cnt[0];
    ans+=1ll*cnt[1]*(cnt[1]+2*cnt[0]);
    cout<<ans<<endl;
    return 0;
}