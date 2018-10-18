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
const int N=100010;
int falun,n,m;
struct Point
{
    int d[2],id;
    Point(int x=0,int y=0,int w=0){d[0]=x;d[1]=y;id=w;}
    int& operator [] (const int &x){return d[x];}
    bool operator < (const Point &p) const{return d[falun]<p.d[falun];}
} pt[N],org[N],qry;
int lc[N],rc[N],idx[N],tot=0,rt=0;
int d[N][2],mn[N][2],mx[N][2],mnd[N];

inline LL sqr(const int &x){return 1ll*x*x;}
inline LL dist(const int &x){return sqr(org[x][0]-qry[0])+sqr(org[x][1]-qry[1]);}
inline LL disq(const int &x){return x?dist(x):-1;}
inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}
inline LL dist(int x,Point &p)
{
    LL res=0;
    for(int i=0;i<2;i++)
        res+=sqr(max(mx[x][i]-p[i],p[i]-mn[x][i]));
    return res;
}

inline int newnode(Point &p)
{
    idx[++tot]=p.id;mnd[tot]=p.id;
    d[tot][0]=mn[tot][0]=mx[tot][0]=p[0];
    d[tot][1]=mn[tot][1]=mx[tot][1]=p[1];
    return tot;
}

void maintain(int o)
{
    for(int i=0;i<2;i++)
    {
        if(!lc[o]) goto uprc;
        upmin(mn[o][i],mn[lc[o]][i]);
        upmax(mx[o][i],mx[lc[o]][i]);
        upmin(mnd[o],mnd[lc[o]]);
        uprc: if(!rc[o]) continue;
        upmin(mn[o][i],mn[rc[o]][i]);
        upmax(mx[o][i],mx[rc[o]][i]);
        upmax(mnd[o],mnd[rc[o]]);
    }
}

void build(int &o,int l,int r,int D)
{
    int mid=(l+r)/2;falun=D;
    nth_element(pt+l,pt+mid,pt+r+1);
    o=newnode(pt[mid]);
    if(l<mid) build(lc[o],l,mid-1,D^1);
    if(r>mid) build(rc[o],mid+1,r,D^1);
    maintain(o);
}

struct cmp
{
    bool operator () (const int &a,const int &b)
    {
        LL disa=disq(a),disb=disq(b);
        if(disa==disb) return a<b;
        else return disa>disb;
    }
};
priority_queue<int,vector<int>,cmp> ans;

void find(int o)
{
    if(!o) return;
    if(cmp()(idx[o],ans.top()))
        ans.pop(),ans.push(idx[o]);
    LL dl=dist(lc[o],qry),dr=dist(rc[o],qry);
    if(dl>dr)
    {
        LL tmp=disq(ans.top());
        if(dl>tmp||dl==tmp&&mnd[lc[o]]<ans.top()) find(lc[o]);
        tmp=disq(ans.top());
        if(dr>tmp||dr==tmp&&mnd[rc[o]]<ans.top()) find(rc[o]);
    }
    else
    {
        LL tmp=disq(ans.top());
        if(dr>tmp||dr==tmp&&mnd[rc[o]]<ans.top()) find(rc[o]);
        tmp=disq(ans.top());
        if(dl>tmp||dl==tmp&&mnd[lc[o]]<ans.top()) find(lc[o]);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        pt[i][0]=read();
        pt[i][1]=read();
        pt[i].id=i;
        org[i]=pt[i];
    }
    build(rt,1,n,0);
    for(m=read();m;m--)
    {
        int x=read(),y=read(),k=read();
        while(!ans.empty()) ans.pop();
        qry=Point(x,y);
        while(k--) ans.push(0);
        find(rt);printf("%d\n",ans.top());
    }
    return 0;
}