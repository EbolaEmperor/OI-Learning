#include<bits/stdc++.h>
using namespace std;

const int N=400010,ha=998244353;
int *omg[30],*iomg[30];
int inv[N],rev[N];
int tinv[N],tln[N],texp[N],tpow[N],tf[N];
int n,g[N],gg[N],h[N],p[N];

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
        int wn=Pow(3,(ha-1)/(i<<1));
        int iwn=Pow(wn,ha-2);
        omg[p]=new int[i];
        iomg[p]=new int[i];
        for(int j=0,w=1,iw=1;j<i;j++)
        {
            omg[p][j]=w;
            iomg[p][j]=iw;
            w=1ll*w*wn%ha;
            iw=1ll*iw*iwn%ha;
        }
    }
    inv[1]=1;
    for(int i=2;i<N;i++)
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
}

void ntt(int *a,int n,int d)
{
    for(int i=0;i<n;i++) rev[i]=(rev[i/2]/2)|((i&1)*(n/2));
    for(int i=0;i<n;i++) if(i<rev[i]) swap(a[i],a[rev[i]]);
    for(int i=1,p=0;i<n;i<<=1,p++)
    {
        int *w=(d>0)?omg[p]:iomg[p];
        for(int j=0;j<n;j+=i<<1)
            for(int k=0;k<i;k++)
            {
                int x=a[j+k],y=1ll*w[k]*a[i+j+k]%ha;
                a[j+k]=add(x,y);
                a[i+j+k]=mns(x,y);
            }
    }
    if(d<0) for(int i=0;i<n;i++) a[i]=1ll*a[i]*inv[n]%ha;
}

void get_inv(int n,int *a,int *b)
{
    if(n==1){b[0]=Pow(a[0],ha-2);return;}
    get_inv(n>>1,a,b);n<<=1;
    memset(tinv,0,sizeof(int)*n);
    for(int i=0;i<n/2;i++) tinv[i]=a[i];
    ntt(tinv,n,1);ntt(b,n,1);
    for(int i=0;i<n;i++)
        b[i]=1ll*(2ll-1ll*tinv[i]*b[i]%ha+ha)*b[i]%ha;
    ntt(b,n,-1);
    for(int i=n/2;i<n;i++) b[i]=0;
}

void get_der(int n,int *a)
{
    for(int i=0;i<n-1;i++)
        a[i]=1ll*a[i+1]*(i+1)%ha;
    a[n-1]=0;
}

void get_int(int n,int *a)
{
    for(int i=n-1;i>0;i--)
        a[i]=1ll*a[i-1]*inv[i]%ha;
    a[0]=0;
}

void get_ln(int n,int *a)
{
    memset(tln,0,sizeof(int)*(n<<1));
    get_inv(n,a,tln);
    get_der(n,a);n<<=1;
    ntt(tln,n,1);ntt(a,n,1);
    for(int i=0;i<n;i++)
        a[i]=1ll*a[i]*tln[i]%ha;
    ntt(a,n,-1);
    get_int(n,a);
    for(int i=n/2;i<n;i++) a[i]=0;
}

void get_exp(int n,int *a,int *b)
{
    if(n==1){b[0]=1;return;}
    get_exp(n>>1,a,b);
    for(int i=0;i<n;i++) texp[i]=b[i],texp[n+i]=0;
    get_ln(n,texp);n<<=1;
    for(int i=0;i<n/2;i++)
        texp[i]=mns(a[i],texp[i]);
    texp[0]=add(texp[0],1);
    ntt(texp,n,1);ntt(b,n,1);
    for(int i=0;i<n;i++)
        b[i]=1ll*b[i]*texp[i]%ha;
    ntt(b,n,-1);
    for(int i=n/2;i<n;i++) b[i]=0;
}

void get_pow(int n,int *a,int k)
{
    memset(tpow,0,sizeof(int)*n);
    get_ln(n,a);
    for(int i=0;i<n;i++)
        a[i]=1ll*k*a[i]%ha;
    get_exp(n,a,tpow);
    memcpy(a,tpow,sizeof(int)*n);
}

void gao_g()
{
    h[0]=1;
    for(int i=1;i<=n;i++)
        h[i]=1ll*h[i-1]*i%ha;
    for(int i=0;i<=n;i++) g[i]=h[i];
    int m=1;while(m<=(n<<1)) m<<=1;
    get_inv(m/2,g,gg);g[0]=0;
    ntt(g,m,1);
    for(int i=0;i<m;i++)
        g[i]=1ll*g[i]*g[i]%ha;
    ntt(g,m,-1);
    for(int i=m/2;i<m;i++) g[i]=0;
    ntt(g,m,1);ntt(gg,m,1);
    for(int i=0;i<m;i++)
        g[i]=1ll*g[i]*gg[i]%ha;
    ntt(g,m,-1);
    for(int i=n+1;i<m;i++) g[i]=0;
}

void gao_f()
{
    int m=1;while(m<=(n<<1)) m<<=1;
    for(int i=2;i<=n;i++)
        p[i]=mns(h[i],2*g[i]%ha);
    for(int i=0;i<n;i++) tf[i]=h[i+1];
    get_pow(m/2,tf,ha-n);
    get_der(n+1,p);
    ntt(tf,m,1);ntt(p,m,1);
    for(int i=0;i<m;i++)
        p[i]=1ll*tf[i]*p[i]%ha;
    ntt(p,m,-1);
    int ans=1ll*inv[n]*p[n-1]%ha;
    cout<<ans<<endl;
}

int main()
{
    ntt_init();
    cin>>n;
    if(n==1) cout<<1<<endl;
    else if(n==2) cout<<2<<endl;
    else gao_g(),gao_f();
    return 0;
}
