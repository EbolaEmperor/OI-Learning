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

const int ha=998244353;
const int N=800010;
int omg[N],iomg[N];
int fac[N],ifac[N],inv[N],p2[N];
int rev[N],A[N],B[N];
int xl[N],xr[N],yl[N],yr[N],lx[N],ly[N];
int h,w,n;

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int dec(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void NTT(int *A,int n,int d)
{
    for(int i=0;i<n;i++) if(i<rev[i]) swap(A[i],A[rev[i]]);
    for(int i=1;i<n;i<<=1)
    {
        int wn=(d>0)?omg[i]:iomg[i];
        for(int j=0;j<n;j+=(i<<1))
            for(int k=0,w=1;k<i;k++)
            {
                int x=A[j+k],y=1ll*w*A[i+j+k]%ha;
                A[j+k]=add(x,y);
                A[i+j+k]=dec(x,y);
                w=1ll*w*wn%ha;
            }
    }
    if(d==-1) for(int i=0;i<n;i++) A[i]=1ll*A[i]*inv[n]%ha;
}

struct Poly
{
    vector<int> v;
    Poly(int n=0){v.clear();v.resize(n);}
    int size(){return v.size();}
    int& operator [] (const int &x){return v[x];}
    void reverse(){std::reverse(v.begin(),v.end());}
    Poly operator * (Poly &c)
    {
        int n=size(),m=c.size(),len=1,l=0;
        while(len<n+m) len<<=1,l++;
        for(int i=0;i<len;i++) A[i]=(i<n)?v[i]:0;
        for(int i=0;i<len;i++) B[i]=(i<m)?c[i]:0;
        for(int i=0;i<len;i++) rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
        NTT(A,len,1);NTT(B,len,1);
        for(int i=0;i<len;i++)
            A[i]=1ll*A[i]*B[i]%ha;
        NTT(A,len,-1);
        Poly res(len);
        for(int i=0;i<len;i++)
            res[i]=A[i];
        return res;
    }
} fx,fy;

void init(int n=800000)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
    inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
    p2[0]=1;
    for(int i=1;i<=n;i++)
        p2[i]=(p2[i-1]<<1)%ha;
    for(int i=1;i<n;i<<=1)
    {
        omg[i]=Pow(3,(ha-1)/(i<<1));
        iomg[i]=Pow(omg[i],ha-2);
    }
}
int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

Poly gao_RtoL_DtoU(Poly &fx,int lx1,int lx2,int a,int b)
{
    if(b<0) return Poly(lx2);
    Poly g(lx1+lx2);
    for(int i=0;i<g.size();i++)
        g[i]=C(a+i+b,b-1);
    Poly h=fx*g,res(lx2);
    for(int i=0;i<lx2;i++)
        res[i]=h[lx1+i-1];
    return res;
}

Poly gao_RtoU_DtoL(Poly &fx,int lx,int ly,int a,int b)
{
    Poly g(lx),h(lx+ly);
    for(int i=0;i<g.size();i++)
        g[i]=1ll*fx[i]*ifac[b+lx-i-1]%ha;
    for(int i=0;i<h.size();i++)
        h[i]=fac[a+b-1+i];
    Poly r=g*h,res(ly);
    for(int i=0;i<ly;i++)
        res[i]=1ll*r[lx+i]*ifac[a+i]%ha;
    return res;
}

Poly gao_LtoR_UtoD(Poly &fx,int lx,int a)
{
    Poly g(lx);
    for(int i=0;i<g.size();i++)
        g[i]=1ll*(p2[a+i]-1)*C(a+i-1,a-1)%ha;
    Poly res=fx*g;
    res.v.resize(lx);
    return res;
}

Poly gao_LtoD_UtoR(Poly &fx,int lx,int ly)
{
    Poly h(lx),g(lx+ly);
    for(int i=0;i<h.size();i++)
        h[i]=1ll*fx[i]*ifac[lx-i-1]%ha;
    for(int i=0;i<g.size();i++)
        g[i]=1ll*(p2[i]-1)*fac[i-1]%ha;
    Poly r=g*h,res(ly);
    for(int i=0;i<ly;i++)
        res[i]=1ll*r[lx+i]*ifac[i]%ha;
    return res;
}

int main()
{
    init();
    h=read();w=read();n=read();
    for(int i=0;i<=n+1;i++)
    {
        xl[i]=read();yl[i]=read();
        xr[i]=read();yr[i]=read();
        lx[i]=xr[i]-xl[i]+1;
        ly[i]=yr[i]-yl[i]+1;
    }
    fx=Poly(lx[0]);fy=Poly(ly[0]);
    for(int i=0;i<lx[0];i++) fx[i]=C(lx[0]+ly[0]-i,ly[0])-1;
    for(int i=0;i<ly[0];i++) fy[i]=C(lx[0]+ly[0]-i,lx[0])-1;
    fx.reverse();fy.reverse();
    for(int i=1;i<=n+1;i++)
    {
        static Poly h1,h2,h3,h4;
        h1=gao_RtoL_DtoU(fx,lx[i-1],lx[i],xl[i]-xr[i-1]-1,yl[i]-yr[i-1]-1); // R to L
        h2=gao_RtoU_DtoL(fx,lx[i-1],ly[i],yl[i]-yr[i-1]-1,xl[i]-xr[i-1]-1); // R to U
        h3=gao_RtoL_DtoU(fy,ly[i-1],ly[i],yl[i]-yr[i-1]-1,xl[i]-xr[i-1]-1); // D to U
        h4=gao_RtoU_DtoL(fy,ly[i-1],lx[i],xl[i]-xr[i-1]-1,yl[i]-yr[i-1]-1); // D to L
        fx=Poly(lx[i]);fy=Poly(ly[i]);
        for(int j=0;j<lx[i];j++) fx[j]=add(h1[j],h4[j]);
        for(int j=0;j<ly[i];j++) fy[j]=add(h2[j],h3[j]);
        if(i==n+1) break;
        h1=gao_LtoR_UtoD(fx,lx[i],ly[i]); // L to R
        h2=gao_LtoR_UtoD(fy,ly[i],lx[i]); // U to D
        h3=gao_LtoD_UtoR(fx,lx[i],ly[i]); // L to D
        h4=gao_LtoD_UtoR(fy,ly[i],lx[i]); // U to R
        for(int j=0;j<lx[i];j++) fx[j]=add(h1[j],h4[j]);
        for(int j=0;j<ly[i];j++) fy[j]=add(h2[j],h3[j]);
    }
    int ans=0;
    for(int i=0;i<lx[n+1];i++)
        ans=(ans+1ll*fx[i]*(C(lx[n+1]+ly[n+1]-i,ly[n+1])-1))%ha;
    for(int i=0;i<ly[n+1];i++)
        ans=(ans+1ll*fy[i]*(C(lx[n+1]+ly[n+1]-i,lx[n+1])-1))%ha;
    ans=(ans+ha)%ha;
    printf("%d\n",ans);
    return 0;
}