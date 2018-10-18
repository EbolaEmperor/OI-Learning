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
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=300010;
struct Point
{
    int x,y;
    Point(int _x=0,int _y=0):x(_x),y(_y){}
    bool operator < (Point a) const{return x<a.x||x==a.x&&y<a.y;}
} a[N];
int mx[N<<2],tag[N<<2];
stack<Point> s1,s2;
int w,h,n,ans=0;

void add(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr)
    {
        mx[o]+=x;
        tag[o]+=x;
        return;
    }
    int mid=(l+r)/2;
    if(nl<=mid) add(o<<1,l,mid,nl,nr,x);
    if(nr>mid) add(o<<1|1,mid+1,r,nl,nr,x);
    mx[o]=max(mx[o<<1],mx[o<<1|1])+tag[o];
}

void gao()
{
    memset(mx,0,sizeof(mx));
    memset(tag,0,sizeof(tag));
    sort(a+1,a+1+n);
    while(!s1.empty()) s1.pop();
    while(!s2.empty()) s2.pop();
    for(int i=1;i<=n;i++)
    {
        if(a[i].y<=h/2)
        {
            int nxt=i-1;
            while(!s1.empty()&&s1.top().y<a[i].y)
            {
                Point p=s1.top();s1.pop();
                add(1,1,n,p.x,nxt,p.y-a[i].y);
                nxt=p.x-1;
            }
            if(nxt!=i-1) s1.push(Point(nxt+1,a[i].y));
        }
        else
        {
            int nxt=i-1;
            while(!s2.empty()&&s2.top().y>a[i].y)
            {
                Point p=s2.top();s2.pop();
                add(1,1,n,p.x,nxt,a[i].y-p.y);
                nxt=p.x-1;
            }
            if(nxt!=i-1) s2.push(Point(nxt+1,a[i].y));
        }
        s1.push(Point(i,0));
        s2.push(Point(i,h));
        add(1,1,n,i,i,h-a[i].x);
        ans=max(ans,mx[1]+a[i+1].x);
    }
}

int main()
{
    w=read();h=read();n=read();
    for(int i=1;i<=n;i++)
        a[i].x=read(),a[i].y=read();
    a[++n]=Point(0,0);a[++n]=Point(w,h);gao();
    for(int i=1;i<=n;i++) swap(a[i].x,a[i].y);
    swap(w,h);gao();
    printf("%d\n",ans<<1);
    return 0;
}