#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=998244353;
const int N=10100010;
int fac[N],ifac[N];
int pwa[N],ipwa[N],pwb[N];
int m,n,a,b,p,q,f[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=(LL)a*a%ha)
        if(b&1) ans=(LL)ans*a%ha;
    return ans;
}

void Init(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=(LL)fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=(LL)ifac[i+1]*(i+1)%ha;
    int ia=Pow(a,ha-2);
    pwa[0]=ipwa[0]=pwb[0]=1;
    for(int i=1;i<=n;i++)
    {
        pwa[i]=(LL)pwa[i-1]*a%ha;
        pwb[i]=(LL)pwb[i-1]*b%ha;
        ipwa[i]=(LL)ipwa[i-1]*ia%ha;
    }
}

inline int C(int n,int m){return (LL)fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int gao_down(int x,int y)
{
    int res=0;
    for(int k=1;k<=y;k++)
    {
        if(x-p<y-k) continue;
        int t=(LL)C(x-p,y-k)*pwa[x-p-y+k]%ha*pwb[y-k]%ha*f[k]%ha;
        res=(res+t)%ha;
    }
    return res;
}

int gao_up(int x,int y)
{
    int res=0;
    for(int k=1;k<=y;k++)
    {
        int t=(LL)C(p-x+y-k-1,y-k)*pwb[y-k]%ha*ipwa[p-x+y-k]%ha*f[k]%ha;
        if((y-k)&1) t=ha-t;
        res=(res+t)%ha;
    }
    return res;
}

int main()
{
    scanf("%d%d%d%d%d%d",&m,&n,&a,&b,&p,&q);
    for(int i=1;i<=n;i++) scanf("%d",f+i);
    Init(m+n);
    while(q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        if(x==p) printf("%d\n",f[y]);
        if(x>p) printf("%d\n",gao_down(x,y));
        if(x<p) printf("%d\n",gao_up(x,y));
    }
    return 0;
}