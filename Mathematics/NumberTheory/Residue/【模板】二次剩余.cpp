#include<bits/stdc++.h>
using namespace std;

int n,p,w;
struct Comp
{
    int r,i;
    Comp(int _r=0,int _i=0):r(_r),i(_i){}
    friend Comp operator * (const Comp &a,const Comp &b){return Comp((1ll*a.r*b.r+1ll*a.i*b.i%p*w)%p,(1ll*a.r*b.i+1ll*a.i*b.r)%p);}
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

int main()
{
    int T,n,a;
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d%d",&n,&p);n%=p;
        if(p==2){puts("1");continue;}
        if(Pow(n,(p-1)/2)==p-1){puts("No root");continue;}
        do{
            a=rand()%p;
            w=(1ll*a*a-n+p)%p;
        }while(Pow(w,(p-1)/2)!=p-1);
        Comp t=Comp(a,1)^((p+1)/2);
        int x1=t.r,x2=p-x1;
        if(x2<x1) swap(x1,x2);
        if(x1==x2) printf("%d\n",x1);
        else printf("%d %d\n",x1,x2);
    }
    return 0;
}