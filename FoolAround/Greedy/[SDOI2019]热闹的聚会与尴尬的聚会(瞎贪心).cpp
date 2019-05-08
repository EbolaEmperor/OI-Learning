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
    struct END{~END(){flush();} } EENNDD;
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
}
using IO::read;
using IO::putc;
using IO::print;

const int N=10010;
struct Edge{int to,nxt;} e[N*20];
int h[N],esum=0;
bool eg[N][N];
vector<int> ps,qs;
int qwq,n,m,deg[N];
int cnt[N],inp[N];

void add_edge(int u,int v)
{
    e[++esum]={v,h[u]};h[u]=esum;
    e[++esum]={u,h[v]};h[v]=esum;
    deg[u]++;deg[v]++;
}

int getp(int x)
{
    for(int i=h[x];i;i=e[i].nxt)
        if(inp[e[i].to]) cnt[x]++,cnt[e[i].to]++;
    inp[x]=1;
    ps.emplace_back(x);
    int res=n;
    for(int u : ps)
        res=min(res,cnt[u]);
    return res;
}

int getq()
{
    static int perm[N],inq[N];
    for(int i=1;i<=n;i++) perm[i]=i,inq[i]=0;
    random_shuffle(perm+1,perm+1+n);
    for(int i=1;i<=n;i++)
    {
        int u=perm[i],flag=1;
        for(int i=h[u];i;i=e[i].nxt)
            if(inq[e[i].to]){flag=0;break;}
        if(flag) inq[u]=1,qs.emplace_back(u);
    }
    return qs.size();
}

void _main_()
{
    n=read();m=read();
    for(int i=1,u,v;i<=m;i++)
    {
        u=read();v=read();
        if(u>v) swap(u,v);
        if(eg[u][v]) continue;
        add_edge(u,v);
        eg[u][v]=1;
    }
    static int perm[N],dv[N];
    for(int i=1;i<=n;i++) perm[i]=i;
    sort(perm+1,perm+1+n,[](int a,int b){return deg[a]>deg[b];});
    int q=getq();
    for(int i=n;i>=1;i--) dv[n/i]=i;
    for(int i=1;i<=n;i++)
        if(!dv[i]) dv[i]=dv[i-1];
    for(int i=1;i<=n;i++)
    {
        int p=getp(perm[i]);
        if(n/(p+1)>q) continue;
        if(dv[p]-1>q) continue;
        print(ps.size());putc(' ');
        for(int x : ps) print(x),putc(' ');
        putc('\n');print(qs.size());putc(' ');
        for(int x : qs) print(x),putc(' ');
        putc('\n');break;
    }
    for(int u=1;u<=n;u++)
        for(int i=h[u];i;i=e[i].nxt)
            eg[u][e[i].to]=0;
    ps.clear();qs.clear();esum=0;
    memset(h,0,sizeof(int)*(n+1));
    memset(deg,0,sizeof(int)*(n+1));
    memset(dv,0,sizeof(int)*(n+1));
    memset(cnt,0,sizeof(int)*(n+1));
    memset(inp,0,sizeof(int)*(n+1));
}

int main()
{
    srand(time(0));
    qwq=read();
    while(qwq--) _main_();
    return 0;
}