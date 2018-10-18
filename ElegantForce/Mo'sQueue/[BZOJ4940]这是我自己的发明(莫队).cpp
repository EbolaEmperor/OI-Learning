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
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
const int M=4500010,N=100010,B=350;
struct Edge{int to,next;} e[N<<1];
struct Qry{int x,y,d,id;} q[M],qx[4],qy[4];
int h[N],sum=0,n,m,tot=0,qcnt=0,root=1;
int in[N],out[N],idx[N],dfc=0;
int fa[17][N],dep[N];
int val[N],Hash[N],hs;
int cntx[N],cnty[N],col[N<<1];
long long ans[N*5];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u)
{
    idx[in[u]=++dfc]=u;
    for(int i=1;i<=16;i++)
        fa[i][u]=fa[i-1][fa[i-1][u]];
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa[0][u]) continue;
        dep[v]=dep[u]+1;
        fa[0][v]=u;dfs(v);
    }
    out[u]=dfc;
}

int jump(int x,int aim)
{
    for(int i=16;i>=0;i--)
        if(dep[fa[i][x]]>dep[aim])
            x=fa[i][x];
    return x;
}

bool operator < (const Qry &a,const Qry &b)
{
    if(a.x/B!=b.x/B) return a.x/B<b.x/B;
    if((a.x/B)&1) return a.y>b.y;
    return a.y<b.y;
}

void getqx(int x,int &cx,Qry *qx)
{
    if(root==x) qx[++cx].x=n,qx[cx].d=1;
    else if(in[root]>in[x]&&in[root]<=out[x])
    {
        int z=jump(root,x);
        qx[++cx].x=in[z]+n-1,qx[cx].d=1;
        qx[++cx].x=out[z],qx[cx].d=-1;
    }
    else
    {
        qx[++cx].x=out[x],qx[cx].d=1;
        qx[++cx].x=in[x]-1,qx[cx].d=-1;
    }
}

void getq()
{
    int opt,x,y;
    for(int Q=1;Q<=m;Q++)
    {
        opt=read();x=read();
        if(opt==1){root=x;continue;}
        y=read();qcnt++;
        int cx=0,cy=0;
        getqx(x,cx,qx);
        getqx(y,cy,qy);
        for(int i=1;i<=cx;i++)
            for(int j=1;j<=cy;j++)
            {
                if(!qx[i].x||!qy[j].x) continue;
                int fg=qx[i].d*qy[j].d;
                q[++tot]={qx[i].x,qy[j].x,fg,qcnt};
            }
    }
    sort(q+1,q+1+tot);
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++) 
        Hash[i]=val[i]=read();
    sort(Hash+1,Hash+1+n);
    int hs=unique(Hash+1,Hash+1+n)-(Hash+1);
    for(int i=1;i<=n;i++)
        val[i]=lower_bound(Hash+1,Hash+1+hs,val[i])-Hash;
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    dep[1]=1;dfs(1);getq();
    for(int i=1;i<=n;i++) col[i+n]=col[i]=val[idx[i]];
    int px=0,py=0;long long cur=0;
    for(int i=1;i<=tot;i++)
    {
        while(px<q[i].x) px++,cntx[col[px]]++,cur+=cnty[col[px]];
        while(px>q[i].x) cur-=cnty[col[px]],cntx[col[px]]--,px--;
        while(py<q[i].y) py++,cnty[col[py]]++,cur+=cntx[col[py]];
        while(py>q[i].y) cur-=cntx[col[py]],cnty[col[py]]--,py--;
        ans[q[i].id]+=cur*q[i].d;
    }
    for(int i=1;i<=qcnt;i++) print(ans[i]);
    flush();
    return 0;
}