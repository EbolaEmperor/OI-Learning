#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

typedef long long LL;
const int ha=998244353;
const int N=400010;
int A[N],B[N],n,ma,mb;
int rev[N],omg[N],iomg[N],inv[N];
int t1[N],t2[N],t3[N],t4[N],t5[N];
int f[N],g[N],fac[N],ifac[N];

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int dev(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=(LL)a*a%ha)
        if(b&1) ans=(LL)ans*a%ha;
    return ans;
}

void NTT_init()
{
    for(int i=1;i<N;i<<=1)
    {
        int p=i<<1;
        omg[i]=Pow(3,(ha-1)/p);
        iomg[i]=Pow(omg[i],ha-2);
        inv[i]=Pow(i,ha-2);
    }
}

void fac_init(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=(LL)fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=(LL)ifac[i+1]*(i+1)%ha;
}

void NTT(int *A,int n,int v)
{
    for(int i=0;i<n;i++) if(i<rev[i]) swap(A[i],A[rev[i]]);
    for(int i=1;i<n;i<<=1)
    {
        int wn=(v>0)?omg[i]:iomg[i];
        for(int j=0;j<n;j+=(i<<1))
            for(int k=0,w=1;k<i;k++)
            {
                int x=A[j+k],y=(LL)w*A[i+j+k]%ha;
                A[j+k]=add(x,y);
                A[i+j+k]=dev(x,y);
                w=(LL)w*wn%ha;
            }
    }
    if(v<0) for(int i=0;i<n;i++) A[i]=(LL)A[i]*inv[n]%ha;
}

void clear(int n)
{
    memset(t1,0,sizeof(int)*(n+1));
    memset(t2,0,sizeof(int)*(n+1));
    memset(t3,0,sizeof(int)*(n+1));
    memset(t4,0,sizeof(int)*(n+1));
    memset(t5,0,sizeof(int)*(n+1));
}

void gao(int l,int r)
{
    if(l==r)
    {
        f[l]=add(f[l],B[l-1]);
        g[l]=add(g[l],f[l]);
        return;
    }
    int mid=(l+r)/2;gao(l,mid);
    int len=1,pl=0;for(;len<=r-l;len<<=1,pl++);clear(len);
    for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<pl-1);
    for(int i=l;i<=mid;i++) t1[i-l]=(LL)g[i]*ifac[i]%ha;
    for(int i=0;i<r-l;i++) t2[i]=A[i]*ifac[i];
    NTT(t1,len,1);NTT(t2,len,1);
    for(int i=0;i<len;i++) t2[i]=(LL)t1[i]*t2[i]%ha;
    NTT(t2,len,-1);
    for(int i=mid+1;i<=r;i++) f[i]=add(f[i],(LL)fac[i-1]*t2[i-l-1]%ha);
    for(int i=2;i<=min(r-l,mid);i++) t3[i-1]=(LL)f[i]*ifac[i-1]%ha;
    for(int i=1;i<=min(r-l,l-1);i++) t4[i-1]=(LL)g[i]*ifac[i]%ha;
    for(int i=max(l,2);i<=mid;i++) t5[i-l]=(LL)f[i]*ifac[i-1]%ha;
    NTT(t3,len,1);NTT(t4,len,1);NTT(t5,len,1);
    for(int i=0;i<len;i++) t1[i]=add((LL)t1[i]*t3[i]%ha,(LL)t4[i]*t5[i]%ha);
    NTT(t1,len,-1);
    for(int i=mid+1;i<=r;i++) g[i]=add(g[i],(LL)fac[i-1]*t1[i-l-1]%ha);
    gao(mid+1,r);
}

int main()
{
    NTT_init();fac_init(114514);
    n=read();ma=read();mb=read();
    if(n==1) return puts("1"),0;
    for(int i=1;i<=ma;i++) A[read()]=1;
    for(int i=1;i<=mb;i++) B[read()]=1;
    B[0]=0;gao(1,n);printf("%d\n",f[n]);
    return 0;
}