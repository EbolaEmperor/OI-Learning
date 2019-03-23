#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline LL read()
{
    LL x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int ha=998244353;
const int N=4200000;
vector<int> omg[25],iomg[25];
int g[N],inv[N],rev[N];
int fac[N],ifac[N],dmp[N],idmp[N];
int pre[N],suf[N];
int n,m,f[N];

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=(LL)a*a%ha)
        if(b&1) ans=(LL)ans*a%ha;
    return ans;
}

void init(int N=4000010)
{
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=(LL)fac[i-1]*i%ha;
    ifac[N]=Pow(fac[N],ha-2);
    for(int i=N-1;i>=0;i--)
        ifac[i]=(LL)ifac[i+1]*(i+1)%ha;
    dmp[0]=n;
    for(int i=1;i<=4*m+1;i++)
        dmp[i]=(LL)dmp[i-1]*(n-i)%ha;
    idmp[4*m+1]=Pow(dmp[4*m+1],ha-2);
    for(int i=4*m;i>=0;i--)
        idmp[i]=(LL)idmp[i+1]*(n-i-1)%ha;
}

int C(int n,int m){return (LL)fac[n]*ifac[m]%ha*ifac[n-m]%ha;}
int Cm(int i)
{
    if(n-i<m) return 0;
    if(n<=4*m+1) return C(n-i,m);
    return ((LL)dmp[m+i-1]*(i?idmp[i-1]:1)%ha*ifac[m]%ha);
}

int Lagrange(int n,int *arry,int x)
{
    if(x<=n) return arry[x];
    pre[0]=x;suf[n]=x-n;
    for(int i=1;i<=n;i++) pre[i]=(LL)pre[i-1]*(x-i)%ha;
    for(int i=n-1;i>=0;i--) suf[i]=(LL)suf[i+1]*(x-i)%ha;
    int res=0;
    for(int i=0;i<=n;i++)
    {
        int tmp1=(LL)(i?pre[i-1]:1)*(i<n?suf[i+1]:1)%ha;
        int tmp2=(LL)ifac[i]*ifac[n-i]%ha;
        if((n-i)&1) tmp2=ha-tmp2;
        res=(res+(LL)arry[i]*tmp1%ha*tmp2)%ha;
    }
    return (res+ha)%ha;
}

void NTT_init(int n)
{
    for(int i=1,p=0;i<n;i<<=1,p++)
    {
        int wn=Pow(3,(ha-1)/(i<<1));
        int iwn=Pow(wn,ha-2);
        for(int k=0,w=1,iw=1;k<i;k++)
        {
            omg[p].emplace_back(w);
            iomg[p].emplace_back(iw);
            w=(LL)w*wn%ha;
            iw=(LL)iw*iwn%ha;
        }
    }
}

void NTT(int *a,int n,int d)
{
    for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(int i=1,p=0;i<n;i<<=1,p++)
    {
        int wn=Pow(3,(ha-1)/(i<<1));
        if(d==-1) wn=Pow(wn,ha-2);
        for(int j=0;j<n;j+=(i<<1))
            for(int k=0;k<i;k++)
            {
                int x=a[j+k],y=(LL)(d>0?omg[p][k]:iomg[p][k])*a[i+j+k]%ha;
                a[j+k]=add(x,y);a[i+j+k]=mns(x,y);
            }
    }
    int inv=Pow(n,ha-2);
    if(d==-1) for(int i=0;i<n;i++) a[i]=(LL)a[i]*inv%ha;
}

void gaogaogaogaogao()
{
    for(int i=0;i<=m;i++)
    {
        g[i]=(LL)f[i]*ifac[i]%ha*ifac[m-i]%ha;
        if((m-i)&1) g[i]=ha-g[i];
    }
    inv[1]=1;
    for(int i=2;i<=3*m+1;i++)
        inv[i]=(LL)(ha-ha/i)*inv[ha%i]%ha;
    int len=1,l=0;
    while(len<=4*m+1) len<<=1,l++;
    for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<l-1);
    NTT_init(len);
    NTT(g,len,1);NTT(inv,len,1);
    for(int i=0;i<len;i++)
        g[i]=(LL)g[i]*inv[i]%ha;
    NTT(g,len,-1);
    for(int i=m+1;i<=3*m+1;i++) f[i]=(LL)g[i]*fac[i]%ha*ifac[i-m-1]%ha;
}

int main()
{
    n=read();m=read();init();
    for(int i=0;i<=m;i++) f[i]=read();
    gaogaogaogaogao();
    for(int i=0;i<=3*m+1;i++)
    {
        int tmp1=(LL)Cm(i)*Cm(i)%ha;
        int tmp2=(LL)Cm(i+1)*Cm(i+1)%ha;
        g[i]=(LL)f[i]*(tmp1-tmp2+ha)%ha;
    }
    for(int i=1;i<=3*m+1;i++) g[i]=(g[i]+g[i-1])%ha;
    printf("%d\n",Lagrange(3*m+1,g,n-1));
    return 0;
}