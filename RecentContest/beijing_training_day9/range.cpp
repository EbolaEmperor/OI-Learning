#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010,INF=0x3f3f3f3f;
struct Tree{int mn[2],mx[2],p[2],exist,lc,rc,fa;} tr[N];
struct Node{int p[2],id;} pt[N];
struct Qry{int opt,x,y;} q[N];
int m,n=0,tot=0,rt,idx[N];

inline bool cmp0(const Node &a,const Node &b){return a.p[0]<b.p[0];}
inline bool cmp1(const Node &a,const Node &b){return a.p[1]<b.p[1];}

void update(int o)
{
    tr[o].mn[0]=min(tr[tr[o].lc].mn[0],tr[tr[o].rc].mn[0]);
    tr[o].mn[1]=min(tr[tr[o].lc].mn[1],tr[tr[o].rc].mn[1]);
    tr[o].mx[0]=max(tr[tr[o].lc].mx[0],tr[tr[o].rc].mx[0]);
    tr[o].mx[1]=max(tr[tr[o].lc].mx[1],tr[tr[o].rc].mx[1]);
    if(tr[o].exist)
    {
        tr[o].mn[0]=min(tr[o].mn[0],tr[o].p[0]);
        tr[o].mn[1]=min(tr[o].mn[1],tr[o].p[1]);
        tr[o].mx[0]=max(tr[o].mx[0],tr[o].p[0]);
        tr[o].mx[1]=max(tr[o].mx[1],tr[o].p[1]);
    }
}

void build(int &o,int l,int r,int d)
{
    int mid=(l+r)/2;
    nth_element(pt+l,pt+mid,pt+r+1,d?cmp0:cmp1);
    tr[o=++tot]={ {INF,INF},{0,0},{pt[mid].p[0],pt[mid].p[1]},0,0,0,0};
    idx[pt[mid].id]=tot;
    if(l==r) return;
    if(l<mid) build(tr[o].lc,l,mid-1,d^1),tr[tr[o].lc].fa=o;
    if(r>mid) build(tr[o].rc,mid+1,r,d^1),tr[tr[o].rc].fa=o;
}

void insert(int o){tr[o].exist++;while(o) update(o),o=tr[o].fa;}
void remove(int o){tr[o].exist--;while(o) update(o),o=tr[o].fa;}

LL calc(int o,const Qry &q)
{
    if(tr[o].mn[0]>q.x||tr[o].mx[1]<q.y) return -1;
    return (LL)(q.x-tr[o].mn[0])*(tr[o].mx[1]-q.y);
}

LL query(int o,const Qry &q)
{
    if(!o||calc(o,q)==-1) return -1;
    LL tmp1=calc(tr[o].lc,q),tmp2=calc(tr[o].rc,q);
    LL ans=(tr[o].exist&&q.x>=tr[o].p[0]&&q.y<=tr[o].p[1])?(LL)(q.x-tr[o].p[0])*(tr[o].p[1]-q.y):-1;
    if(tmp1>tmp2)
    {
        if(tmp1>ans) ans=max(ans,query(tr[o].lc,q));
        if(tmp2>ans) ans=max(ans,query(tr[o].rc,q));
        return ans;
    }
    else
    {
        if(tmp2>ans) ans=max(ans,query(tr[o].rc,q));
        if(tmp1>ans) ans=max(ans,query(tr[o].lc,q));
        return ans;
    }
}

int main()
{
    tr[0].mn[0]=tr[0].mn[1]=INF;
    tr[0].mx[0]=tr[0].mx[1]=0;
    scanf("%d",&m);
    for(int i=1;i<=m;i++)
    {
        int opt,x,y;
        scanf("%d",&opt);
        if(opt==1)
        {
            scanf("%d%d",&x,&y);
            n++;pt[n]={ {x,y},n};
            q[i]={opt,n};
        }
        if(opt==2) scanf("%d",&x),q[i]={opt,x};
        if(opt==3) scanf("%d%d",&x,&y),q[i]={opt,x,y};
    }
    build(rt,1,n,0);
    for(int i=1;i<=m;i++)
    {
        if(q[i].opt==1) insert(idx[q[i].x]);
        if(q[i].opt==2) remove(idx[q[i].x]);
        if(q[i].opt==3) printf("%lld\n",query(rt,q[i]));
    }
    return 0;
}
