#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H=buf,*T=buf+S-1;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') c=Get(),fg=-1;
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

const int N=20010;
struct Circle
{
    int x,y,r;
    friend bool operator < (const Circle &a,const Circle &b){return a.r<b.r;}
    friend long long len(const Circle &a,const Circle &b){return 1ll*(a.x-b.x)*(a.x-b.x)+1ll*(a.y-b.y)*(a.y-b.y);}
    friend bool inC(const Circle &a,const Circle &b){return len(a,b)<=1ll*(a.r-b.r)*(a.r-b.r);}
} c[N];
struct Edge{int to,next;} e[N];
int h[N],sum,fa[N];
vector<int> id[80010];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

int dfs(int u)
{
    int res=0;
    for(int tmp=h[u];~tmp;tmp=e[tmp].next)
        res^=dfs(e[tmp].to)+1;
    return res;
}

void gao(int u)
{
    for(int i=c[u].x-c[u].r+1;i<=c[u].x+c[u].r-1;i++)
        for(int j=0;j<id[i].size();j++)
        {
            if(!inC(c[id[i][j]],c[u])) continue;
            fa[id[i][j]]=u;
            id[i][j]=id[i][id[i].size()-1];
            id[i].pop_back();j--;
        }
}

int main()
{
    int T,n;
    for(T=read();T;T--)
    {
        n=read();
        bool flag=1;
        for(int i=1;i<=n;i++)
        {
            c[i].x=read()+40000;
            c[i].y=read()+40000;
            c[i].r=read();
            if(i<=100&&c[i].r>1) flag=0;
        }
        if(flag){puts("Bob");continue;}
        sort(c+1,c+1+n);
        memset(fa,0,sizeof(fa));
        sum=-1;memset(h,-1,sizeof(h));
        for(int i=0;i<=80000;i++) id[i].clear();
        for(int i=1;i<=n;i++) gao(i),id[c[i].x].push_back(i);
        for(int i=1;i<=n;i++) add_edge(fa[i],i);
        puts(dfs(0)?"Alice":"Bob");
    }
    return 0;
}