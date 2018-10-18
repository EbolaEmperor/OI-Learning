#include<bits/stdc++.h>
using namespace std;

typedef double DB;
const int N=150010;
const DB epsF=1e-9;
const DB eps=1e-5;

DB a,b,lastans=0.1;
int falun,n,m,ans;
struct Point
{
    DB d[3],r;int id;
    DB& operator [] (const int &x){return d[x];}
    Point(DB x=0.0,DB y=0.0,DB z=0.0,int w=0){d[0]=x;d[1]=y;d[2]=z;id=w;}
    bool operator < (const Point &b) const{return d[falun]<b.d[falun];}
} pt[N];
DB d[N][3],mn[N][3],mx[N][3];
int idx[N],pos[N],rt=0;
int lc[N],rc[N],tot=0;

inline DB sqr(const DB &x){return x*x;}
inline DB dist(int o,Point &p){DB res=0;for(int i=0;i<3;i++)res+=sqr(d[o][i]-p[i]);return res;}
inline DB dis1(int o,Point &p){DB res=0;for(int i=0;i<3;i++)res+=sqr(max(0.0,max(p[i]-mx[o][i],mn[o][i]-p[i])));return res;}
inline DB dis2(int o,Point &p){DB res=0;for(int i=0;i<3;i++)res+=sqr(max(mx[o][i]-p[i],p[i]-mn[o][i]));return res;}

int newnode(Point &p)
{
    idx[++tot]=p.id;
    pos[p.id]=tot;
    for(int i=0;i<3;i++)
        d[tot][i]=mn[tot][i]=mx[tot][i]=p[i];
    return tot;
}

void maintain(int o,int y)
{
    if(!y) return;
    for(int i=0;i<3;i++)
    {
        mn[o][i]=min(mn[o][i],mn[y][i]);
        mx[o][i]=max(mx[o][i],mx[y][i]);
    }
}

void build(int &o,int l,int r,int D)
{
    int mid=(l+r)/2;falun=D;
    nth_element(pt+l,pt+mid,pt+r+1);
    o=newnode(pt[mid]);
    if(l<mid) build(lc[o],l,mid-1,(D+1)%3),maintain(o,lc[o]);
    if(r>mid) build(rc[o],mid+1,r,(D+1)%3),maintain(o,rc[o]);
}

void insert(int &o,Point &p,int D)
{
    if(!o){o=newnode(p);return;}
    if(p[D]<d[o][D]) insert(lc[o],p,(D+1)%3),maintain(o,lc[o]);
    else insert(rc[o],p,(D+1)%3),maintain(o,rc[o]);
}

void remove(int id)
{
    int o=pos[id];idx[o]=0;
    for(int i=0;i<3;i++) mn[o][i]=1e4;
    for(int i=0;i<3;i++) mx[o][i]=-1e4;
    maintain(o,lc[o]);maintain(o,rc[o]);
}

void find(int o,Point &crl)
{
    if(!o||ans) return;
    if(idx[o]&&fabs(dist(o,crl)-crl.r)<eps){ans=idx[o];return;}
    DB dl1=dis1(lc[o],crl),dr1=dis1(rc[o],crl);
    DB dl2=dis2(lc[o],crl),dr2=dis2(rc[o],crl);
    if(dl2<dr2)
    {
        if(dl1<crl.r+eps&&dl2>crl.r-eps) find(lc[o],crl);
        if(dr1<crl.r+eps&&dr2>crl.r-eps) find(rc[o],crl);
    }
    else
    {
        if(dr1<crl.r+eps&&dr2>crl.r-eps) find(rc[o],crl);
        if(dl1<crl.r+eps&&dl2>crl.r-eps) find(lc[o],crl);
    }
}

inline DB F(DB x){x=x*lastans+1.0L;return a*x-b*sin(x);}
DB decrypt(DB f,DB l,DB r)
{
    while(r-l>epsF)
    {
        DB mid=(l+r)/2.0;
        if(F(mid)<f) l=mid;
        else r=mid;
    }
    return (l+r)/2.0;
}

int main()
{
    DB x,y,z,r;int opt,id;
    scanf("%d%d%lf%lf",&n,&m,&a,&b);
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf%lf",&x,&y,&z);
        pt[i]=Point(x,y,z,i);
    }
    build(rt,1,n,0);
    while(m--)
    {
        scanf("%d",&opt);
        if(opt==0)
        {
            scanf("%lf%lf%lf%lf",&r,&x,&y,&z);
            x=decrypt(x,-100,100);
            y=decrypt(y,-100,100);
            z=decrypt(z,-100,100);
            id=(int)round(decrypt(r,0,n));
            remove(id);
            Point tmp(x,y,z,id);
            insert(rt,tmp,0);
        }
        if(opt==1)
        {
            scanf("%lf%lf%lf%lf",&x,&y,&z,&r);
            x=decrypt(x,-100,100);
            y=decrypt(y,-100,100);
            z=decrypt(z,-100,100);
            r=decrypt(r,-800,800);
            Point tmp(x,y,z);tmp.r=sqr(r);
            ans=0;find(rt,tmp);
            printf("%d\n",ans);
            lastans=ans;
        }
    }
    return 0;
}