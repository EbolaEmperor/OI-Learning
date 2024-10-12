#include<bits/stdc++.h>
using namespace std;

typedef long double LD;
typedef pair<int,int> pii;
const int N=100010;
const LD eps=1e-11,eeps=1e-13;
int n,m,a,b,c,st,ed,tot=0,ptot,mx,my;
int kt[N],rnk[N];  //kt[i]:第i个终点对应的航线； rnk[i]:第i个航线对应的终点 
LD hx[N*10],hy[N*10];
struct Seg{int yl,yr;} l[N];

struct Point
{
    LD x,y;int d;
    Point(LD _x=0,LD _y=0,int _d=0):x(_x),y(_y),d(_d){}
    void rotate(){LD tx=x,ty=y;x=(tx-ty);y=(tx+ty);}
} p[N*10];

struct Opt
{
    int x,y,d;
    bool operator < (const Opt &b){return x<b.x||x==b.x&&y<b.y||x==b.x&&y==b.y&&d>b.d;}
} opt[N*10];

inline bool dcmp(const LD &a,const LD &b){return fabs(a-b)<eeps;}

Point intersec(LD yl1,LD yr1,LD yl2,LD yr2)
{
    LD a=(yl1-yl2)*(ed-st)/(yr2-yr1+yl1-yl2);
    LD h=a/(ed-st)*(yr2-yl2);
    return Point(st+a,yl2+h,0);
}

void get_intersection()
{
    set<pii> s;
    for(int i=1;i<=n;i++)
    {
        for(auto it=s.upper_bound(pii(l[i].yr,0));it!=s.end();it++)
            p[++tot]=intersec(l[i].yl,l[i].yr,it->second,it->first);
        s.insert(pii(l[i].yr,l[i].yl));
    }
    for(int i=1;i<=tot;i++) p[i].rotate();
}

int bit[N*10];
inline int lowbit(const int &x){return x&-x;}
void add(int p,int k){for(;p<=my;p+=lowbit(p)) bit[p]+=k;}
int sum(int p){int res=0;for(;p;p-=lowbit(p)) res+=bit[p];return res;}

int main()
{
    scanf("%d%d%d%d%d%d",&n,&a,&b,&c,&st,&ed);
    for(int i=1;i<=n;i++) scanf("%d",&l[i].yl);
    for(int i=1;i<=n;i++) scanf("%d",&l[i].yr);
    for(int i=1;i<=n;i++) kt[i]=i;
    sort(kt+1,kt+1+n,[](int a,int b){return l[a].yr<l[b].yr;});
    for(int i=1;i<=n;i++) rnk[kt[i]]=i;
    get_intersection();ptot=tot;
    scanf("%d",&m);
    for(int i=1,x,y,r;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&r);
        p[++tot]=Point(x-r,y,1);
        p[tot].rotate();
        p[++tot]=Point(x,y+r,-1);
        p[tot].rotate();
        p[tot].y+=eps;
        p[++tot]=Point(x,y-r,-1);
        p[tot].rotate();
        p[tot].x+=eps;
        p[++tot]=Point(x+r,y,1);
        p[tot].rotate();
        p[tot].y+=eps;
        p[tot].x+=eps;
    }
    for(int i=1;i<=tot;i++)
        hx[i]=p[i].x,hy[i]=p[i].y;
    sort(hx+1,hx+1+tot);
    sort(hy+1,hy+1+tot);
    mx=unique(hx+1,hx+1+tot,dcmp)-(hx+1);
    my=unique(hy+1,hy+1+tot,dcmp)-(hy+1);
    for(int i=1;i<=tot;i++)
    {
        opt[i].x=lower_bound(hx+1,hx+1+mx,p[i].x-eeps)-hx;
        opt[i].y=lower_bound(hy+1,hy+1+my,p[i].y-eeps)-hy;
        opt[i].d=p[i].d;
    }
    sort(opt+1,opt+1+tot);
    int ans=0;
    for(int i=1;i<=tot;i++)
    {
        if(opt[i].d) add(opt[i].y,opt[i].d);
        else if(sum(opt[i].y)) ans+=c;
    }
    int t1=ans+ptot*a,t2=ans+ptot*b;
    for(int i=1;i<=n;i++)
    {
        int p=rnk[i],q=kt[i];
        if(p!=i)
        {
            rnk[q]=p,kt[p]=q;
            rnk[i]=i,kt[i]=i;
            t2+=a-b;
        }
    }
    printf("%d %d\n",min(t1,t2),max(t1,t2));
    return 0;
}
