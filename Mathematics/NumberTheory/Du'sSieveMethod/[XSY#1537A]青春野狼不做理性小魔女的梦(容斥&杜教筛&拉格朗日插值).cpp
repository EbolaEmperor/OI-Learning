#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=55;
int k,n,c,g;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

namespace MuSum
{
    const int M=1000010;
    int mu[M],prm[M],mark[M],tot=0;
    unordered_map<int,int> smu;

    void init(int n=1000000)
    {
        mu[1]=1;
        for(int i=2;i<=n;i++)
        {
            if(!mark[i]) prm[++tot]=i,mu[i]=-1;
            for(int j=1;j<=tot&&i*prm[j]<=n;j++)
            {
                mark[i*prm[j]]=1;
                if(i%prm[j]) mu[i*prm[j]]=-mu[i];
                else{mu[i*prm[j]]=0;break;}
            }
        }
        for(int i=2;i<=n;i++) mu[i]+=mu[i-1];
    }

    int gao(int x)
    {
        if(x<=1000000) return mu[x];
        if(smu.count(x)) return smu[x];
        int d,res=1;
        for(int i=2;i<=x;i=d+1)
            d=x/(x/i),res=(res-1ll*(d-i+1)*gao(x/i)%ha+ha)%ha;
        return smu[x]=res;
    }
}

namespace PowSum
{
    int y[N],pre[N],suf[N],ifac[N];

    void init()
    {
        y[1]=1;
        for(int i=2;i<=c+2;i++)
            y[i]=(y[i-1]+Pow(i,c))%ha;
        int facn=1;
        for(int i=1;i<=c+2;i++)
            facn=1ll*facn*i%ha;
        ifac[c+2]=Pow(facn,ha-2);
        for(int i=c+1;i>=0;i--)
            ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
        pre[0]=suf[c+3]=1;
    }

    int gao(int x)
    {
        if(x<=c+2) return y[x];
        for(int i=1;i<=c+2;i++) pre[i]=1ll*pre[i-1]*(x-i)%ha;
        for(int i=c+2;i>=1;i--) suf[i]=1ll*suf[i+1]*(x-i)%ha;
        int res=0;
        for(int i=1;i<=c+2;i++)
        {
            int t=1ll*y[i]*pre[i-1]%ha*suf[i+1]%ha;
            t=1ll*t*ifac[i-1]%ha*ifac[c+2-i]%ha;
            if((c+2-i)&1) t=ha-t;
            res=(res+t)%ha;
        }
        return res;
    }
}

int gao1()
{
    int ans=0,d;
    for(int i=1;i<=n;i=d+1)
    {
        d=n/(n/i);
        int u=(MuSum::gao(d)-MuSum::gao(i-1)+ha)%ha;
        ans=(ans+1ll*u*PowSum::gao(n/i))%ha;
    }
    return ans;
}

int gao2()
{
    static int p[N],tot=0;
    for(int i=2;i*i<=g;i++)
    {
        if(g%i) continue;
        p[++tot]=i;
        while(g%i==0) g/=i;
    }
    if(g>1) p[++tot]=g;
    int ans=0;
    for(int s=0;s<(1<<tot);s++)
    {
        int fg=1,d=1;
        for(int i=1;i<=tot;i++) if(s&(1<<i-1)) fg*=-1,d*=p[i];
        ans=(ans+fg*PowSum::gao(n/d))%ha;
    }
    return (ans+ha)%ha;
}

int main()
{
    scanf("%d%d",&k,&n);
    int cnt=0;
    for(int i=1,x;i<=k;i++)
    {
        scanf("%d",&x);
        if(x==-1) c++;
        if(x>0) g=g?__gcd(g,x):x;
        if(x) cnt++;
    }
    PowSum::init();MuSum::init();
    printf("%d\n",(c==cnt)?gao1():gao2());
    return 0;
}