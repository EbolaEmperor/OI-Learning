#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;

struct Matrix
{
    int n,m,a[5][5];
    Matrix(int _n=0,int _m=0):n(_n),m(_m){memset(a,0,sizeof(a));}
    int* operator [] (const int &x){return a[x];}
    Matrix operator * (Matrix &b)
    {
        Matrix c(n,b.m);
        for(int i=0;i<n;i++)
            for(int j=0;j<b.m;j++)
                for(int k=0;k<m;k++)
                    c[i][j]=(c[i][j]+1ll*a[i][k]*b[k][j])%ha;
        return c;
    }
    friend Matrix operator ^ (Matrix a,int b)
    {
        Matrix ans(a.n,a.n);
        for(int i=0;i<a.n;i++) ans[i][i]=1;
        for(;b;b>>=1,a=a*a)
            if(b&1) ans=ans*a;
        return ans;
    }
} A,B;

int main()
{
    int T,n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        if(n<=2){puts("0");continue;}
        A=Matrix(5,5);
        A[0][0]=1;A[0][1]=1;A[0][4]=2;
        A[1][0]=1;A[2][2]=1;A[2][3]=1;
        A[3][2]=1;A[4][2]=1;A[4][4]=1;
        B=Matrix(5,1);
        B[2][0]=1;B[3][0]=1;B[4][0]=1;
        A=A^(n-2);B=A*B;
        printf("%d\n",B[0][0]);
    }
    return 0;
}
// 令g[i]表示长度为i时的答案，f[i]表示斐波那契数列第i项，s表示f的前缀和
// 显然有g[i]=g[i-1]+g[i-2]+2*s[i-3]，矩阵加速即可 
