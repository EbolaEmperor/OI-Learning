#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=1010;

struct Point
{
    LL x,y;double ang;
    Point(LL _x=0,LL _y=0):x(_x),y(_y){}
    void init(){ang=atan2(y,x);}
    Point operator - (const Point &a){return Point(x-a.x,y-a.y);}
    double operator * (const Point &a){return 1.0*x*a.y-1.0*y*a.x;}
    bool operator < (const Point &a) const{return ang<a.ang;}
} p[N],pp[N];
LL ans=0,x=0,y=0,n;

int nxt(int x){if(++x==n) x=1;return x;}
void gao()
{
    for(int i=1;i<n;i++) pp[i]=p[i]-p[n],pp[i].init();
    sort(pp+1,pp+n);
    for(int i=1,q=1,cnt=0;i<n;i++,cnt--)
    {
        if(cnt<0) cnt=0,q=i;
        while(nxt(q)!=i&&pp[i]*pp[nxt(q)]>=0) q=nxt(q),cnt++;
        x+=1ll*cnt*(n-cnt-2);
        y+=1ll*cnt*(cnt-1)/2+(n-cnt-2)*(n-cnt-3)/2;
    }
}

int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;i++) scanf("%lld%lld",&p[i].x,&p[i].y);
    for(int i=1;i<=n;i++) swap(p[i],p[n]),gao(),swap(p[i],p[n]);
    ans=4ll*(y-x)/2+4ll*n*(n-1)*(n-2);
    printf("%lld\n",ans);
    return 0;
}