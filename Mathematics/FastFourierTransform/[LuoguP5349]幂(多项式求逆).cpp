#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=400010;
int rev[N],f[N],g[N];
int fac[N],ifac[N];
int m,r,a[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void ntt(int *a,int n,int d)
{
    for(int i=0;i<n;i++) rev[i]=(rev[i>>1]>>1)|((i&1)*(n/2));
    for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(int i=1;i<n;i<<=1)
    {
        int wn=Pow(3,(ha-1)/(i<<1));
        if(d<0) wn=Pow(wn,ha-2);
        for(int j=0;j<n;j+=i<<1)
            for(int k=0,w=1;k<i;k++)
            {
                int x=a[j+k],y=1ll*w*a[i+j+k]%ha;
                a[j+k]=(x+y)%ha;
                a[i+j+k]=(x-y+ha)%ha;
                w=1ll*w*wn%ha;
            }
    }
    int inv=Pow(n,ha-2);
    if(d<0) for(int i=0;i<n;i++) a[i]=1ll*a[i]*inv%ha;
}

void getinv(int n,int *a,int *b)
{
    if(n==1){b[0]=Pow(a[0],ha-2);return;}
    getinv(n>>1,a,b);
    static int c[N];n<<=1;
    for(int i=0;i<n/2;i++) c[i]=a[i],c[i+n/2]=0;
    ntt(c,n,1);ntt(b,n,1);
    for(int i=0;i<n;i++)
        b[i]=1ll*(2ll-1ll*c[i]*b[i]%ha+ha)*b[i]%ha;
    ntt(b,n,-1);
    for(int i=n/2;i<n;i++) b[i]=0;
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

int main()
{
    scanf("%d%d",&m,&r);
    int b=Pow(1-r+ha,ha-2),t=1ll*r*b%ha;
    for(int i=0;i<=m;i++) scanf("%d",a+i);
    int len=1,l=0;
    while(len<=m) len<<=1,l++;
    init(len);
    for(int i=1;i<len;i++) f[i]=ha-1ll*t*ifac[i]%ha;
    f[0]=1;getinv(len,f,g);
    int ans=0;
    for(int i=0;i<=m;i++)
        ans=(ans+1ll*a[i]*g[i]%ha*fac[i]%ha*b%ha)%ha;
    cout<<ans<<endl;
    return 0;
}