#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
LL mxt[N],f[N],mnf[N],li[N],ri[N];
LL w[N],sufw[N],t[N];
int n;

struct Point
{
    LL x,y;
    Point(LL _x=0,LL _y=0):x(_x),y(_y){}
    LL operator () (const LL c){return x*c+y;}
    Point operator - (const Point &a){return Point(x-a.x,y-a.y);}
    LL operator * (const Point &a){return x*a.y-y*a.x;}
};

struct Convex
{
    vector<Point> cvx;
    void clear(){cvx.clear();}
    void insert(Point p)
    {
        #define m cvx.size()
        if(!m){cvx.emplace_back(p);return;}
        if(p.x==cvx[m-1].x)
        {
            if(p.y<cvx[m-1].y) cvx.pop_back();
            else return;
        }
        while(m>=2&&(cvx[m-1]-cvx[m-2])*(p-cvx[m-2])<=0) cvx.pop_back();
        cvx.emplace_back(p);
    }
    LL query(LL c)
    {
        int p=0;
        while(p<m-1&&cvx[p+1](c)<=cvx[p](c)) p++;
        return cvx[p](c);
    }
} ch[N<<2];

void build(int o,int l,int r)
{
    ch[o].clear();
    for(int i=r;i>=l;i--)
        ch[o].insert(Point(mxt[i],f[i]));
    if(l==r) return;
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
}

LL query(int o,int l,int r,int nl,int nr,LL c)
{
    if(l>=nl&&r<=nr) return ch[o].query(c);
    int mid=(l+r)/2;LL res=INT64_MAX;
    if(nl<=mid) res=min(res,query(o<<1,l,mid,nl,nr,c));
    if(nr>mid) res=min(res,query(o<<1|1,mid+1,r,nl,nr,c));
    return res;
}

void cdq(int l,int r)
{
    if(l==r) return;
    int mid=(l+r)/2;
    cdq(l,mid);
    mxt[mid]=mxt[mid+1]=t[mid+1];mnf[mid]=f[mid];
    for(int i=mid-1;i>=l;i--) mxt[i]=max(mxt[i+1],t[i+1]);
    for(int i=mid-1;i>=l;i--) mnf[i]=min(mnf[i+1],f[i]);
    for(int i=mid+2;i<=r;i++) mxt[i]=max(mxt[i-1],t[i]);
    for(int i=mid+1,p=mid+1;i<=r;i++)
    {
        while(p>l&&mxt[p-1]<=mxt[i]) p--;
        if(li[i]<=mid&&p<=mid) f[i]=min(f[i],mnf[max((LL)p,li[i])]+sufw[i+1]*mxt[i]);
        ri[i]=p-1;
    }
    for(int i=mid+1;i<=r;i++)
        li[i]=max(li[i],(LL)l);
    build(1,l,mid);
    for(int i=mid+1;i<=r;i++)
        if(li[i]<=ri[i]) f[i]=min(f[i],query(1,l,mid,li[i],ri[i],sufw[i+1]));
    cdq(mid+1,r);
}

int main()
{
    ios::sync_with_stdio(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>li[i]>>t[i]>>w[i];
    for(int i=n;i>=1;i--)
        sufw[i]=sufw[i+1]+w[i];
    memset(f,0x3f,sizeof(f));f[0]=0;
    cdq(0,n);
    cout<<f[n]<<endl;
    return 0;
}