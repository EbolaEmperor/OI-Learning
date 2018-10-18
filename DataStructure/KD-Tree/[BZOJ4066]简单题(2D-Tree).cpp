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
inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}

int falun;
struct Point
{
    int d[2],v;
    Point(int x=0,int y=0,int z=0){d[0]=x;d[1]=y;v=z;}
    int& operator [] (const int &x){return d[x];}
    bool operator == (Point &a){return d[0]==a[0]&&d[1]==a[1];}
    bool operator < (const Point &a) const{return d[falun]<a.d[falun];}
};
struct Rectangle
{
    Point ll,ur;
    Rectangle(int x1=0,int y1=0,int x2=0,int y2=0){ll=Point(x1,y1);ur=Point(x2,y2);}
    bool in (Rectangle &a){return a.ll[0]>=ll[0]&&a.ll[1]>=ll[1]&&a.ur[0]<=ur[0]&&a.ur[1]<=ur[1];}
    bool out (Rectangle &a){return a.ur[0]<ll[0]||a.ur[1]<ll[1]||a.ll[0]>ur[0]||a.ll[1]>ur[1];}
    bool in (Point &a){return a[0]>=ll[0]&&a[0]<=ur[0]&&a[1]>=ll[1]&&a[1]<=ur[1];}
};

const int N=200010;
int lc[N],rc[N],rt=0,tot=0;
Rectangle rec[N];
Point pt[N];
int sum[N];

inline void maintain(int o)
{
    rec[o].ll=rec[o].ur=pt[o];
    for(int i=0;i<2;i++)
    {
        if(!lc[o]) goto uprc;
        upmin(rec[o].ll[i],rec[lc[o]].ll[i]);
        upmax(rec[o].ur[i],rec[lc[o]].ur[i]);
        uprc: if(!rc[o]) continue;
        upmin(rec[o].ll[i],rec[rc[o]].ll[i]);
        upmax(rec[o].ur[i],rec[rc[o]].ur[i]);
    }
    sum[o]=pt[o].v;
    if(lc[o]) sum[o]+=sum[lc[o]];
    if(rc[o]) sum[o]+=sum[rc[o]];
}

void insert(int &o,Point &p,int d)
{
    if(!o)
    {
        o=++tot;
        rec[o].ll=rec[o].ur=p;
        pt[o]=p;sum[o]=p.v;
        return;
    }
    sum[o]+=p.v;
    if(pt[o]==p){pt[o].v+=p.v;return;}
    else if(p[d]<pt[o][d]) insert(lc[o],p,d^1);
    else insert(rc[o],p,d^1);
    maintain(o);
}

int rebuild(int l,int r,int d)
{
    if(l>r) return 0;
    int mid=(l+r)/2;falun=d;
    nth_element(pt+l,pt+mid,pt+r+1);
    lc[mid]=rebuild(l,mid-1,d^1);
    rc[mid]=rebuild(mid+1,r,d^1);
    maintain(mid);
    return mid;
}

int query(int o,Rectangle &q)
{
    int res=0;
    if(q.in(rec[o])) return sum[o];
    if(q.out(rec[o])) return 0;
    if(q.in(pt[o])) res+=pt[o].v;
    if(lc[o]) res+=query(lc[o],q);
    if(rc[o]) res+=query(rc[o],q);
    return res;
}

int main()
{
    int n=read(),lastans=0,cnt=0,R=5000;
    while(1)
    {
        int opt=read();
        if(opt==3) break;
        int x1=read()^lastans;
        int y1=read()^lastans;
        if(opt==1)
        {
            int A=read()^lastans;
            Point tmp(x1,y1,A);
            insert(rt,tmp,0);
            if(++cnt==R) rt=rebuild(1,tot,0),R+=5000;
        }
        if(opt==2)
        {
            int x2=read()^lastans;
            int y2=read()^lastans;
            Rectangle tmp(x1,y1,x2,y2);
            lastans=query(rt,tmp);
            print(lastans);
        }
    }
    flush();
    return 0;
}