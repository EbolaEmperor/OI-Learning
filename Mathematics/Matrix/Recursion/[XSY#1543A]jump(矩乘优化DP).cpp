#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=1e9+7;
const LL INF=(LL)ha*ha;
const int N=210;
int n,m,K,a[N],dta[N];

struct Matrix
{
    int a[N][N];
    Matrix(){memset(a,0,sizeof(a));}
    int* operator [] (const int &x){return a[x];}
    Matrix operator * (Matrix &B)
    {
        Matrix C;
        for(int i=1;i<=2*K+2;i++)
            for(int j=1;j<=2*K+2;j++)
            {
                LL res=0;
                for(int k=1;k<=2*K+1;k++)
                {
                    res+=(LL)a[i][k]*B[k][j];
                    if(res>INF) res-=INF;
                    if(res<0) res+=INF;
                }
                C[i][j]=res%ha;
            }
        return C;
    }
    friend Matrix operator ^ (Matrix A,int b)
    {
        Matrix ans;
        for(int i=1;i<=2*K+2;i++) ans[i][i]=1;
        for(;b;b>>=1,A=A*A)
            if(b&1) ans=ans*A;
        return ans;
    }
} A;

int sum(int l,int r){return 1ll*(l+r)*(r-l+1)/2%ha;}

bool check(int x)
{
    static bool g[N];
    memset(g,0,sizeof(g));
    for(int i=1;i<=x;i++)
    {
        if(dta[i]<dta[1]) continue;
        g[i]=1;
        for(int j=2;j<x;j++)
        {
            if(dta[i+j-1]!=dta[j]) break;
            g[i+j-1]=1;
        }
    }
    return !g[x];
}

int main()
{
    scanf("%d%d%d",&K,&m,&n);
    for(int i=1;i<=K;i++) scanf("%d",a+i);
    for(int i=1;i<=K;i++) dta[i]=a[i]-a[i-1];
    for(int i=1;i<=K;i++) A[i][i+1]=A[i+K+1][i+K+2]=1;
    for(int i=1;i<=K;i++)
    {
        if(i>1&&!check(i)) continue;
        A[i][1]=A[i+K+1][1+K+1]=m-a[1]+1;
        A[i+K+1][1]=sum(a[i],(a[i]+m-a[1])%ha);
    }
    A=A^n;
    printf("%d\n",A[1+K+1][1]);
    return 0;
}