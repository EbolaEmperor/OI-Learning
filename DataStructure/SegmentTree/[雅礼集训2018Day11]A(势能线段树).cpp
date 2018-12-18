#include<bits/stdc++.h>
using namespace std;
 
const int N=200010;
const int all=(1<<20)-1;
int mx[N<<2],sand[N<<2],sor[N<<2];
int tand[N<<2],tor[N<<2];
int n,q,a[N];
 
void maintain(int o)
{
    sand[o]=sand[o<<1]&sand[o<<1|1];
    sor[o]=sor[o<<1]|sor[o<<1|1];
    mx[o]=max(mx[o<<1],mx[o<<1|1]);
}
 
inline void mand(int o,int x){mx[o]&=x;sand[o]&=x;sor[o]&=x;tand[o]&=x;tor[o]&=x;}
inline void mor(int o,int x){mx[o]|=x;sand[o]|=x;sor[o]|=x;tor[o]|=x;}
 
void pushdown(int o)
{
    if(tand[o]<all)
    {
        mand(o<<1,tand[o]);
        mand(o<<1|1,tand[o]);
        tand[o]=all;
    }
    if(tor[o]>0)
    {
        mor(o<<1,tor[o]);
        mor(o<<1|1,tor[o]);
        tor[o]=0;
    }
}
 
void build(int o,int l,int r)
{
    tand[o]=all;tor[o]=0;
    if(l==r)
    {
        mx[o]=sand[o]=sor[o]=a[l];
        return;
    }
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    maintain(o);
}
 
void cand(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr)
        if(((x^all)&(sand[o]|(sor[o]^all)))==(x^all))
            return mand(o,x);
    pushdown(o);
    int mid=(l+r)/2;
    if(nl<=mid) cand(o<<1,l,mid,nl,nr,x);
    if(nr>mid) cand(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}
 
void cor(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr)
        if((x&(sand[o]|(sor[o]^all)))==x)
            return mor(o,x);
    pushdown(o);
    int mid=(l+r)/2;
    if(nl<=mid) cor(o<<1,l,mid,nl,nr,x);
    if(nr>mid) cor(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}
 
int qmax(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return mx[o];
    int mid=(l+r)/2,res=0;pushdown(o);
    if(nl<=mid) res=max(res,qmax(o<<1,l,mid,nl,nr));
    if(nr>mid) res=max(res,qmax(o<<1|1,mid+1,r,nl,nr));
    return res;
}
 
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    build(1,1,n);
    int opt,l,r,x;
    while(q--)
    {
        scanf("%d%d%d",&opt,&l,&r);
        if(opt<3) scanf("%d",&x);
        if(opt==1) cand(1,1,n,l,r,x);
        if(opt==2) cor(1,1,n,l,r,x);
        if(opt==3) printf("%d\n",qmax(1,1,n,l,r));
    }
    return 0;
}
