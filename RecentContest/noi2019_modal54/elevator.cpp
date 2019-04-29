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

typedef long long LL;
const int N=1000010;
struct G{int t,x;} g[N];
LL f[N];int n,stk[N],top=0;

struct SegmentTree
{
    LL mx[N<<2],mn[N<<2];
    void build(int o,int l,int r)
    {
        mn[o]=INT64_MAX;
        if(l==r) return;
        int mid=(l+r)/2;
        build(o<<1,l,mid);
        build(o<<1|1,mid+1,r);
    }
    void update(int o,int l,int r,int k,LL x)
    {
        if(l==r){mx[o]=mn[o]=x;return;}
        int mid=(l+r)/2;
        if(k<=mid) update(o<<1,l,mid,k,x);
        else update(o<<1|1,mid+1,r,k,x);
        mx[o]=max(mx[o<<1],mx[o<<1|1]);
        mn[o]=min(mn[o<<1],mn[o<<1|1]);
    }
    LL qmax(int o,int l,int r,int nl,int nr)
    {
        if(l>=nl&&r<=nr) return mx[o];
        int mid=(l+r)/2;LL res=0;
        if(nl<=mid) res=max(res,qmax(o<<1,l,mid,nl,nr));
        if(nr>mid) res=max(res,qmax(o<<1|1,mid+1,r,nl,nr));
        return res;
    }
    LL qmin(int o,int l,int r,int nl,int nr)
    {
        if(l>=nl&&r<=nr) return mn[o];
        int mid=(l+r)/2;LL res=UINT_MAX;
        if(nl<=mid) res=min(res,qmin(o<<1,l,mid,nl,nr));
        if(nr>mid) res=min(res,qmin(o<<1|1,mid+1,r,nl,nr));
        return res;
    }
} t1,t2;

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        g[i].t=read(),g[i].x=read();
    sort(g+1,g+1+n,[](G a,G b){return a.t<b.t;});
    stk[++top]=0;
    t1.build(1,0,n);
    int clk=0;
    for(int i=1;i<=n;i++)
    {
        t2.update(1,0,n,i,g[i].x);
        while(top>1&&g[i].x>g[stk[top]].x)
            t1.update(1,0,n,stk[top-1],UINT_MAX),top--;
        t1.update(1,0,n,stk[top],f[stk[top]]+2*g[i].x);
        stk[++top]=i;
        int pos=upper_bound(f,f+i,g[i].t)-f;
        f[i]=g[i].t+t2.qmax(1,0,n,pos,i)*2;
        if(pos<i) f[i]=min(f[i],t1.qmin(1,0,n,pos,i-1));
    }
    cout<<f[n]<<endl;
    return 0;
}