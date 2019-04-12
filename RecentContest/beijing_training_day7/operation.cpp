#include<bits/stdc++.h>
using namespace std;

const int ha=998244353,N=400010;
int omg[20][N],iomg[20][N];
int f[N],g[N],h[N];
int rev[N],inv[N];
int *poly[N],*poly2[N];
int n,p[N],a[N],b[N];
int fac[N],ifacn;

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void ntt_init()
{
    for(int i=1,p=0;i<N;i<<=1,p++)
    {
        inv[i]=Pow(i,ha-2);
        int wn=Pow(3,(ha-1)/(i<<1));
        int iwn=Pow(wn,ha-2);
        for(int k=0,w=1,iw=1;k<i;k++)
        {
            omg[p][k]=w;
            iomg[p][k]=iw;
            w=1ll*w*wn%ha;
            iw=1ll*iw*iwn%ha;
        }
    }
}

void ntt(int *a,int n,int d)
{
    for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(int i=1,p=0;i<n;i<<=1,p++)
    {
        int* cur=(d>0?omg[p]:iomg[p]);
        for(int j=0;j<n;j+=i<<1)
            for(int k=0;k<i;k++)
            {
                int x=a[j+k],y=1ll*cur[k]*a[i+j+k]%ha;
                a[j+k]=add(x,y);
                a[i+j+k]=mns(x,y);
            }
    }
    if(d<0) for(int i=0;i<n;i++) a[i]=1ll*a[i]*inv[n]%ha;
}

void mul(int *a,int *b,int *c,int n,int m)
{
    int len=1,l=0;
    while(len<=n+m) len<<=1,l++;
    for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<l-1);
    for(int i=0;i<=n;i++) f[i]=a[i];
    for(int i=0;i<=m;i++) g[i]=b[i];
    for(int i=n+1;i<len;i++) f[i]=0;
    for(int i=m+1;i<len;i++) g[i]=0;
    ntt(f,len,1);ntt(g,len,1);
    for(int i=0;i<len;i++) h[i]=1ll*f[i]*g[i]%ha;
    ntt(h,len,-1);
    for(int i=0;i<=n+m;i++) c[i]=add(c[i],h[i]);
}

void gao(int o,int l,int r)
{
    poly[o]=new int[r-l+2];
    poly2[o]=new int[r-l+1];
    memset(poly[o],0,sizeof(int)*(r-l+2));
    memset(poly2[o],0,sizeof(int)*(r-l+1));
    if(l==r)
    {
        poly2[o][0]=1ll*a[l]*p[l]%ha;
        poly[o][0]=(p[l]+1ll*(ha+1-p[l])*b[l])%ha;
        poly[o][1]=1;
        return;
    }
    int mid=(l+r)/2;
    gao(o<<1,l,mid);
    gao(o<<1|1,mid+1,r);
    mul(poly[o<<1],poly[o<<1|1],poly[o],mid-l+1,r-mid);
    mul(poly[o<<1],poly2[o<<1|1],poly2[o],mid-l+1,r-mid-1);
    mul(poly2[o<<1],poly[o<<1|1],poly2[o],mid-l,r-mid);
}

void fac_init()
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifacn=Pow(fac[n],ha-2);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",p+i,a+i,b+i);
    ntt_init();
    gao(1,1,n);
    fac_init();
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=(ans+1ll*poly2[1][i-1]*fac[i-1]%ha*fac[n-i])%ha;
    ans=1ll*ans*ifacn%ha;
    printf("%d\n",ans);
    return 0;
}
