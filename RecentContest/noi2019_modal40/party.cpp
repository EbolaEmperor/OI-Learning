#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
LL ans=0;
int n;

struct Party
{
    int l,r,v;
    void init(){scanf("%d%d%d",&l,&r,&v);}
    bool operator < (const Party &b) const{return l>b.l;}
} a[N],b[N];

struct Line
{
    LL k,b;
    Line(LL _k=0,LL _b=0):k(_k),b(_b){}
    LL operator () (const int &x){return k*x+b;}
};

inline int lowbit(const int &x){return x&-x;}
inline void upmax(LL &x,const LL &y){if(y>x) x=y;}

namespace BIT
{
    LL val[N];
    void clear(){memset(val,0,sizeof(val));}
    void update(int p,LL x){for(;p<=n;p+=lowbit(p)) upmax(val[p],x);}
    int qmax(int p){LL res=0;for(;p;p-=lowbit(p)) upmax(res,val[p]);return res;}
}

namespace Segment
{
    Line line[N*20];
    int lc[N*20],rc[N*20],rt[N],tot=0;
    void clear()
    {
        tot=0;
        memset(rt,0,sizeof(rt));
        memset(lc,0,sizeof(lc));
        memset(rc,0,sizeof(rc));
        memset(line,0,sizeof(line));
    }
    void insert(int &o,int l,int r,Line t)
    {
        if(!o){line[o=++tot]=t;return;}
        int mid=(l+r)/2;
        if(line[o](mid)<t(mid)) swap(t,line[o]);
        if(l==r) return;
        if(line[o](l)<t(l)) insert(lc[o],l,mid,t);
        if(line[o](r)<t(r)) insert(rc[o],mid+1,r,t);
    }
    LL qmax(int o,int l,int r,int x)
    {
        if(!o) return 0;
        LL res=line[o](x);
        if(l==r) return res;
        int mid=(l+r)/2;
        if(x<=mid) upmax(res,qmax(lc[o],l,mid,x));
        else upmax(res,qmax(rc[o],mid+1,r,x));
        return res;
    }
    void insert(int a,Line b)
    {
        for(;a;a-=lowbit(a))
            insert(rt[a],0,N,b);
    }
    LL qmax(int a,int x)
    {
        LL res=0;
        for(;a<=N;a+=lowbit(a))
            res=max(res,qmax(rt[a],0,N,x));
        return res;
    }
}

void gao(Party *a,Party *b)
{
    int j=1;
    BIT::clear();
    Segment::clear();
    for(int i=1;i<=n;i++)
    {
        for(;j<=n&&b[j].l>=a[i].l;j++)
        {
            BIT::update(b[j].r,(LL)(b[j].r-b[j].l+1)*b[j].v);
            Segment::insert(b[j].r,Line(b[j].v,(LL)b[j].v*(1-b[j].l)));
        }
        ans=max(ans,(LL)a[i].v*BIT::qmax(a[i].r));
        ans=max(ans,(LL)a[i].v*Segment::qmax(a[i].r,a[i].r));
    }
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) a[i].init();
    for(int i=1;i<=n;i++) b[i].init();
    sort(a+1,a+1+n);sort(b+1,b+1+n);
    gao(a,b);gao(b,a);
    printf("%lld\n",ans);
    return 0;
}