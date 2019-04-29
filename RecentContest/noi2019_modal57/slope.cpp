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
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

typedef long long LL;
const LL INF=(1ll<<60);
template<class I,class T>inline void upmin(I &x,const T &y){if(y<x) x=y;}
template<class I,class T>inline void upmax(I &x,const T &y){if(y>x) x=y;}
inline LL sqr(int x){return 1ll*x*x;}
inline LL dis(int x1,int y1,int x2,int y2){return sqr(x1-x2)+sqr(y1-y2);}

const int N=100010;
int falun,n;
struct Point
{
    int d[2],id;
    Point(int x=0,int y=0,int z=0){d[0]=x;d[1]=y;id=z;}
    int& operator [] (const int &x){return x<2?d[x]:id;}
    bool operator < (const Point &a) const{return d[falun]<a.d[falun];}
} pt[N];
int now;
LL dist;

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
    LL disp(Point &p)
    {
        LL d1=0,d2=0;
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
        if(id!=now) dist=min(dist,dis(d[0],d[1],p[0],p[1]));
        if(lc==nullptr&&rc==nullptr) return;
        if(lc==nullptr){rc->find(p);return;}
        if(rc==nullptr){lc->find(p);return;}
        LL dl=lc->disp(p),dr=rc->disp(p);
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
    root=new KD_Tree;
    n=read();
    for(int i=1;i<=n;i++)
    {
        pt[i][0]=i;
        pt[i][1]=pt[i-1][1]+read();
        pt[i][2]=i;
    }
    root->build(1,n);
    LL mn=INT64_MAX;
    for(int i=1;i<=n;i++)
    {
        dist=INF;now=pt[i].id;
        root->find(pt[i]);
        mn=min(mn,dist);
    }
    cout<<mn<<endl;
    return 0;
}