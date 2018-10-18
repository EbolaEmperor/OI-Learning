#include<bits/stdc++.h>
#define ha 313
using namespace std;

const double pi=acos(-1);
struct Comp
{
    double r,i;
    Comp(double _r=0,double _i=0):r(_r),i(_i){}
    Comp operator + (const Comp &a){return Comp(r+a.r,i+a.i);}
    Comp operator - (const Comp &a){return Comp(r-a.r,i-a.i);}
    Comp operator * (const Comp &a){return Comp(r*a.r-i*a.i,r*a.i+i*a.r);}
};

const int N=300010;
int f[N],a[N],r[N];
Comp A[N],B[N];

void FFT(Comp *A,int n,int v)
{
    for(int i=0;i<n;i++) if(i<r[i]) swap(A[i],A[r[i]]);
    for(int i=1;i<n;i<<=1)
    {
        Comp wn(cos(pi/i),v*sin(pi/i));
        for(int j=0;j<n;j+=(i<<1))
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
}

void CDQ(int L,int R)
{
    if(L==R){f[L]=(f[L]+a[L])%ha;return;}
    int M=(L+R)/2;CDQ(L,M);
    int len=1,l=0;for(;len<=R-L+1;len<<=1,l++);
    for(int i=0;i<len;i++) A[i]=B[i]=Comp(0,0);
    for(int i=0;i<=M-L;i++) A[i]=Comp(f[i+L],0);
    for(int i=0;i<=R-L;i++) B[i]=Comp(a[i],0);
    for(int i=0;i<len;i++) r[i]=(r[i>>1]>>1)|((i&1)<<l-1);
    FFT(A,len,1);FFT(B,len,1);
    for(int i=0;i<len;i++) A[i]=A[i]*B[i];
    FFT(A,len,-1);
    for(int i=M+1;i<=R;i++) f[i]=(f[i]+int(round(A[i-L].r/len)))%ha;
    CDQ(M+1,R);
}

int main()
{
    int n;
    while(~scanf("%d",&n)&&n)
    {
        memset(f,0,sizeof(f));
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++)
            scanf("%d",a+i),a[i]%=ha;
        CDQ(1,n);
        printf("%d\n",f[n]);
    }
    return 0;
}