#include<bits/stdc++.h>
using namespace std;

int n,w;
const int p=1000000009;
struct Comp
{
    int r,i;
    Comp(int _r=0,int _i=0):r(_r),i(_i){}
    Comp operator * (const Comp &a){return Comp((1ll*r*a.r+1ll*i*a.i%p*w)%p,(1ll*r*a.i+1ll*i*a.r)%p);}
    friend Comp operator ^ (Comp a,int b)
    {
        Comp ans(1,0);
        for(;b;b>>=1,a=a*a)
            if(b&1) ans=ans*a;
        return ans;
    }
};

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%p)
        if(b&1) ans=1ll*ans*a%p;
    return ans;
}

int Sqrt(int n)
{
    if(Pow(n,(p-1)/2)==p-1) return -1;
    int a;
    do{
        a=rand()%p;
        w=(1ll*a*a-n+p)%p;
    }while(Pow(w,(p-1)/2)!=p-1);
    Comp t=Comp(a,1)^((p+1)/2);
    return t.r;
}

int BSGS(int a,int b)
{
    map<int,int> mp;
    int m=sqrt(p),base=1;
    for(int i=0;i<m;i++)
    {
        mp.insert(make_pair(base,i));
        base=1ll*base*a%p;
    }
    int d=1;
    for(int i=0;i<m;i++)
    {
        int y=1ll*b*Pow(d,p-2)%p;
        if(mp.count(y)) return m*i+mp[y];
        d=1ll*d*base%p;
    }
    return p+1;
}

int main()
{
    scanf("%d",&n);
    int sq5=Sqrt(5),inv2=Pow(2,p-2);
    int T=1ll*sq5*n%p,r=1ll*(sq5+1)*inv2%p;
    int delta=Sqrt((1ll*T*T+4)%p),ans=p+1,res;
    if(~delta)
    {
        int a=1ll*(T+delta)*inv2%p;
        res=BSGS(r,a);
        if(res<p&&!(res&1)) ans=min(ans,res);
        a=1ll*(T-delta+p)*inv2%p;
        res=BSGS(r,a);
        if(res<p&&!(res&1)) ans=min(ans,res);
    }
    delta=Sqrt((1ll*T*T-4+p)%p);
    if(~delta)
    {
        int a=1ll*(T+delta)*inv2%p;
        res=BSGS(r,a);
        if(res<p&&(res&1)) ans=min(ans,res);
        a=1ll*(T-delta+p)*inv2%p;
        res=BSGS(r,a);
        if(res<p&&(res&1)) ans=min(ans,res);
    }
    if(ans==p+1) puts("-1");
    else printf("%d\n",ans);
    return 0;
}