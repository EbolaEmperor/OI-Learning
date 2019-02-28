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

const int N=1000010;
int qwq,n,m,h,p,a,b,c,f[N];
int incm[N],Sbh[N],Sb[N],Tb[N];
int fac[N],ifac[N];
int hp[N],hmp[N],ap[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%p)
        if(b&1) ans=1ll*ans*a%p;
    return ans;
}

void initS(int *S,int r)
{
    if(r!=1)
    {
        int rm=Pow(r,m),ir=Pow(1-r+p,p-2);
        S[0]=1ll*(rm-1)*Pow(r-1,p-2)%p;
        for(int i=1;i<=n;i++)
            S[i]=1ll*(S[i-1]-1ll*incm[i]*ifac[i]%p*rm%p+p)*ir%p;
    }
    else for(int i=0;i<=n;i++)
        S[i]=1ll*incm[i+1]*ifac[i+1]%p;
}

void initT(int *T,int r,int *S)
{
    if(r!=1)
    {
        int ir=Pow(r-1,p-2),ir2=1ll*ir*ir%p;
        T[0]=(1ll*r*(Pow(r,m)-1)%p*ir2%p-1ll*m*ir%p+p)%p;
        for(int i=1;i<=n;i++)
            T[i]=1ll*(1ll*r*S[i]-T[i-1])%p*ir%p;
    }
    else for(int i=0;i<=n;i++)
        T[i]=1ll*incm[i+2]*ifac[i+2]%p;
}

void initPow(int *pw,int a)
{
    pw[0]=1;pw[1]=a;
    for(int i=2;i<=n+3;i++)
        pw[i]=1ll*pw[i-1]*a%p;
}

void init()
{
    incm[1]=m;
    for(int i=2;i<=n+3;i++)
        incm[i]=1ll*incm[i-1]*(m+i-1)%p;
    fac[0]=1;
    for(int i=1;i<=n+3;i++)
        fac[i]=1ll*fac[i-1]*i%p;
    ifac[n+3]=Pow(fac[n+3],p-2);
    for(int i=n+2;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%p;
    initS(Sb,b);initS(Sbh,1ll*b*h%p);
    initPow(hp,h);initPow(hmp,Pow(h,m));
    initPow(ap,a);
}

int gaoF()
{
    int res=0;
    static int sum[N];
    sum[0]=Sbh[0];
    for(int i=1;i<=n;i++)
        sum[i]=(sum[i-1]+1ll*hmp[i]*ap[i]%p*Sbh[i])%p;
    for(int k=1;k<=n;k++)
        res=(res+1ll*f[k]*hmp[k-1]%p*b%p*sum[n-k])%p;
    return res;
}

int gaoC_1()
{
    int res=0,ihm=Pow(hmp[1]-1,p-2),ih=Pow(h-1,p-2);
    for(int i=0;i<n;i++)
    {
        int tmp=1ll*hmp[i]*ap[i]%p;
        tmp=1ll*tmp*(hmp[n-i]-1)%p*ihm%p;
        int tmp2=(1ll*hmp[1]*Sb[i]-Sbh[i])%p;
        tmp2=1ll*tmp2*ih%p;
        res=(res+1ll*tmp*tmp2)%p;
    }
    return res;
}

int gaoC_2()
{
    int res=0;
    initT(Tb,b,Sb);
    for(int i=0;i<n;i++)
    {
        int tmp=1ll*ap[i]*(n-i)%p;
        tmp=1ll*tmp*Tb[i]%p;
        res=(res+tmp)%p;
    }
    return res;
}

int gaoC(){return (h!=1)?gaoC_1():gaoC_2();}

int main()
{
    qwq=read();
    n=read();m=read();h=read();p=read();
    a=read();b=read();c=read();
    for(int i=1;i<=n;i++) f[i]=read();
    init();
    int ans=gaoF();
    ans=(ans+1ll*c*gaoC())%p;
    cout<<ans<<endl;
    return 0;
}