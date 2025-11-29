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
const int N=5010,M=210;
int L[M][N],R[M][N];
int B[M][N],n,m;
int stk[N],w[N],top;
LL a[N],mat[N][N];

int main()
{
    n=read();m=read();
    for(int i=2;i<=n;i++)
        a[i]=a[i-1]+read();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            B[j][i]=read();
    for(int i=1;i<=m;i++)
    {
        top=0;
        for(int j=1;j<=n;j++)
        {
            while(top&&w[top]<B[i][j]) top--;
            L[i][j]=top?stk[top]+1:1;
            stk[++top]=j;w[top]=B[i][j];
        }
        top=0;
        for(int j=n;j>=1;j--)
        {
            while(top&&w[top]<B[i][j]) top--;
            R[i][j]=top?stk[top]-1:n;
            stk[++top]=j;w[top]=B[i][j];
        }
        for(int j=1;j<=n;j++)
        {
            mat[L[i][j]][j]+=B[i][j];
            mat[L[i][j]][R[i][j]+1]-=B[i][j];
            mat[j+1][j]-=B[i][j];
            mat[j+1][R[i][j]+1]+=B[i][j];
        }
    }
    LL ans=0;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++) mat[i][j]+=mat[i][j-1];
        for(int j=1;j<=n;j++) mat[i][j]+=mat[i-1][j];
        for(int j=i;j<=n;j++) ans=max(ans,mat[i][j]-a[j]+a[i]);
    }
    printf("%lld\n",ans);
    return 0;
}