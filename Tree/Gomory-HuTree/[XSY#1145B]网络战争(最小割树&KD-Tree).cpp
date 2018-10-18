#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
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
        int x=0,fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x*fg;
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
const int N=150010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],sum=0,n,idx[N],ff[N];
int dep[N],mn[18][N],fa[18][N],st[N];
int pdx[2010],tdx[2010];
bool vis[N];

int find(int x){return ff[x]==x?x:ff[x]=find(ff[x]);}

void add_edge(int u,int v,int w)
{
    if(find(u)!=find(v))
        ff[find(u)]=find(v);
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int la)
{
    vis[u]=1;
    for(int i=1;i<=17;i++)
    {
        fa[i][u]=fa[i-1][fa[i-1][u]];
        mn[i][u]=min(mn[i-1][u],mn[i-1][fa[i-1][u]]);
    }
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;
        if(v==la) continue;
        mn[0][v]=e[tmp].capa;
        dep[v]=dep[u]+1;
        fa[0][v]=u;dfs(v,u);
    }
}

int getmin(int u,int v)
{
    int ans=INF;
    if(find(u)!=find(v)) return 0;
    if(dep[u]<dep[v]) swap(u,v);
    for(int i=17;i>=0;i--)
        if(dep[fa[i][u]]>=dep[v])
        {
            ans=min(ans,mn[i][u]);
            u=fa[i][u];
        }
    for(int i=17;i>=0;i--)
        if(fa[i][u]!=fa[i][v])
        {
            ans=min(ans,mn[i][u]);
            ans=min(ans,mn[i][v]);
            u=fa[i][u];v=fa[i][v];
        }
    if(u!=v)
    {
        ans=min(ans,mn[0][u]);
        ans=min(ans,mn[0][v]);
    }
    return ans;
}

struct Graph
{
    struct Edge{int from,to,flow,capa,next;};
    vector<Edge> e;
    vector<int> h,deep,cur,col;
    vector<bool> vis;
    int sum=-1,n,m,s,t,now,self;

    void Init()
    {
        now=0;
        h.resize(n+1);
        deep.resize(n+1);
        cur.resize(n+1);
        vis.resize(n+1);
        col.resize(n+1);
        for(int i=0;i<=n;i++) h[i]=-1;
    }

    void add_edge(int u,int v,int w)
    {
        e.push_back((Edge){u,v,0,w,h[u]});
        e.push_back((Edge){v,u,0,0,h[v]});
        h[u]=++sum;h[v]=++sum;
    }

    bool BFS()
    {
        queue<int> f;f.push(s);
        for(int i=0;i<=n;i++) vis[i]=0;
        vis[s]=1;deep[s]=0;
        while(!f.empty())
        {
            int o=f.front();
            for(int tmp=h[o];~tmp;tmp=e[tmp].next)
            {
                if((!vis[e[tmp].to])&&e[tmp].capa>e[tmp].flow)
                {
                    vis[e[tmp].to]=1;
                    f.push(e[tmp].to);
                    deep[e[tmp].to]=deep[o]+1;
                    if(e[tmp].to==t) return 1;
                }
            }
            f.pop();
        }
        return vis[t];
    }

    int DFS(int u,int a)
    {
        if(u==t||a==0) return a;
        int flow=0,f;
        for(int &tmp=cur[u];~tmp;tmp=e[tmp].next)
            if(deep[u]+1==deep[e[tmp].to])
            {
                f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
                if(f>0)
                {
                    flow+=f;a-=f;
                    e[tmp].flow+=f;
                    e[tmp^1].flow-=f;
                    if(a==0) break;
                }
            }
        return flow;
    }

    int Dinic(int x,int y)
    {
        if(x==y) return INF;
        int flow=0;s=x;t=y;
        for(int i=0;i<=sum;i++) e[i].flow=0;
        while(BFS())
        {
            for(int i=0;i<=n;i++) cur[i]=h[i];
            flow+=DFS(s,INF);
        }
        return flow;
    }

    void dfs(int u)
    {
        col[u]=now;
        for(int t=h[u];~t;t=e[t].next)
            if(e[t].capa>e[t].flow&&col[e[t].to]!=now)
                dfs(e[t].to);
    }

    void build(int l,int r)
    {
        if(l>=r) return;
        int cut=Dinic(pdx[l],pdx[l+1]);
        now++;dfs(s);int p=l,q=r;
        for(int i=l;i<=r;i++)
            if(col[pdx[i]]==now) tdx[p++]=pdx[i];
            else tdx[q--]=pdx[i];
        ::add_edge(st[self]+s-1,st[self]+t-1,cut);
        ::add_edge(st[self]+t-1,st[self]+s-1,cut);
        for(int i=l;i<=r;i++) pdx[i]=tdx[i];
        build(l,p-1);build(q+1,r);
    }
} g[N];

int falun;
struct Point
{
    int d[2],id;
    Point(int x=0,int y=0,int z=0){d[0]=x;d[1]=y;id=z;}
    int& operator [] (const int &x){return x<2?d[x]:id;}
    bool operator < (const Point &a) const{return d[falun]<a.d[falun];}
} pt[N];
struct Node{int x,y,w;} node[N];
int now,ansid,dist;
int ans[N];

inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}
inline int sqr(const int &x){return x*x;}
inline int dis(int x1,int y1,int x2,int y2){return sqr(x1-x2)+sqr(y1-y2);}

struct KD_Tree
{
    int d[2],mn[2],mx[2],id;
    KD_Tree *lc,*rc;
    KD_Tree(int x=0,int y=0,int z=0)
    {
        d[0]=mn[0]=mx[0]=x;
        d[1]=mn[1]=mx[1]=y;
        id=z;lc=rc=nullptr;
    }
    int disp(Point &p)
    {
        int d1=0,d2=0;
        upmax(d1,mn[0]-p[0]);
        upmax(d1,p[0]-mx[0]);
        upmax(d2,mn[1]-p[1]);
        upmax(d2,p[1]-mx[1]);
        return d1*d1+d2*d2;
    }
    void maintain()
    {
        for(int i=0;i<2;i++)
        {
            if(lc==nullptr) goto uprc;
            upmin(mn[i],lc->mn[i]);
            upmax(mx[i],lc->mx[i]);
            uprc: if(rc==nullptr) continue;
            upmin(mn[i],rc->mn[i]);
            upmax(mx[i],rc->mx[i]);
        }
    }
    void build(int l,int r,int d=0)
    {
        int mid=(l+r)/2;falun=d;
        nth_element(pt+l,pt+mid,pt+r+1);
        *this=KD_Tree(pt[mid][0],pt[mid][1],pt[mid][2]);
        if(l<mid) lc=new KD_Tree,lc->build(l,mid-1,d^1);
        if(r>mid) rc=new KD_Tree,rc->build(mid+1,r,d^1);
        maintain();
    }
    void find(Point &p)
    {
        int tmp=(id==now)?INF:dis(d[0],d[1],p[0],p[1]);
        if(tmp<dist||tmp==dist&&id<ansid) dist=tmp,ansid=id;
        if(lc==nullptr&&rc==nullptr) return;
        if(lc==nullptr){rc->find(p);return;}
        if(rc==nullptr){lc->find(p);return;}
        int dl=lc->disp(p),dr=rc->disp(p);
        if(dl<=dr)
        {
            if(dl<=dist) lc->find(p);
            if(dr<=dist) rc->find(p);
        }
        else
        {
            if(dr<=dist) rc->find(p);
            if(dl<=dist) lc->find(p);
        }
    }
} *root;

int main()
{
    n=read();st[0]=1;
    for(int i=0;i<N;i++) ff[i]=i;
    for(int i=1;i<=n;i++)
    {
        node[i].x=read();node[i].y=read();node[i].w=read();
        pt[i]=Point(node[i].x,node[i].y,i);
        g[i].n=read();g[i].m=read();g[i].self=i;g[i].Init();
        st[i]=st[i-1]+g[i-1].n;
        for(int j=1;j<=g[i].m;j++)
        {
            int x=read(),y=read(),w=read();
            g[i].add_edge(x,y,w);
            g[i].add_edge(y,x,w);
        }
        for(int j=1;j<=g[i].n;j++) pdx[j]=j;
        g[i].build(1,g[i].n);
    }
    root=new KD_Tree;
    root->build(1,n);
    for(int i=1;i<=n;i++)
    {
        now=pt[i].id;dist=INF;
        root->find(pt[i]);
        ans[pt[i].id]=ansid;
    }
    for(int i=1;i<=n;i++)
    {
        if(ans[ans[i]]==i&&idx[ans[i]])
        {
            e[idx[ans[i]]].capa+=node[i].w;
            e[idx[ans[i]]+1].capa+=node[i].w;
        }
        else
        {
            idx[i]=sum+1;
            add_edge(st[i],st[ans[i]],node[i].w);
            add_edge(st[ans[i]],st[i],node[i].w);
        }
    }
    for(int i=1;i<=st[n]+g[n].n-1;i++)
        if(!vis[i])
        {
            mn[0][i]=INF;
            fa[0][i]=i;
            dep[i]=1;
            dfs(i,0);
        }
    for(int Q=read();Q;Q--)
    {
        int x=read(),y=read(),u=read(),v=read();
        print(getmin(st[x]+u-1,st[y]+v-1));
    }
    flush();
    return 0;
}