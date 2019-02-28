#include<bits/stdc++.h>
using namespace std;

const int ha=19491001;
const int N=500010;
int fac[N],ifac[N];
int n,k,d;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void init(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}
int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int gao2()
{
    init(k);
    int ans=0;
    for(int i=0;i<=k;i++)
        ans=(ans+1ll*C(k,i)*Pow(2*i-k,n))%ha;
    ans=(ans+ha)%ha;
    ans=1ll*ans*Pow(Pow(2,k),ha-2)%ha;
    return ans;
}

int gao3()
{
    init(k);
    int ans=0,g1=Pow(7,(ha-1)/3),g2=Pow(g1,2);
    for(int i=0;i<=k;i++)
        for(int j=0;j<=k-i;j++)
        {
            int p=(i+1ll*g1*j+1ll*g2*(k-i-j))%ha;
            int tmp=1ll*C(k,i)*C(k-i,j)%ha*Pow(p,n)%ha;
            ans=(ans+tmp)%ha;
        }
    ans=1ll*ans*Pow(Pow(3,k),ha-2)%ha;
    return ans;
}

int main()
{
    cin>>n>>k>>d;
    if(n%d) return puts("0"),0;
    if(d==1) printf("%d\n",Pow(k,n));
    else if(d==2) printf("%d\n",gao2());
    else printf("%d\n",gao3());
    return 0;
}