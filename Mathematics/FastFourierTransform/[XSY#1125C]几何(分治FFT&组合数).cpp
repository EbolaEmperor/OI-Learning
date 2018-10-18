#include<bits/stdc++.h>
#define ha 100003
#define double long double
using namespace std;

const double pi=acos(-1);
const int N=60010,M=150010;
int r[M],*P[N<<2];
int good[N],desk[N];
int fac[ha],ifac[ha];

struct Comp
{
    double r,i;
    Comp(double _r=0.0,double _i=0.0):r(_r),i(_i){}
    Comp operator + (const Comp &a){return Comp(r+a.r,i+a.i);}
    Comp operator - (const Comp &a){return Comp(r-a.r,i-a.i);}
    Comp operator * (const Comp &a){return Comp(r*a.r-i*a.i,r*a.i+i*a.r);}
} A[M],B[M];

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

int divide(int o,int L,int R)
{
    if(L==R)
    {
        P[o]=new int[2];
        P[o][0]=desk[L];
        P[o][1]=1;
        return 2;
    }
    int M=(L+R)/2;
    int nl=divide(o<<1,L,M);
    int nr=divide(o<<1|1,M+1,R);
    int l=0,len=1;for(;len<nl+nr-1;len<<=1,l++);
    for(int i=0;i<len;i++) r[i]=(r[i>>1]>>1)|((i&1)<<l-1);
    for(int i=0;i<nl;i++) A[i]=Comp(P[o<<1][i],0);
    for(int i=0;i<nr;i++) B[i]=Comp(P[o<<1|1][i],0);
    for(int i=nl;i<len;i++) A[i]=Comp(0,0);
    for(int i=nr;i<len;i++) B[i]=Comp(0,0);
    FFT(A,len,1);FFT(B,len,1);
    for(int i=0;i<len;i++) A[i]=A[i]*B[i];
    FFT(A,len,-1);P[o]=new int[nl+nr-1];
    for(int i=0;i<nl+nr-1;i++) P[o][i]=llround(A[i].r)%ha;
    delete P[o<<1],P[o<<1|1];
    return nl+nr-1;
}

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void Init()
{
    fac[0]=1;
    for(int i=1;i<ha;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[ha-1]=Pow(fac[ha-1],ha-2);
    for(int i=ha-2;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

int C(int n,int m){return n<m?0:1ll*fac[n]*ifac[m]*ifac[n-m]%ha;}
int Lucas(int n,int m)
{
    if(n<ha&&m<ha) return C(n,m);
    return 1ll*Lucas(n/ha,m/ha)*C(n%ha,m%ha)%ha;
}

void prework(int n)
{
    good[3]=42;
    for(int i=3;i<n;i++)
    {
        int sum=good[i];
        for(int j=0;j<6;j++)
            sum=(2*sum+Lucas(6*i-12+j,i-1))%ha;
        good[i+1]=(sum-Lucas(6*i-6,i)+ha)%ha;
    }
    desk[1]=9;
    for(int i=2;i<=n;i++)
    {
        int sum=0,cur=good[i];
        for(int a=0;a<=4;a++)
        {
            sum=(sum+1ll*Lucas(4,a)*Pow(3,a)*cur)%ha;
            cur=(cur+Lucas(6*i-12,i-a-1))%ha;
        }
        desk[i]=sum;
    }
}

int main()
{
    int T,n,k;Init();
    for(cin>>T;T;T--)
    {
        cin>>n>>k;
        prework(n);
        divide(1,1,n);
        int ans=0;
        for(int i=0;i<=n-k;i++)
            if((ans+=P[1][i])>=ha) ans-=ha;
        cout<<ans<<endl;
        delete P[1];
    }
    return 0;
}