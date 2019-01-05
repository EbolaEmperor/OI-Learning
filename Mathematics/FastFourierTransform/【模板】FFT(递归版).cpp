#include<bits/stdc++.h>
#define vec vector<Comp>
#define pb push_back
using namespace std;

const double pi=acos(-1);
struct Comp  //复数运算类
{
    double r,i;
    Comp(double x=0,double y=0):r(x),i(y){}
    friend Comp operator + (Comp a,Comp b){return Comp(a.r+b.r,a.i+b.i);}
    friend Comp operator - (Comp a,Comp b){return Comp(a.r-b.r,a.i-b.i);}
    friend Comp operator * (Comp a,Comp b){return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
};

vec A,B,C;

vec FFT(vec a,int v)  //v=1时，进行DFT；v=-1时，进行IDFT
{
    int n=a.size();
    if(n==1) return a;  //多项式只剩1项时，点值等于常数项
    vec a1,a2;
    for(int i=0;i<n;i++)  //将f按奇偶项拆分成两个多项式
        if(i&1) a2.pb(a[i]);
        else a1.pb(a[i]);
    a1=FFT(a1,v);a2=FFT(a2,v);  //递归处理子问题
    Comp wn=Comp(cos(2*pi/n),v*sin(2*pi/n));  //DFT时求出w(n,1)，IDFT时求出w(n,-1)
    Comp w=Comp(1,0);  //这是w(n,0)
    for(int i=0;i<n/2;i++)
    {
        Comp x=a1[i],y=a2[i];
        a[i]=x+w*y;  //这一步的推导过程在课件的第29页
        a[n/2+i]=x-w*y;
        w=w*wn;  //w(n,k+1)=w(n,k)*w(n,1)，IDFT同理
    }
    return a;
}

int main()
{
    int n,m;double x;
    scanf("%d%d%d",&n,&m);
    for(int i=0;i<=n;i++)
    {
        scanf("%lf",&x);
        A.pb(Comp(x,0));
    }
    for(int i=0;i<=m;i++)
    {
        scanf("%lf",&x);
        B.pb(Comp(x,0));
    }
    int now=1;
    while(now<=n+m) now<<=1;
    for(int i=n+1;i<now;i++) A.pb(Comp(0,0));  //高次项补0
    for(int i=m+1;i<now;i++) B.pb(Comp(0,0));
    A=FFT(A,1);B=FFT(B,1);
    for(int i=0;i<now;i++) C.pb(A[i]*B[i]);  //点值直接相乘
    C=FFT(C,-1);
    for(int i=0;i<=n+m;i++) printf("%d ",(int)round(C[i].r/now));  //逆变换的最后一步要除以n
    return 0;
}
