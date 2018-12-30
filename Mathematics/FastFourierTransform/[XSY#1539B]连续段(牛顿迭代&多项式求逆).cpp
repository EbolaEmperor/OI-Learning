#include<bits/stdc++.h>
using namespace std;

const int S=1<<20;
char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
template <class I>inline void print(I x)
{
    if(!x) putc('0');
    while(x) qu[++qr]=x%10+'0',x/=10;
    while(qr) putc(qu[qr--]);
}

const int N=800010;
int rev[20][N],omg[20][N],iomg[20][N],inv[N],lg[N];
int mul1[N],mul2[N],inv1[N];
int g,ha,n,ans[N],f[N],h[N],t[N],px[N],ivt[N];

inline int add(const int &x,const int &y){return (x+y>=ha)?(x+y-ha):(x+y);}
inline int mns(const int &x,const int &y){return (x-y<0)?(x-y+ha):(x-y);}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

namespace Root
{
    int p[50],cnt=0;
    bool check(int g)
    {
        for(int i=1;i<=cnt;i++)
            if(Pow(g,(ha-1)/p[i])==1) return 0;
        return 1;
    }
    int gao()
    {
        int x=ha-1;
        for(int i=2;i*i<=x;i++)
        {
            if(x%i) continue;
            p[++cnt]=i;
            while(x%i==0) x/=i;
        }
        if(x>1) p[++cnt]=x;
        int g=2;
        while(!check(g)) g++;
        return g;
    }
}

namespace Poly
{
    void NTT_init()
    {
        int cnt=-1;
        for(int i=1,b=0;b<=18;i<<=1,b++)
        {
            inv[i]=Pow(i,ha-2);
            int p=i<<1;lg[i]=++cnt;
            omg[cnt][0]=iomg[cnt][0]=1;
            omg[cnt][1]=Pow(g,(ha-1)/p);
            iomg[cnt][1]=Pow(omg[cnt][1],ha-2);
            for(int j=2;j<i;j++) omg[cnt][j]=1ll*omg[cnt][j-1]*omg[cnt][1]%ha;
            for(int j=2;j<i;j++) iomg[cnt][j]=1ll*iomg[cnt][j-1]*iomg[cnt][1]%ha;
            for(int j=0;j<i;j++) rev[cnt][j]=(rev[cnt][j>>1]>>1)|((j&1)<<cnt-1);
        }
    }
    void NTT(int *A,int n,int d)
    {
        int bit=lg[n];
        for(int i=0;i<n;i++) if(i<rev[bit][i]) swap(A[i],A[rev[bit][i]]);
        for(int i=1,b=0;i<n;i<<=1,b++)
            for(int j=0;j<n;j+=i<<1)
                for(int k=0;k<i;k++)
                {
                    int w=(d>0)?omg[b][k]:iomg[b][k];
                    int x=A[j+k],y=1ll*w*A[i+j+k]%ha;
                    A[j+k]=add(x,y);
                    A[i+j+k]=mns(x,y);
                }
        if(d<0) for(int i=0;i<n;i++) A[i]=1ll*A[i]*inv[n]%ha;
    }
    void Mul(int *a,int *b,int *c,int n,int m)
    {
        int len=1;for(;len<n+m;len<<=1);
        for(int i=0;i<len;i++) mul1[i]=(i<n)?a[i]:0;
        for(int i=0;i<len;i++) mul2[i]=(i<m)?b[i]:0;
        NTT(mul1,len,1);NTT(mul2,len,1);
        for(int i=0;i<len;i++) c[i]=1ll*mul1[i]*mul2[i]%ha;
        NTT(c,len,-1);
    }
    void Inv(int *a,int *b,int n)
    {
        if(n==1){b[0]=Pow(a[0],ha-2);return;}
        Inv(a,b,(n+1)>>1);
        int len=1;for(;len<n<<1;len<<=1);
        for(int i=0;i<len;i++) inv1[i]=(i<n)?a[i]:0;
        NTT(inv1,len,1);NTT(b,len,1);
        for(int i=0;i<len;i++) b[i]=1ll*(2ll-1ll*inv1[i]*b[i]%ha+ha)*b[i]%ha;
        NTT(b,len,-1);for(int i=n;i<len;i++) b[i]=0;
    }
}

void gao(int* a,int n)
{
    if(n==1) return;
    gao(a,n>>1);int len=n<<1;
    for(int i=0;i<len;i++) f[i]=(i<(n>>1))?a[i]:0;
    for(int i=0;i<len;i++) px[i]=(i<2)?1:0;
    Poly::NTT(f,len,1);Poly::NTT(px,len,1);
    for(int i=0;i<len;i++)
    {
        int p1=f[i],p2=1ll*p1*p1%ha,p3=1ll*p2*p1%ha,p4=1ll*p3*p1%ha;
        h[i]=mns((p4+2ll*p2)%ha,1ll*px[i]*p1%ha);
        t[i]=4ll*(p1+p3)%ha;
    }
    Poly::NTT(h,len,-1);Poly::NTT(t,len,-1);
    (h[1]+=1)%=ha;(t[0]+=ha-1)%=ha;(t[1]+=ha-1)%=ha;
    memset(ivt,0,sizeof(int)*(n<<2));
    Poly::Inv(t,ivt,n);Poly::Mul(h,ivt,h,n,n);
    for(int i=0;i<n;i++) a[i]=mns(a[i],h[i]);
}

int main()
{
    cin>>n>>ha;
    g=Root::gao();
    Poly::NTT_init();
    int len=1;for(;len<=n;len<<=1);
    gao(ans,len);
    for(int i=1;i<=n;i++)
        print(ans[i]),putc('\n');
    return flush(),0;
}
