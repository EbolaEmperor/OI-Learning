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

const int N=500010;
struct Edge
{
    int u,v,w;
    Edge(int _u=0,int _v=0,int _w=0):u(_u),v(_v),w(_w){}
    bool operator < (const Edge &a) const{return w<a.w;}
} e[N];
int n,m,fa[N],cnt=0;
bool loop[N];
long long ans=0;

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

int main()
{
    n=read();m=read();
    for(int i=1,u,v,w;i<=m;i++)
    {
        u=read();v=read();w=read();
        e[i]=Edge(u,v,w);
    }
    sort(e+1,e+1+m);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1,u,v,w;i<=m;i++)
    {
        u=e[i].u;v=e[i].v;w=e[i].w;
        u=find(u);v=find(v);
        if(u==v)
        {
            if(loop[u]) continue;
            ans+=w;loop[u]=1;cnt++;
        }
        else
        {
            if(loop[u]&&loop[v]) continue;
            fa[u]=v;ans+=w;cnt++;
            loop[v]|=loop[u];
        }
    }
    if(cnt<n) puts("No");
    else printf("%lld\n",ans);
    return 0;
}