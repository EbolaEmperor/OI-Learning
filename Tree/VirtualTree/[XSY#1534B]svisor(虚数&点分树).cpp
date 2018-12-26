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
const int N=100010;
struct Edger{int to,next;} e[N<<1];
int h[N],esum=0,n;
int root,sum,mxsz[N],sz[N];
int *s1[N],*s2[N],cnt[N],dep[N];
int maxd1[N],maxd2[N],mxd;
int dis[N][20],rt[N][20],deep[N];
int trsz[N],trdep[N],dfn[N],idx[N],dfc=0;
int hson[N],top[N],trfa[N];
bool done[N];

void add_edge(int u,int v)
{
    e[++esum].to=v;
    e[esum].next=h[u];
    h[u]=esum;
}

void find(int u,int fa)
{
    sz[u]=1;mxsz[u]=0;
    mxd=max(mxd,dep[u]);
    if(u<=n) cnt[dep[u]]++;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]||v==fa) continue;
        find(v,u);sz[u]+=sz[v];
        mxsz[u]=max(mxsz[u],sz[v]);
    }
    mxsz[u]=max(mxsz[u],sum-sz[u]);
    if(mxsz[u]<mxsz[root]) root=u;
}

void dfs(int u,int fa,int rot)
{
    sz[u]=1;
    mxd=max(mxd,dep[u]);
    if(u<=n) cnt[dep[u]]++;
    rt[u][++deep[u]]=rot;
    dis[u][deep[u]]=dep[u];
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]||v==fa) continue;
        dep[v]=dep[u]+1;
        dfs(v,u,rot);sz[u]+=sz[v];
    }
}

void build(int u)
{
    done[u]=1;mxd=0;dep[u]=0;dfs(u,0,u);maxd1[u]=mxd;
    s1[u]=new int[mxd+1];s1[u][0]=cnt[0];cnt[0]=0;
    for(int i=1;i<=mxd;i++) s1[u][i]=s1[u][i-1]+cnt[i],cnt[i]=0;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]) continue;
        sum=sz[v];root=0;mxd=0;find(v,u);maxd2[root]=mxd;
        s2[root]=new int[mxd+1];s2[root][0]=cnt[0];cnt[0]=0;
        for(int i=1;i<=mxd;i++) s2[root][i]=s2[root][i-1]+cnt[i],cnt[i]=0;
        build(root);
    }
}

int query(int u,int r)
{
    int ans=0;
    for(int k=deep[u];k>=1;k--)
    {
        int rot=rt[u][k],d=dis[u][k],d2=dis[u][k-1];
        if(r>=d) ans+=(r-d>=maxd1[rot]?s1[rot][maxd1[rot]]:s1[rot][r-d]);
        if(k>1&&r>=d2) ans-=(r-d2>=maxd2[rot]?s2[rot][maxd2[rot]]:s2[rot][r-d2]);
    }
    return ans;
}

void predfs1(int u)
{
    trsz[u]=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==trfa[u]) continue;
        trdep[v]=trdep[u]+1;
        trfa[v]=u;predfs1(v);
        trsz[u]+=trsz[v];
        if(trsz[v]>trsz[hson[u]]) hson[u]=v;
    }
}

void predfs2(int u,int tp)
{
    idx[dfn[u]=++dfc]=u;top[u]=tp;
    if(hson[u]) predfs2(hson[u],tp);
    for(int t=h[u];t;t=e[t].next)
        if(e[t].to!=trfa[u]&&e[t].to!=hson[u])
            predfs2(e[t].to,e[t].to);
}

int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(trdep[top[x]]<trdep[top[y]]) swap(x,y);
        x=trfa[top[x]];
    }
    return trdep[x]<trdep[y]?x:y;
}

int jump(int x,int d)
{
    while(d)
    {
        int t=trdep[x]-trdep[top[x]]+1;
        if(d>=t) d-=t,x=trfa[top[x]];
        else break;
    }
    return idx[dfn[x]-d];
}

int gao()
{
    static stack<int> stk;
    static int m,a[N],r[N],fafa[N];
    static bool trp[N];
    vector<int> ls;
    m=read();r[0]=-1;
    for(int i=1;i<=m;i++)
        a[i]=read(),r[a[i]]=read()<<1,trp[a[i]]=1;
    sort(a+1,a+1+m,[](int x,int y){return dfn[x]<dfn[y];});
    stk.push(a[1]);
    for(int i=2;i<=m;i++)
    {
        int c=lca(a[i],stk.top());
        if(!trp[c]) r[c]=-1;
        while(!stk.empty()&&trdep[stk.top()]>trdep[c])
        {
            int x=stk.top();
            ls.push_back(x);stk.pop();
            fafa[x]=(!stk.empty()&&trdep[stk.top()]>trdep[c])?stk.top():c;
        }
        if(stk.empty()||trdep[c]>trdep[stk.top()]) stk.push(c);
        if(c!=a[i]) stk.push(a[i]);
    }
    while(!stk.empty())
    {
        int x=stk.top();stk.pop();
        ls.push_back(x);
        fafa[x]=stk.empty()?0:stk.top();
    }
    for(int i=1;i<=m;i++) trp[a[i]]=0;
    for(int i=0;i<ls.size();i++)
        r[fafa[ls[i]]]=max(r[fafa[ls[i]]],r[ls[i]]-(trdep[ls[i]]-trdep[fafa[ls[i]]]));
    for(int i=ls.size()-1;i>=0;i--)
        r[ls[i]]=max(r[ls[i]],r[fafa[ls[i]]]-(trdep[ls[i]]-trdep[fafa[ls[i]]]));
    int ans=0;
    for(int x : ls) ans+=query(x,r[x]);
    for(int i=0;i<ls.size()-1;i++)
    {
        int x=ls[i],y=fafa[ls[i]],d=trdep[x]-trdep[y];
        if(r[x]+r[y]>=d)
        {
            int t=(r[x]+d-r[y])/2;
            int z=jump(x,t);
            ans-=query(z,r[x]-t);
        }
    }
    return ans;
}

int main()
{
    n=read();
    for(int i=1,u,v;i<n;i++)
    {
        u=read();v=read();
        add_edge(u,n+i);add_edge(n+i,u);
        add_edge(v,n+i);add_edge(n+i,v);
    }
    predfs1(1);predfs2(1,1);
    mxsz[root=0]=INT_MAX;sum=2*n;find(1,0);
    memset(cnt,0,sizeof(cnt));build(root);
    int Q=read();
    while(Q--) print(gao());
    flush();
    return 0;
}