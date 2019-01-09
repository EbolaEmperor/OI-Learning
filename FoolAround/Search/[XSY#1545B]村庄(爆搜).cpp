#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const LL INF=1ll<<60;
const int N=210,M=40010;
struct Info
{
    LL l,r;
    Info(LL _l=INF,LL _r=-INF):l(_l),r(_r){}
    Info operator + (const Info &a){return Info(min(l,a.l),max(r,a.r));}
    Info operator + (const LL &x){return Info(l+x,r+x);}
    bool in(int x){return x>l&&x<r;}
};
struct{int x,y;} p[N];
LL cnt[M],sum[M],val[M],tot;
map<LL,LL> space;
int n,m,cc=0;

Info gao(int xl,int xr,int yl,int yr,LL v0,LL k)
{
    LL area=(LL)(xr-xl)*(yr-yl);
    bool inside=0,hor=0,ver=0,corner=0;
    Info sx(xl,xr),sy(yl,yr),a,b;
    for(int i=1;i<=m;i++)
    {
        int j=(i<m)?(i+1):1;
        if(sx.in(p[i].x)&&sy.in(p[i].y)) corner=1;
        if(p[i].x==p[j].x&&sx.in(p[i].x)&&max(yl,min(p[i].y,p[j].y))<min(yr,max(p[i].y,p[j].y))) ver=1;
        if(p[i].y==p[j].y&&sy.in(p[i].y)&&max(xl,min(p[i].x,p[j].x))<min(xr,max(p[i].x,p[j].x))) hor=1;
        Info vy(min(p[i].y,p[j].y),max(p[i].y,p[j].y));
        if(p[i].x<=xl&&vy.l<=yl&&vy.r>yl) inside^=1;
    }
    if(!(corner||hor||ver)) return inside?Info(v0,v0+area-1):Info();
    if(xr-xl==yr-yl)
    {
        if(!corner&&hor) a=gao(xl,(xl+xr)/2,yl,yr,v0,k<<1),b=a+area/2;
        else a=gao(xl,(xl+xr)/2,yl,yr,v0,k),b=gao((xl+xr)/2,xr,yl,yr,v0+area/2,k);
    }
    else
    {
        if(!corner&&ver) a=gao(xl,xr,yl,(yl+yr)/2,v0,k<<1),b=a+area/2;
        else a=gao(xl,xr,yl,(yl+yr)/2,v0,k),b=gao(xl,xr,(yl+yr)/2,yr,v0+area/2,k);
    }
    if(a.r!=-INF&&b.l!=INF&&b.l-a.r>1)
        space[b.l-a.r-1]+=k;
    return a+b;
}

void prework()
{
    for(auto it=space.rbegin();it!=space.rend();it++)
    {
        val[++cc]=it->first;
        cnt[cc]=cnt[cc-1]+it->second;
        sum[cc]=sum[cc-1]+it->first*it->second;
    }
}

LL query(LL t)
{
    t=min(t-1,cnt[cc]);
    int k=upper_bound(cnt+1,cnt+1+cc,t)-cnt-1;
    LL ans=sum[k]+val[k+1]*(t-cnt[k]);
    return tot-ans;
}

int main(int argc,char* argv[])
{
    if(argc>1) freopen(argv[1],"r",stdin);
    if(argc>2) freopen(argv[2],"w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",&p[i].x,&p[i].y);
    Info tmp=gao(0,1<<n,0,1<<n,0,1);
    tot=tmp.r-tmp.l+1;
    prework();
    int q,t;
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d",&t);
        printf("%lld\n",query(t));
    }
    return 0;
}