#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
char Get(){if(H==T) T=(H=buf)+fread(buf,1,S,stdin);return H==T?-1:*H++;}
int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

typedef unsigned long long ULL;
const int N=200010;
struct Edge{int to,next;} e[N];
int he[N],sum=0;
int fa[18][N],n;
ULL h[18][N],pw[18];
int dep[N];
int sa[N],rk[N];
set<int> s[N];
int ans=0;

inline void upmax(int &x,const int &y){if(y>x) x=y;}

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=he[u];
    he[u]=sum;
}

int jump(int u,int x)
{
    for(int i=17;i>=0;i--)
        if(x&(1<<i)) u=fa[i][u];
    return h[0][u];
}

int lcp(int u,int v)
{
    int res=0;
    for(int i=17;i>=0;i--)
        if(h[i][u]==h[i][v])
        {
            u=fa[i][u];
            v=fa[i][v];
            res|=1<<i;
        }
    return res;
}

bool cmp(const int &a,const int &b)
{
    int len=lcp(a,b);
    return jump(a,len)<jump(b,len);
}

void dfs(int u)
{
    s[u].insert(rk[u]);
    for(int tmp=he[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;dfs(v);
        if(s[u].size()<s[v].size()) swap(s[u],s[v]);
        for(auto it=s[v].begin();it!=s[v].end();it++)
        {
            auto p=s[u].lower_bound(*it);
            if(p!=s[u].end()) upmax(ans,lcp(sa[*it],sa[*p])+dep[u]);
            if(p!=s[u].begin()) upmax(ans,lcp(sa[*it],sa[*--p])+dep[u]);
            s[u].insert(*it);
        }
    }
}

int main()
{
    n=read();
    for(int i=2;i<=n;i++)
    {
        fa[0][i]=read();
        h[0][i]=read()+1;
        dep[i]=dep[fa[0][i]]+1;
        add_edge(fa[0][i],i);
    }
    pw[0]=1;pw[1]=311;
    for(int i=2;i<=17;i++)
        pw[i]=pw[i-1]*pw[i-1];
    for(int j=1;j<=17;j++)
        for(int i=1;i<=n;i++)
        {
            fa[j][i]=fa[j-1][fa[j-1][i]];
            h[j][i]=h[j-1][i]*pw[j]+h[j-1][fa[j-1][i]];
        }
    for(int i=1;i<=n;i++) sa[i]=i;
    sort(sa+1,sa+1+n,cmp);
    for(int i=1;i<=n;i++) rk[sa[i]]=i;
    dfs(1);printf("%d\n",ans);
    return 0;
}