#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return EOF;return *H++;
}
inline LL read()
{
    LL x=0;char c=Get();
    while(!isdigit(c)&&c!=EOF) c=Get();
    if(c==EOF) return EOF;
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=100010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n;LL a[N];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

LL dfs(int u,int fa)
{
    LL falun=0;
    for(int t=h[u];t;t=e[t].next)
        if(e[t].to!=fa) falun^=dfs(e[t].to,u);
    return a[u]-(a[u]<=falun);
}

int main()
{
    while(~(n=read()))
    {
        for(int i=1;i<=n;i++)
            a[i]=log2(read())+1;
        memset(h,0,sizeof(h));sum=0;
        for(int i=1;i<n;i++)
        {
            int u=read()+1,v=read()+1;
            add_edge(u,v);
            add_edge(v,u);
        }
        puts(dfs(1,0)?"Alice":"Marisa");
    }
    return 0;
}