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

const int N=6010,M=610;
int p[N][M],n,m;
double a[N],b[N],f[M][N],sum[N];

void mul(double *A,int n,int x)
{
    double p=(double)x/1000.0,q=1-p;
    for(int i=n+1;i>0;i--)
        A[i]=A[i-1]*p+A[i]*q;
    A[0]=A[0]*q;
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            p[i][j]=read();
    for(int i=1;i<=m;i++)
    {
        memset(a,0,sizeof(a));
        int len=0;a[0]=1;
        for(int j=1;j<=n;j++)
        {
            mul(a,len,p[j][i]);
            if(a[len+1]>1e-11) len++;
        }
        memset(b,0,sizeof(b));
        memset(sum,0,sizeof(sum));
        for(int j=len;j>=1;j--) b[j]=b[j+1]+a[j];
        for(int j=1;j<=len;j++) sum[j]=sum[j-1]+a[j]*j;
        for(int j=1;j<=len;j++) b[j]=b[j]*j+sum[j-1];
        for(int j=0;j<=n;j++)
            for(int k=0;k<=len;k++)
                f[i][j+k]=max(f[i][j+k],f[i-1][j]+b[k]);
    }
    printf("%.10lf\n",f[m][n]);
    return 0;
}