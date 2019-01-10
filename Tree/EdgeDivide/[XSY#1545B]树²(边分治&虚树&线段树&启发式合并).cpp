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
typedef pair<LL,LL> pll;
const int N=50010,M=1800010;
const int MAX=2.1e8;
int vertix[N],vcnt=0;
int d1[N<<1],d2[N<<1],now;
int ToT,n,dv[N];
LL ans=0;

pll operator + (const pll &a,const pll &b){return pll(a.first+b.first,a.second+b.second);}
inline int gmax(const int &x,const int &y){return (x>y)?x:y;}

struct SegmentTree
{
    LL sum[M];int cnt[M];
    int lc[M],rc[M],rt[N];
    int mmp[M],top,tot;
    SegmentTree(){top=tot=0;}
    int newnode(){return top?mmp[top--]:++tot;}
    void insert(int &o,int l,int r,int x)
    {
        if(!o) o=newnode();
        sum[o]+=x;cnt[o]++;
        if(l==r) return;
        int mid=floor(0.5*(l+r));
        if(x<=mid) insert(lc[o],l,mid,x);
        else insert(rc[o],mid+1,r,x);
    }
    pll query(int o,int l,int r,int nl,int nr)
    {
        if(!o) return pll(0,0);
        if(l==nl&&r==nr) return pll(sum[o],cnt[o]);
        int mid=floor(0.5*(l+r));
        if(nr<=mid) return query(lc[o],l,mid,nl,nr);
        if(nl>mid) return query(rc[o],mid+1,r,nl,nr);
        return query(lc[o],l,mid,nl,mid)+query(rc[o],mid+1,r,mid+1,nr);
    }
    void destroy(int &o)
    {
        if(!o) return;
        destroy(lc[o]);
        destroy(rc[o]);
        sum[o]=cnt[o]=0;
        mmp[++top]=o;o=0;
    }
} segt1,segt2;

namespace Virtual
{
    struct Edge{int to,next;} e[N<<1];
    int h[N],sum,sz[N];
    bool merged[N];
    void add_edge(int u,int v)
    {
        e[++sum]={v,h[u]};h[u]=sum;
        e[++sum]={u,h[v]};h[v]=sum;
    }
    void dfs1(int u,int fa,int rt,LL d)
    {
        pll tmp;
        int pre=d1[u]+now-d2[u]+d;
        if(dv[u]==1) tmp=segt2.query(segt2.rt[rt],-MAX,MAX,-MAX,pre);
        if(dv[u]==2) tmp=segt1.query(segt1.rt[rt],-MAX,MAX,-MAX,pre);
        if(dv[u]) ans+=tmp.first-(LL)pre*tmp.second;
        for(int t=h[u];t;t=e[t].next)
        {
            int v=e[t].to;
            if(v==fa) continue;
            if(!merged[v]) continue;
            dfs1(v,u,rt,d);
        }
    }
    void dfs2(int u,int fa,int rt)
    {
        if(dv[u]==1) segt1.insert(segt1.rt[rt],-MAX,MAX,d2[u]-d1[u]);
        if(dv[u]==2) segt2.insert(segt2.rt[rt],-MAX,MAX,d2[u]-d1[u]);
        for(int t=h[u];t;t=e[t].next)
        {
            int v=e[t].to;
            if(v==fa) continue;
            if(!merged[v]) continue;
            dfs2(v,u,rt);
        }
    }
    void merge(int x,int y,LL d)
    {
        if(sz[x]>=sz[y])
        {
            dfs1(y,x,x,d);
            segt1.destroy(segt1.rt[y]);
            segt2.destroy(segt2.rt[y]);
            dfs2(y,x,x);
        }
        else
        {
            dfs1(x,0,y,d);
            segt1.destroy(segt1.rt[x]);
            segt2.destroy(segt2.rt[x]);
            dfs2(x,0,y);
            swap(segt1.rt[x],segt1.rt[y]);
            swap(segt2.rt[x],segt2.rt[y]);
        }
    }
    void solve(int u,int fa)
    {
        sz[u]=1;
        if(dv[u]==1) segt1.insert(segt1.rt[u],-MAX,MAX,d2[u]-d1[u]);
        if(dv[u]==2) segt2.insert(segt2.rt[u],-MAX,MAX,d2[u]-d1[u]);
        for(int t=h[u];t;t=e[t].next)
        {
            int v=e[t].to;
            if(v==fa) continue;
            solve(v,u);
            merge(u,v,d2[u]<<1);
            sz[u]+=sz[v];
            merged[v]=1;
        }
    }
}

namespace Tree2
{
    struct Edge{int to,capa,next;} e[N<<1];
    int h[N],sum,dep[N],fa[16][N];
    int dfn[N],dfc;
    void add_edge(int u,int v,int w)
    {
        e[++sum].to=v;
        e[sum].capa=w;
        e[sum].next=h[u];
        h[u]=sum;
    }
    void init()
    {
        sum=dfc=0;
        memset(h,0,sizeof(int)*(n+1));
        for(int i=1,u,v,w;i<n;i++)
        {
            u=read();v=read();w=read();
            add_edge(u,v,w);
            add_edge(v,u,w);
        }
    }
    void predfs(int u,int la)
    {
        dfn[u]=++dfc;
        for(int k=1;k<=15;k++)
            fa[k][u]=fa[k-1][fa[k-1][u]];
        for(int t=h[u];t;t=e[t].next)
        {
            int v=e[t].to;
            if(v==la) continue;
            dep[v]=dep[u]+1;
            d2[v]=d2[u]+e[t].capa;
            fa[0][v]=u;predfs(v,u);
        }
    }
    int getlca(int x,int y)
    {
        if(dep[x]<dep[y]) swap(x,y);
        for(int k=15;k>=0;k--)
            if(dep[fa[k][x]]>=dep[y]) x=fa[k][x];
        if(x==y) return x;
        for(int k=15;k>=0;k--)
            if(fa[k][x]!=fa[k][y])
                x=fa[k][x],y=fa[k][y];
        return fa[0][x];
    }
    bool cmp(const int &a,const int &b){return dfn[a]<dfn[b];}
    void solve()
    {
        static int stk[N],rcd[N];
        int top=0,tot=0;
        sort(vertix+1,vertix+1+vcnt,cmp);
        for(int i=1;i<=vcnt;i++)
        {
            int x=vertix[i];
            if(!top){stk[++top]=rcd[++tot]=x;continue;}
            int f=getlca(x,stk[top]);
            while(dep[f]<dep[stk[top]])
            {
                if(dep[f]>=dep[stk[top-1]])
                {
                    Virtual::add_edge(stk[top--],f);
                    if(f!=stk[top]) stk[++top]=rcd[++tot]=f;
                    break;
                }
                Virtual::add_edge(stk[top],stk[top-1]);top--;
            }
            if(x!=stk[top]) stk[++top]=rcd[++tot]=x;
        }
        while(top>1) Virtual::add_edge(stk[top],stk[top-1]),top--;
        Virtual::solve(stk[1],0);
        for(int i=1;i<=vcnt;i++) dv[vertix[i]]=0;
        segt1.destroy(segt1.rt[stk[1]]);
        segt2.destroy(segt2.rt[stk[1]]);
        segt1.top=segt1.tot=segt2.top=segt2.tot=0;
        Virtual::sum=0;
        for(int i=1;i<=tot;i++)
        {
            Virtual::merged[rcd[i]]=0;
            Virtual::h[rcd[i]]=0;
        }
    }
}

namespace Tree1
{
    const int N=100010;
    struct E{int v,w;};vector<E> G[N];
    struct Edge{int from,to,capa,next;} e[N<<1];
    int h[N],sum,cnt,sz[N],rsz[N],tot,rt,mxs;
    bool done[N<<1];
    void add_edge(int u,int v,int w)
    {
        e[++sum]={u,v,w,h[u]};h[u]=sum;
        e[++sum]={v,u,w,h[v]};h[v]=sum;
    }
    void init()
    {
        sum=-1;cnt=n;
        memset(h,-1,sizeof(int)*(n+1));
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1,u,v,w;i<n;i++)
        {
            u=read();v=read();w=read();
            G[u].push_back({v,w});
            G[v].push_back({u,w});
        }
    }
    void build(int u,int fa)
    {
        int lst=0,scnt=0,sp=0;
        for(E e : G[u]) if(e.v!=fa) scnt++;
        for(E e : G[u])
        {
            int v=e.v,w=e.w;
            if(v==fa) continue;
            if(!lst) add_edge(u,v,w),lst=u;
            else if(sp==scnt) add_edge(lst,v,w);
            else h[++cnt]=-1,add_edge(lst,cnt,0),add_edge(cnt,v,w),lst=cnt;
            sp++;build(v,u);
        }
    }
    void getsz(int u,int fa)
    {
        sz[u]=1;rsz[u]=(u<=n);
        for(int t=h[u];~t;t=e[t].next)
        {
            int v=e[t].to;
            if(v==fa) continue;
            if(done[t]) continue;
            getsz(v,u);
            sz[u]+=sz[v];
            rsz[u]+=rsz[v];
        }
    }
    void dfs(int u,int fa,int s,int p)
    {
        if(u<=n) ans+=(LL)d1[u]*s,vertix[++vcnt]=u,dv[u]=p;
        for(int t=h[u];~t;t=e[t].next)
        {
            int v=e[t].to;
            if(v==fa) continue;
            if(done[t]) continue;
            d1[v]=d1[u]+e[t].capa;
            dfs(v,u,s,p);
        }
    }
    void find(int u,int fa)
    {
        sz[u]=1;rsz[u]=(u<=n);
        for(int t=h[u];~t;t=e[t].next)
        {
            int v=e[t].to;
            if(v==fa) continue;
            if(done[t]) continue;
            find(v,u);
            sz[u]+=sz[v];
            rsz[u]+=rsz[v];
            if(rt<0||gmax(sz[v],tot-sz[v])<mxs)
                rt=t,mxs=gmax(sz[v],tot-sz[v]);
        }
    }
    void solve(int edg)
    {
        done[edg]=done[edg^1]=1;
        int u=e[edg].from,v=e[edg].to;now=e[edg].capa;
        getsz(u,v);getsz(v,u);vcnt=0;
        d1[u]=0;dfs(u,v,rsz[v],1);
        d1[v]=0;dfs(v,u,rsz[u],2);
        ans+=(LL)e[edg].capa*rsz[u]*rsz[v];
        Tree2::solve();
        rt=-1;tot=sz[u];find(u,v);
        if(rt>=0) solve(rt);
        rt=-1;tot=sz[v];find(v,u);
        if(rt>=0) solve(rt);
    }
    void main()
    {
        memset(done,0,sizeof(bool)*(sum+2));
        rt=-1;tot=cnt;
        find(1,0);
        solve(rt);
    }
}

int main(int argc,char* argv[])
{
    ToT=read();
    while(ToT--)
    {
        n=read();ans=0;
        Tree1::init();
        Tree1::build(1,0);
        Tree2::init();
        Tree2::dep[1]=1;
        Tree2::predfs(1,0);
        Tree1::main();
        printf("%lld\n",ans);
    }
    return 0;
}