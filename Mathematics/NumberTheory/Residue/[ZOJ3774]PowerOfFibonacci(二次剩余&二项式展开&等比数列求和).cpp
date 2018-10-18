#include<bits/stdc++.h>
using namespace std;

const int N=100000;
const int p=1000000009;
typedef long long LL;
int w,S,R1,R2,sq5,inv2;
int fac[N+10],ifac[N+10];

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

int Pow(int a,LL b)
{
    (a+=p)%=p;
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%p)
        if(b&1) ans=1ll*ans*a%p;
    return ans;
}

void Init()
{
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=1ll*fac[i-1]*i%p;
    ifac[N]=Pow(fac[N],p-2);
    for(int i=N-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%p;
}

int C(int m,int k){return 1ll*fac[m]*ifac[k]%p*ifac[m-k]%p;}

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

int main()
{
    sq5=Sqrt(5);
    inv2=Pow(2,p-2);
    S=Pow(sq5,p-2);
    R1=1ll*(sq5+1)*inv2%p;
    R2=1ll*(1-sq5+p)*inv2%p;
    int T,K;LL n;Init();
    for(scanf("%d",&T);T;T--)
    {
        scanf("%lld%d",&n,&K);
        int ans=0;
        for(int i=0;i<=K;i++)
        {
            int res=(i&1)?p-1:1;
            res=1ll*res*C(K,i)%p;
            int a=1ll*Pow(R1,K-i)*Pow(R2,i)%p;
            a=a>1?1ll*a*(Pow(a,n)-1+p)%p*Pow(a-1,p-2)%p:n*a%p;
            res=1ll*res*a%p;
            ans=(ans+res)%p;
        }
        ans=1ll*Pow(S,K)*ans%p;
        printf("%d\n",ans);
    }
    return 0;
}