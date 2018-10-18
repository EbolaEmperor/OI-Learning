#include<bits/stdc++.h>
#define MP make_pair
#define FR first
#define SE second
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

typedef pair<int,int> pii;
typedef long long LL;
const int N=100010;
struct Point
{
    int x,y;
    Point(int _x=0,int _y=0):x(_x),y(_y){}
    Point rotate(){return Point(x+y,y-x);}
    bool operator != (Point b){return x!=b.x||y!=b.y;}
} org[N],rtg[N],prg[N];
set<pii> sx[N],sy[N];
vector<pii> vx[N],vy[N];
queue<int> q;
bool vis[N];
int Hx[N],Hy[N],mx,my;
int n,A,B,d;
LL ans=0;

void prework()
{
    sort(Hx+1,Hx+1+n);sort(Hy+1,Hy+1+n);
    mx=unique(Hx+1,Hx+1+n)-(Hx+1);
    my=unique(Hy+1,Hy+1+n)-(Hy+1);
    for(int i=1;i<=n;i++)
    {
        prg[i].x=lower_bound(Hx+1,Hx+1+mx,rtg[i].x)-Hx;
        prg[i].y=lower_bound(Hy+1,Hy+1+my,rtg[i].y)-Hy;
        sx[prg[i].x].insert(MP(rtg[i].y,i));
        sy[prg[i].y].insert(MP(rtg[i].x,i));
        vx[prg[i].x].push_back(MP(rtg[i].y,i));
        vy[prg[i].y].push_back(MP(rtg[i].x,i));
    }
    for(int i=1;i<=mx;i++) sort(vx[i].begin(),vx[i].end());
    for(int i=1;i<=my;i++) sort(vy[i].begin(),vy[i].end());
}

pii gao(set<pii> &s,vector<pii> &v,int l,int r)
{
    ans+=upper_bound(v.begin(),v.end(),MP(r,n))-lower_bound(v.begin(),v.end(),MP(l,0));
    auto pl=s.lower_bound(MP(l,0)),pr=s.upper_bound(MP(r,n));
    for(auto it=pl;it!=pr;)
    {
        if(!vis[it->SE])
        {
            vis[it->SE]=1;
            q.push(it->SE);
        }
        auto it2=it;it2++;
        s.erase(it);it=it2;
    }
    auto ppl=lower_bound(v.begin(),v.end(),MP(l,0));
    auto ppr=lower_bound(v.begin(),v.end(),MP(r,0));
    return MP(ppl==v.end()?0:ppl->SE,ppr==v.end()?0:ppr->SE);
}

void BFS()
{
    vis[A]=1;q.push(A);
    while(!q.empty())
    {
        int u=q.front();q.pop();
        pii p1(0,0),p2(0,0),p3(0,0),p4(0,0);
        Point pt=org[u];
        Point pt1=Point(pt.x+d,pt.y).rotate();
        Point pt2=Point(pt.x,pt.y+d).rotate();
        Point pt3=Point(pt.x-d,pt.y).rotate();
        Point pt4=Point(pt.x,pt.y-d).rotate();
        int p=lower_bound(Hx+1,Hx+1+mx,pt1.x)-Hx;
        if(Hx[p]==pt1.x) p1=gao(sx[p],vx[p],pt1.y,pt2.y);
        p=lower_bound(Hx+1,Hx+1+mx,pt3.x)-Hx;
        if(Hx[p]==pt3.x) p2=gao(sx[p],vx[p],pt4.y,pt3.y);
        p=lower_bound(Hy+1,Hy+1+my,pt2.y)-Hy;
        if(Hy[p]==pt2.y) p3=gao(sy[p],vy[p],pt3.x,pt2.x);
        p=lower_bound(Hy+1,Hy+1+my,pt1.y)-Hy;
        if(Hy[p]==pt1.y) p4=gao(sy[p],vy[p],pt4.x,pt1.x);
        if(p1.SE&&p3.SE&&p1.SE==p3.SE) ans--;
        if(p2.SE&&p3.FR&&p2.SE==p3.FR) ans--;
        if(p2.FR&&p4.FR&&p2.FR==p4.FR) ans--;
        if(p4.SE&&p1.FR&&p4.SE==p1.FR) ans--;
    }
}

int main()
{
    n=read();A=read();B=read();
    for(int i=1;i<=n;i++)
    {
        org[i].x=read();
        org[i].y=read();
        rtg[i]=org[i].rotate();
        Hx[i]=rtg[i].x;
        Hy[i]=rtg[i].y;
    }
    d=abs(org[A].x-org[B].x)+abs(org[A].y-org[B].y);
    prework();BFS();
    printf("%lld\n",ans/2);
    return 0;
}