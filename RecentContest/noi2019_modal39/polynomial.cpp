#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010;
struct Point
{
    int x,y;bool del;
    Point(int _x=0,int _y=0):x(_x),y(_y),del(0){}
    Point operator - (const Point &b){return Point(x-b.x,y-b.y);}
    LL operator * (const Point &b) const{return (LL)x*b.y-(LL)y*b.x;}
    bool operator < (const Point &b) const{return x<b.x||x==b.x&&y<b.y;}
} p[N];
int n,m,ch[N];

int convex_hull()
{
    int m=0;
    for(int i=1;i<=n;i++)
    {
        if(p[i].del) continue;
        while(m>1&&(p[ch[m-1]]-p[ch[m-2]])*(p[i]-p[ch[m-2]])<=0) m--;
        ch[m++]=i;
    }
    int k=m;
    for(int i=n-1;i>0;i--)
    {
        if(p[i].del) continue;
        while(m>k&&(p[ch[m-1]]-p[ch[m-2]])*(p[i]-p[ch[m-2]])<=0) m--;
        ch[m++]=i;
    }
    return m>1?m-1:m;
}

bool gao()
{
    static int gg[N];
    memcpy(gg,ch,sizeof(gg));
    for(int i=0;i<m;i++) if((p[ch[i]].x|p[ch[i]].y)&1) return 1;
    for(int i=1;i<m;i++) p[gg[i]].del=(i&1);
    int mm=convex_hull();
    for(int i=0;i<mm;i++) if((p[ch[i]].x|p[ch[i]].y)&1) return 1;
    for(int i=1;i<m;i++) p[gg[i]].del=!(i&1);
    mm=convex_hull();
    for(int i=0;i<mm;i++) if((p[ch[i]].x|p[ch[i]].y)&1) return 1;
    return 0;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&p[i].x,&p[i].y);
    p[++n]=Point(0,0);
    sort(p+1,p+1+n);
    m=convex_hull();
    puts(gao()?"Alice":"Bob");
    return 0;
}