#include<bits/stdc++.h>
using namespace std;

const int ha=1004535809;
const long long bigha=2ll*ha*ha;
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

const int N=300010;
int r[N],A[N],B[N];
int gpw[20],igpw[20];
int v[N],n,k;
long long f[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void NTT(int *A,int n,bool IDFT)
{
    for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1,l=0;i<n;i<<=1,l++)
    {
        int wn=IDFT?igpw[l]:gpw[l];
        for(int j=0;j<n;j+=(i<<1))
            for(int k=0,w=1;k<i;k++)
            {
                int x=A[j+k],y=1ll*w*A[i+j+k]%ha;
                A[j+k]=(x+y)%ha;
                A[i+j+k]=(x-y+ha)%ha;
                w=1ll*w*wn%ha;
            }
    }
    int inv=IDFT?Pow(n,ha-2):0;
    if(IDFT) for(int i=0;i<n;i++) A[i]=1ll*A[i]*inv%ha;
}

struct Poly
{
    int* a;int n;
    void destroy(){delete a;}
    Poly(int len=0){a=new int[len];n=len;}
    int& operator [] (const int &x){return a[x];}
    Poly operator * (Poly &b)
    {
        int len=1,l=0;for(;len<n+b.n;len<<=1,l++);
        for(int i=0;i<len;i++) r[i]=(r[i>>1]>>1)|((i&1)<<l-1);
        for(int i=0;i<len;i++) A[i]=B[i]=0;
        for(int i=0;i<n;i++) A[i]=a[i];
        for(int i=0;i<b.n;i++) B[i]=b[i];
        NTT(A,len,0);NTT(B,len,0);
        for(int i=0;i<len;i++) A[i]=1ll*A[i]*B[i]%ha;
        NTT(A,len,1);Poly c(n+b.n-1);
        for(int i=0;i<n+b.n-1;i++) c[i]=A[i];
        return c;
    }
} poly[N<<1];

void divide(int o,int l,int r)
{
    if(l==r)
    {
        poly[o]=Poly(2);
        poly[o][0]=1;
        poly[o][1]=ha-v[l];
        return;
    }
    int mid=(l+r)/2;
    divide(o<<1,l,mid);
    divide(o<<1|1,mid+1,r);
    poly[o]=poly[o<<1]*poly[o<<1|1];
    poly[o<<1].destroy();
    poly[o<<1|1].destroy();
}

int main()
{
    for(int i=1,l=0;i<N;i<<=1,l++)
    {
        gpw[l]=Pow(3,(ha-1)/(i<<1));
        igpw[l]=Pow(gpw[l],ha-2);
    }
    n=read();k=read();
    for(int i=1;i<=k;i++) v[i]=read();
    for(int i=1;i<=k;i++) f[i]=read();
    divide(1,1,k);
    for(int i=0;i<poly[1].n;i++)
        poly[1][i]=ha-poly[1][i];
    for(int i=k+1;i<=n;f[i++]%=ha)
        for(int j=1;j<=k;j++)
        {
            f[i]+=1ll*poly[1][j]*f[i-j];
            if(f[i]>bigha) f[i]-=bigha;
        }
    printf("%d\n",f[n]%ha);
    return 0;
}