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
const int N=300010;
const double pi=acos(-1);
struct Comp
{
    double r,i;
    Comp(double _r=0,double _i=0):r(_r),i(_i){}
    Comp operator + (const Comp &a){return Comp(r+a.r,i+a.i);}
    Comp operator - (const Comp &a){return Comp(r-a.r,i-a.i);}
    Comp operator * (const Comp &a){return Comp(r*a.r-i*a.i,r*a.i+i*a.r);}
} A[N],B[N];
int r[N],n,K;
int X[N],Y[N];
LL sumx[N],sumy[N];
LL sum2x[N],sum2y[N];
LL xy[N];

void FFT(Comp *A,int n,int v)
{
    for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1;i<n;i<<=1)
    {
        Comp wn(cos(pi/i),sin(pi/i)*v);
        for(int j=0;j<n;j+=i<<1)
        {
            Comp w(1,0);
            for(int k=0;k<i;k++)
            {
                Comp x=A[j+k],y=w*A[i+j+k];
                A[j+k]=x+y;
                A[i+j+k]=x-y;
                w=w*wn;
            }
        }
    }
    if(v==-1) for(int i=0;i<n;i++) A[i].r/=n;
}

int main()
{
    for(int T=read();T;T--)
    {
        n=read();K=read();
        for(int i=1;i<=K;i++) X[i]=read();
        for(int i=1;i<=K;i++) Y[i]=read();
        for(int i=1;i<=K;i++) Y[i+K]=Y[i]+n;
        //Perwork1: presum of x,y,x2,y2
        memset(sumx,0,sizeof(sumx));
        memset(sumy,0,sizeof(sumy));
        memset(sum2x,0,sizeof(sum2x));
        memset(sum2y,0,sizeof(sum2y));
        for(int i=1;i<=2*K;i++)
        {
            sumx[i]=sumx[i-1]+X[i];
            sumy[i]=sumy[i-1]+Y[i];
            sum2x[i]=sum2x[i-1]+X[i]*X[i];
            sum2y[i]=sum2y[i-1]+Y[i]*Y[i];
        }
        //prework2: xy[s]=sigma{x[i]*y[i+s]}
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        for(int i=0;i<K;i++) A[i].r=X[i+1];
        for(int i=0;i<2*K;i++) B[i].r=Y[2*K-i];
        int l=0,len=1;for(;len<2*K;len<<=1,l++);
        for(int i=0;i<len;i++) r[i]=(r[i>>1]>>1)|((i&1)<<l-1);
        FFT(A,len,1);FFT(B,len,1);
        for(int i=0;i<len;i++) A[i]=A[i]*B[i];
        FFT(A,len,-1);
        for(int i=0;i<K;i++) xy[i]=(LL)round(A[2*K-i-1].r);
        //get answer in O(K)
        LL ans=1ll<<60;
        for(int i=0;i<K;i++)
        {
            LL c=sum2x[K]+sum2y[K+i]-sum2y[i]-2*xy[i];
            LL b=(sumx[K]-sumy[K+i]+sumy[i])*2;
            LL a=K,x=b/(-2*a);
            ans=min(ans,a*x*x+b*x+c);
            x++;ans=min(ans,a*x*x+b*x+c);
            x-=2;ans=min(ans,a*x*x+b*x+c);
        }
        printf("%lld\n",ans);
    }
    return 0;
}