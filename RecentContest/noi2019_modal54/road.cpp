#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7,N=55;
int n,k,q,t;
int C[N][N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

struct Matrix
{
    int a[N][N];
    Matrix(){memset(a,0,sizeof(a));}
    int* operator [] (const int &x){return a[x];}
    Matrix operator * (const Matrix &b)
    {
        Matrix c;
        for(int i=0;i<n;i++)
            for(int k=0;k<n;k++)
                for(int j=0;j<n;j++)
                    c.a[i][j]=(c.a[i][j]+1ll*a[i][k]*b.a[k][j])%ha;
        return c;
    }
    Matrix operator + (const Matrix &b)
    {
        Matrix c;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                c.a[i][j]=(a[i][j]+b.a[i][j])%ha;
        return c;
    }
    Matrix operator * (const int &b)
    {
        Matrix c;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                c.a[i][j]=1ll*b*a[i][j]%ha;
        return c;
    }
    friend Matrix operator ^ (Matrix a,int b)
    {
        Matrix ans;
        for(int i=0;i<n;i++)
            ans.a[i][i]=1;
        for(;b;b>>=1,a=a*a)
            if(b&1) ans=ans*a;
        return ans;
    }
} S[30][N],pG[30],G,ans;

int main()
{
    scanf("%d%d%d%d",&n,&k,&q,&t);k--;
    for(int i=0;i<=t;i++)
        for(int j=C[i][0]=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%ha;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            scanf("%d",G[i]+j);
    for(int i=0;i<30;i++) pG[i]=G^(1<<i);
    for(int i=0;i<=t;i++) S[0][i]=G;
    for(int i=1;i<30;i++)
        for(int j=0;j<=t;j++)
        {
            for(int u=0;u<=j;u++)
                S[i][j]=S[i][j]+S[i-1][u]*(1ll*C[j][u]*Pow(1<<i-1,j-u)%ha);
            S[i][j]=S[i-1][j]+pG[i-1]*S[i][j];
        }
    ans=S[0][t];
    int cnt=1;k--;
    for(int i=29;i>=0;i--)
        if(k>=(1<<i))
        {
            Matrix tmp;
            for(int u=0;u<=t;u++)
                tmp=tmp+S[i][u]*(1ll*C[t][u]*Pow(cnt,t-u)%ha);
            ans=ans+(G^cnt)*tmp;
            k-=1<<i;
            cnt+=1<<i;
        }
    while(q--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        printf("%d\n",ans[u-1][v-1]);
    }
    return 0;
}