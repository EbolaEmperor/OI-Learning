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
struct Point{LL x,y;} p[N];
int mx[N<<2],tag[N<<2];
int n,k,my,lft[N];
LL hy[N];

bool operator < (const Point &a,const Point &b){return a.x<b.x;}

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

bool check(LL d)
{
    memset(mx,0,sizeof(mx));
    memset(tag,0,sizeof(tag));
    for(int i=1,l=1;i<=my;i++)
    {
        while(hy[i]-hy[l]>d) l++;
        lft[i]=l;
    }
    for(int i=1,l=1,r=0;i<=n;i++)
    {
        while(r<n&&p[r+1].x-p[i].x<=d) r++,add(1,1,my,lft[p[r].y],p[r].y,1);
        while(l<r&&p[l].x<p[i].x) add(1,1,my,lft[p[l].y],p[l].y,-1),l++;
        if(mx[1]>=k) return 1;
        if(r==n) return 0;
    }
    return 0;
}

int main()
{
    n=read();k=read();
    for(int i=1;i<=n;i++)
    {
        p[i].x=read();
        p[i].y=read();
        hy[i]=p[i].y;
    }
    sort(hy+1,hy+1+n);
    my=unique(hy+1,hy+1+n)-(hy+1);
    for(int i=1;i<=n;i++) p[i].y=lower_bound(hy+1,hy+1+my,p[i].y)-hy;
    sort(p+1,p+1+n);
    LL l=0,r=4e9,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(check(mid)) r=mid-1;
        else l=mid+1;
    }
    printf("%lld\n",l);
    return 0;
}