#include<bits/stdc++.h>
using namespace std;
 
const int N=100010;
struct OPT{int opt,x,y;} opt[N];
vector<int> g[N];
int n,m,col[N],cc[N],ans[N];
 
namespace Task1
{
    int cnt[N<<2];
    int fa[N],top[N],hson[N];
    int dfn[N],idx[N],dfc=0;
    int sz[N],dep[N];
 
    void build(int o,int l,int r)
    {
        if(l==r){cnt[o]=1;return;}
        int mid=(l+r)/2;
        build(o<<1,l,mid);
        build(o<<1|1,mid+1,r);
        cnt[o]=cnt[o<<1]+cnt[o<<1|1];
        if(col[idx[mid]]==col[idx[mid+1]]) cnt[o]--;
    }
 
    void update(int o,int l,int r,int k)
    {
        if(l==r) return;
        int mid=(l+r)/2;
        if(k<=mid) update(o<<1,l,mid,k);
        else update(o<<1|1,mid+1,r,k);
        cnt[o]=cnt[o<<1]+cnt[o<<1|1];
        if(col[idx[mid]]==col[idx[mid+1]]) cnt[o]--;
    }
 
    int query(int o,int l,int r,int nl,int nr)
    {
        if(l>=nl&&r<=nr)
        {
            int res=cnt[o];
            if(l>nl&&col[idx[l]]==col[idx[l-1]]) res--;
            return res;
        }
        int mid=(l+r)/2,res=0;
        if(nl<=mid) res+=query(o<<1,l,mid,nl,nr);
        if(nr>mid) res+=query(o<<1|1,mid+1,r,nl,nr);
        return res;
    }
 
    void dfs1(int u)
    {
        sz[u]=1;
        for(int v : g[u])
        {
            if(v==fa[u]) continue;
            dep[v]=dep[u]+1;
            fa[v]=u;dfs1(v);
            sz[u]+=sz[v];
            if(sz[v]>sz[hson[u]]) hson[u]=v;
        }
    }
 
    void dfs2(int u,int tp)
    {
        top[u]=tp;
        idx[dfn[u]=++dfc]=u;
        if(hson[u]) dfs2(hson[u],tp);
        for(int v : g[u])
            if(v!=fa[u]&&v!=hson[u])
                dfs2(v,v);
    }
 
    int lca(int x,int y)
    {
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            x=fa[top[x]];
        }
        return dep[x]<dep[y]?x:y;
    }
 
    int query(int x,int y)
    {
        int res=0;
        while(top[x]!=top[y])
        {
            if(dep[top[x]]<dep[top[y]]) swap(x,y);
            res+=query(1,1,n,dfn[top[x]],dfn[x]);
            if(col[top[x]]==col[fa[top[x]]]) res--;
            x=fa[top[x]];
        }
        if(dep[x]>dep[y]) swap(x,y);
        res+=query(1,1,n,dfn[x],dfn[y]);
        return res;
    }
 
    void main()
    {
        dfs1(1);dfs2(1,1);build(1,1,n);
        int op,x,y;col[0]=-1;
        for(int i=1;i<=m;i++)
        {
            op=opt[i].opt;x=opt[i].x;y=opt[i].y;
            if(op==1) col[x]=y,update(1,1,n,dfn[x]);
            if(op==2) ans[i]=query(x,y);
        }
    }
}
 
namespace Task2
{
    const int B=3155,BB=320;
    struct Qry
    {
        int l,r,t,x,id;
        Qry(int _l=0,int _r=0,int _x=0,int _t=0,int _id=0):l(_l),r(_r),x(_x),t(_t),id(_id){}
        bool operator < (const Qry &b) const
        {
            if(l/B!=b.l/B) return l/B<b.l/B;
            if(r/B!=b.r/B) return r/B<b.r/B;
            return t<b.t;
        }
    } qry[N];
    struct Chg{int x,c,pre;} ch[N];
    int q=0,idfn[N],odfn[N],idx[N<<1],dfc=0;
    int cnt[N],bcntcnt[N],cntcnt[N],a[N];
    bool inq[N];
 
    void dfs(int u,int fa)
    {
        idfn[u]=++dfc;
        idx[dfc]=u;
        for(int v : g[u])
            if(v!=fa) dfs(v,u);
        odfn[u]=++dfc;
        idx[dfc]=u;
    }
 
    Qry addq(int x,int y,int id)
    {
        int z=Task1::lca(x,y);
        if(x==z) return Qry(idfn[x],idfn[y],0,id,id);
        if(y==z) return Qry(idfn[y],idfn[x],0,id,id);
        if(idfn[x]>idfn[y]) swap(x,y);
        return Qry(odfn[x],idfn[y],z,id,id);
    }
 
    int query()
    {
        int tmp=BB-1;
        while(!bcntcnt[tmp]) tmp--;
        int ans=BB*(tmp+1);
        while(!cntcnt[ans]) ans--;
        return ans;
    }
 
    void update(int c,int v){if(!c) return;cntcnt[c]+=v;bcntcnt[c/BB]+=v;}
    void ins(int c){update(cnt[c],-1);cnt[c]++;update(cnt[c],1);}
    void del(int c){update(cnt[c],-1);cnt[c]--;update(cnt[c],1);}
    void gao(int x){inq[x]?del(col[x]):ins(col[x]);inq[x]^=1;}
 
    void doit(int t)
    {
        if(!ch[t].x) return;
        if(inq[ch[t].x]) del(ch[t].pre);
        if(inq[ch[t].x]) ins(ch[t].c);
        col[ch[t].x]=ch[t].c;
    }
    void undo(int t)
    {
        if(!ch[t].x) return;
        if(inq[ch[t].x]) del(ch[t].c);
        if(inq[ch[t].x]) ins(ch[t].pre);
        col[ch[t].x]=ch[t].pre;
    }
 
    void main()
    {
        dfs(1,0);
        for(int i=1;i<=m;i++)
        {
            if(opt[i].opt==1) ch[i]={opt[i].x,opt[i].y};
            if(opt[i].opt==3) qry[++q]=addq(opt[i].x,opt[i].y,i);
        }
        for(int i=1;i<=m;i++)
            if(ch[i].x) ch[i].pre=a[ch[i].x],a[ch[i].x]=ch[i].c;
        sort(qry+1,qry+1+q);
        int pl=1,pr=0,pt=0;
        for(int i=1;i<=q;i++)
        {
            while(pr<qry[i].r) gao(idx[++pr]);
            while(pr>qry[i].r) gao(idx[pr--]);
            while(pl>qry[i].l) gao(idx[--pl]);
            while(pl<qry[i].l) gao(idx[pl++]);
            while(pt<qry[i].t) doit(++pt);
            while(pt>qry[i].t) undo(pt--);
            if(qry[i].x) gao(qry[i].x);
            ans[qry[i].id]=query();
            if(qry[i].x) gao(qry[i].x);
        }
    }
}
 
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",col+i),cc[i]=Task2::a[i]=col[i];
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for(int i=1,op,x,y;i<=m;i++)
        scanf("%d%d%d",&op,&x,&y),opt[i]={op,x,y};
    Task1::main();
    memcpy(col,cc,sizeof(col));
    Task2::main();
    for(int i=1;i<=m;i++)
        if(opt[i].opt>=2) printf("%d\n",ans[i]);
    return 0;
}