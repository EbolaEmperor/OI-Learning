#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=10007;
const int N=305;
int f[N][N][N],g[N];
char s[N];
int n;

struct Matrix
{
    int a[N][N],n;
    Matrix(int _n=0):n(_n){memset(a,0,sizeof(a));}
    int* operator [] (const int &x){return a[x];}
    Matrix operator * (Matrix &b)
    {
        Matrix res(n);
        for(int i=1;i<=n;i++)
            for(int j=i;j<=n;j++)
            {
                LL qwq=0;
                for(int k=i;k<=j;k++)
                    qwq+=a[i][k]*b[k][j];
                res[i][j]=qwq%ha;
            }
        return res;
    }
    friend Matrix operator ^ (Matrix a,int b)
    {
        Matrix res(a.n);
        for(int i=1;i<=res.n;i++) res[i][i]=1;
        for(;b;b>>=1,a=a*a) if(b&1) res=res*a;
        return res;
    }
} mat;

void dp()
{
    int len=strlen(s+1);
    f[1][len][0]=1;
    for(int l=1;l<=len;l++)
        for(int r=len;r>=l;r--)
            for(int k=0;k<=len;k++)
                if(s[l]!=s[r])
                {
                    (f[l+1][r][k+1]+=f[l][r][k])%=ha;
                    (f[l][r-1][k+1]+=f[l][r][k])%=ha;
                }
                else (f[l+1][r-1][k]+=f[l][r][k])%=ha;
    for(int i=1;i<=len;i++)
        for(int k=0;k<=len;k++)
        {
            (g[k]+=f[i][i][k])%=ha;
            if(s[i]==s[i+1]) (g[k]+=f[i][i+1][k])%=ha;
        }
}

int main()
{
    scanf("%s%d",s+1,&n);dp();
    int len=strlen(s+1),m=len+n,t=(len+1)/2;
    mat=Matrix(len+t+1);
    for(int i=1;i<=len;i++)
    {
        mat[i][i]=24;
        if(i<len) mat[i][i+1]=1;
        mat[i][len+t+1-(len-i+1)/2]=g[i];
    }
    for(int i=1;i<=t;i++) mat[len+i][len+i+1]=1,mat[len+i][len+i]=25;
    mat[len+t+1][len+t+1]=26;
    if(m&1)
    {
        mat=mat^((m+1)/2);
        int ans=(mat[1][len+t+1]+mat[len+1][len+t+1]*g[0])%ha;
        memset(g,0,sizeof(g));
        mat=Matrix(len+t+1);
        for(int i=1;i<=len;i++)
            for(int k=0;k<=len;k++)
                if(s[i]==s[i+1]) (g[k]+=f[i][i+1][k])%ha;
        for(int i=1;i<=len;i++)
        {
            mat[i][i]=24;
            if(i<len) mat[i][i+1]=1;
            mat[i][len+t+1-(len-i+1)/2]=g[i];
        }
        for(int i=1;i<=t;i++) mat[len+i][len+i+1]=1,mat[len+i][len+i]=25;
        mat=mat^((m+1)/2);
        ans=(ans-(mat[1][len+t+1]+mat[len+1][len+t+1]*g[0])%ha+ha)%ha;
        printf("%d\n",ans);
    }
    else
    {
        mat=mat^(m/2);
        int ans=(mat[1][len+t+1]+mat[len+1][len+t+1]*g[0])%ha;
        printf("%d\n",ans);
    }
    return 0;
}