#include<bits/stdc++.h>
using namespace std;

namespace IO
{
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
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    inline void YES(){putc('Y');putc('e');putc('s');putc('\n');}
    inline void NO(){putc('N');putc('o');putc('\n');}
}

using namespace IO;
const int N=100010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],sum=0,n,Q;
int fa[N],val[N],dep[N];
int num[55],cnt=0;

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int la)
{
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la) continue;
        val[v]=e[t].capa;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs(v,u);
    }
}

int main()
{
    int T=read();
    for(int cas=1;cas<=T;cas++)
    {
        printf("Case #%d:\n",cas);
        sum=0;memset(h,0,sizeof(h));
        n=read();
        for(int i=1;i<n;i++)
        {
            int u=read(),v=read(),w=read();
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
        dep[1]=1;dfs(1,0);
        for(int Q=read();Q;Q--)
        {
            int u=read(),v=read();cnt=0;
            while(u!=v)
            {
                if(dep[u]<dep[v]) swap(u,v);
                num[++cnt]=val[u];u=fa[u];
                if(cnt==50) break;
            }
            if(cnt<3) NO();
            else if(cnt<50)
            {
                bool flag=0;
                sort(num+1,num+1+cnt);
                for(int i=3;i<=cnt;i++)
                    if(num[i]<num[i-2]+num[i-1]) flag=1;
                flag?YES():NO();
            }
            else YES();
        }
        flush();
    }
    return 0;
}