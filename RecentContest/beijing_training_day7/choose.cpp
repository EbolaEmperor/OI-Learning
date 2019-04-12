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
const int ha=998244353,M=65536,SZ=57;
const int inv6=166374059,inv24=291154603;
int n,k,s,cnt[M];
int phi[M],mark[M],prime[M],prn=0;

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}
inline int div2(const int &x){return (x&1)?(x+ha)/2:x/2;}

void fwt(int *a,int n)
{
    for(int i=1;i<n;i<<=1)
        for(int j=0;j<n;j+=i<<1)
            for(int k=0;k<i;k++)
            {
                int x=a[j+k],y=a[i+j+k];
                a[j+k]=add(x,y);
                a[i+j+k]=mns(x,y);
            }
}

void ifwt(int *a,int n)
{
    for(int i=1;i<n;i<<=1)
        for(int j=0;j<n;j+=i<<1)
            for(int k=0;k<i;k++)
            {
                int x=a[j+k],y=a[i+j+k];
                a[j+k]=div2(add(x,y));
                a[i+j+k]=div2(mns(x,y));
            }
}

int gao1(int d){return (s%d==0)?cnt[s]:0;}

int gao2(int d)
{
    static int num[M];
    LL ans=0;
    for(int i=d;i<M;i+=d) num[i]=cnt[i];
    for(int i=d;i<M;i+=d)
        ans+=(LL)num[i]*num[s^i];
    for(int i=d;i<M;i+=d) num[i]=0;
    return ans%ha;
}

int gao3(int d)
{
    int ans=0,tot=0;
    static int num[M];
    for(int i=d;i<M;i+=d) tot+=cnt[i];
    if(d<=SZ)
    {
        for(int i=d;i<M;i+=d) num[i]=cnt[i];
        fwt(num,M);
        for(int i=0;i<M;i++)
            num[i]=(LL)num[i]*num[i]%ha*num[i]%ha;
        ifwt(num,M);
        ans=num[s];
        memset(num,0,sizeof(num));
    }
    else
    {
        for(int i=d;i<M;i+=d) num[i]=cnt[i];
        for(int i=d;i<M;i+=d)
            for(int j=d;j<M;j+=d)
                ans=(ans+(LL)cnt[i]*cnt[j]*num[s^i^j])%ha;
        for(int i=d;i<M;i+=d) num[i]=0;
    }
    return (LL)(ans-(LL)(3*tot-2)*gao1(d)%ha+ha)*inv6%ha;
}

int gao4(int d)
{
    int ans=0,tot=0;
    static int num[M];
    for(int i=d;i<M;i+=d) tot+=cnt[i];
    if(d<=SZ)
    {
        for(int i=d;i<M;i+=d) num[i]=cnt[i];
        fwt(num,M);
        for(int i=0;i<M;i++)
            num[i]=(LL)num[i]*num[i]%ha*num[i]%ha*num[i]%ha;
        ifwt(num,M);
        ans=num[s];
        memset(num,0,sizeof(num));
    }
    else
    {
        for(int i=d;i<M;i+=d)
            for(int j=d;j<M;j+=d)
                num[i^j]=(num[i^j]+(LL)cnt[i]*cnt[j])%ha;
        for(int i=d;i<M;i+=d)
            for(int j=d;j<M;j+=d)
                ans=(ans+(LL)cnt[i]*cnt[j]%ha*num[s^i^j])%ha;
        for(int i=d;i<M;i+=d)
            for(int j=d;j<M;j+=d)
                num[i^j]=0;
    }
    return (LL)(ans-(LL)(6*tot-8)*gao2(d)%ha+ha)*inv24%ha;
}

int gao(int d)
{
    if(k==1) return gao1(d);
    if(k==2) return div2(gao2(d));
    if(k==3) return gao3(d);
    if(k==4) return gao4(d);
}

void seive(int M=50000)
{
    phi[1]=1;
    for(int i=2;i<=M;i++)
    {
        if(!mark[i]) prime[++prn]=i,phi[i]=i-1;
        for(int j=1;j<=prn&&i*prime[j]<=M;j++)
        {
            mark[i*prime[j]]=1;
            if(i%prime[j]) phi[i*prime[j]]=phi[i]*phi[prime[j]];
            else{phi[i*prime[j]]=phi[i]*prime[j];break;}
        }
    }
}

int main()
{
    seive();
    n=read();k=read();s=read();
    for(int i=1;i<=n;i++) cnt[read()]++;
    int ans=0;
    for(int i=1;i<=50000;i++)
        ans=(ans+(LL)gao(i)*phi[i])%ha;
    printf("%d\n",ans);
    return 0;
}
