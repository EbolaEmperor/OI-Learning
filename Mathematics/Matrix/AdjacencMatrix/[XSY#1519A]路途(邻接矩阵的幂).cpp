#include<bits/stdc++.h>
using namespace std;

const int ha=2333;
const int N=45;
int n,m,Q;

struct Matrix
{
    int a[N][N];
    int* operator [] (const int &x){return a[x];}
    Matrix(){memset(a,0,sizeof(a));}
    
    Matrix operator * (Matrix &A)
    {
        Matrix res;
        for(int k=1;k<=n;k++)
            for(int i=1;i<=n;i++)
                for(int j=1;j<=n;j++)
                    res[i][j]=(res[i][j]+a[i][k]*A[k][j])%ha;
        return res;
    }

    friend Matrix operator ^ (Matrix A,int b)
    {
        Matrix ans;
        for(int i=1;i<=n;i++) ans[i][i]=1;
        for(;b;b>>=1,A=A*A)
            if(b&1) ans=ans*A;
        return ans;
    }
} T,G,gg;

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        G[u][v]++;G[v][u]++;
    }
    int s,t,l,r;
    for(scanf("%d",&Q);Q;Q--)
    {
        scanf("%d%d%d%d",&s,&t,&l,&r);
        T=G^l;gg=G;n++;
        gg[n][s]=gg[n][n]=1;
        gg=gg^(r-l+1);T=gg*T;
        printf("%d\n",T[n][t]);
        n--;
    }
    return 0;
}