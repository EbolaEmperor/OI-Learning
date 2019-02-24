#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=1200010;
int fac[N],ifac[N];
int T,n,a[N],h[N],x[N];
bool fix[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void init(int n=1200000)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int gao(int hight,int width)
{
    if(hight==width) return 1;
    if(hight<0||width<=0||(width-hight&1)) return 0;
    return (C(width,(width-hight)/2)-C(width,(width-hight-2)/2)+ha)%ha;
}

int main()
{
    init();
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        memset(fix,0,sizeof(bool)*(n+2));
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        int mx=0,mn=1,ans=0;
        x[0]=h[0]=0;
        for(int i=1;i<=n;i++)
        {
            if(a[i]>mx)
            {
                for(int k=0;k<a[i]-mx;k++)
                    ans=(ans+gao(h[i-1]+k-1,2*n-x[i-1]-k-1))%ha;
                x[i]=x[i-1]+(a[i]-mx)+1;
                h[i]=h[i-1]+(a[i]-mx)-1;
                mx=a[i];
            }
            else
            {
                while(fix[mn]) mn++;
                if(a[i]!=mn)
                {
                    ans=(ans+gao(h[i-1]-1,2*n-x[i-1]-1))%ha;
                    goto finished;
                }
                x[i]=x[i-1]+1;
                h[i]=h[i-1]-1;
            }
            fix[a[i]]=1;
        }
        ans=(ans+1)%ha;
        finished: printf("%d\n",(gao(0,2*n)-ans+ha)%ha);
    }
    return 0;
}