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
 
const int N=200010;
const int ha=1e9+7;
struct Edge{int to,next;} e[N<<1],et[N<<1];
int h[N],ht[N],esum=0,tsum=0,n,cmt=0;
int gay[N],out[N],sz[N];
bool done[N],inc[N],flag;
vector<int> crl,vertix;
stack<int> s;
int fac[N];
 
int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}
 
void add_edge(int u,int v)
{
    e[++esum]={v,h[u]};h[u]=esum;
    e[++esum]={u,h[v]};h[v]=esum;
}
 
void add_topo_edge(int u,int v)
{
    out[v]++;
    et[++tsum].to=v;
    et[tsum].next=ht[u];
    ht[u]=tsum;
}
 
void findcrl(int u,int fa)
{
    vertix.push_back(u);
    done[u]=1;s.push(u);
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa||inc[v]) continue;
        cmt++;
        if(!flag&&done[v])
        {
            while(s.top()!=v) crl.push_back(s.top()),inc[s.top()]=1,s.pop();
            crl.push_back(v);inc[v]=1;s.pop();
            flag=1;
        }
        else if(!done[v]) findcrl(v,u);
    }
    if(!s.empty()&&s.top()==u) s.pop();
}
 
void findgay(int u,int fa)
{
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa||inc[v]) continue;
        gay[v]=u;findgay(v,u);
    }
}
 
void build_topo()
{
    for(int u : vertix)
        for(int t=h[u];t;t=e[t].next)
        {
            int v=e[t].to;
            if(v>=gay[u]) continue;
            add_topo_edge(u,v);
        }
    for(int u : vertix)
        if(!out[u]) add_topo_edge(0,u);
    for(int u : vertix) out[u]=0;
}
 
void getsize(int u)
{
    sz[u]=1;
    for(int t=ht[u];~t;t=et[t].next)
    {
        int v=et[t].to;
        getsize(v);
        sz[u]+=sz[v];
    }
    ht[u]=-1;
}
 
int getans()
{
    int prodsz=1;getsize(0);
    for(int u : vertix)
        prodsz=1ll*prodsz*sz[u]%ha;
    return Pow(prodsz,ha-2);
}
 
int xi_jin_ping_is_good(int u)
{
    flag=0;cmt=0;findcrl(u,0);
    if(vertix.size()!=cmt) return 0;
    for(int u : crl) if(inc[u]) findgay(u,0);
    for(int i=0;i<crl.size()-1;i++) gay[crl[i]]=crl[i+1];
    gay[crl.back()]=crl[0];
    tsum=-1;build_topo();
    int res=getans();
    for(int i=1;i<crl.size();i++) gay[crl[i]]=crl[i-1];
    gay[crl[0]]=crl.back();
    tsum=-1;build_topo();
    res=(res+getans())%ha;
    vertix.clear();crl.clear();
    return res;
}
 
int main()
{
    memset(ht,-1,sizeof(ht));
    int x,y,ans=1;
    n=read()<<1;fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    for(int i=1;i<=n;i++)
    {
        x=read();y=read();
        add_edge(x,y+n/2);
    }
    for(int i=1;i<=n;i++)
    {
        if(done[i]) continue;
        x=xi_jin_ping_is_good(i);
        if(x==0) return puts("0"),0;
        ans=1ll*ans*x%ha;
    }
    ans=1ll*fac[n]*ans%ha;
    printf("%d\n",ans);
    return 0;
}