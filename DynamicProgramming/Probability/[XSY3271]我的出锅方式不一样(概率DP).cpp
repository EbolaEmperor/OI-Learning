#include<bits/stdc++.h>
using namespace std;

const int N=110;
double g[N][N][N],f[N][N];
double C[N<<1][N<<1];
bool vis[N][N];
int n,m,R,B;

void prework()
{
    for(int i=0;i<=200;i++)
    {
        C[i][0]=1.0;
        for(int j=1;j<=i;j++)
            C[i][j]=C[i-1][j]+C[i-1][j-1];
    }
    for(int r=1;r<=R;r++)
        for(int b=0;b<=B;b++)
        {
            g[r][b][0]=1.0;
            for(int k=1;k<=min(m,r+b);k++)
            {
                g[r][b][k]=g[r-1][b][k-1]*r/(r+b);
                if(b) g[r][b][k]+=g[r][b-1][k-1]*b/(r+b);
            }
        }
}

double dp(int r,int b)
{
    double &res=f[r][b];
    if(vis[r][b]) return res;
    vis[r][b]=1;res=0.0;
    for(int k=1;k<=min(n,r+b);k++)
    {
        double tmp=0.0;
        for(int i=max(0,k-b);i<=min(r,k);i++)
            tmp+=C[r][i]/C[r+b][k]*C[b][k-i]*(1.0-dp(r-i,b-(k-i)))*g[r-i][b-(k-i)][m]/g[r][b][m];
        res=max(res,tmp);
    }
    return res;
}

int main()
{
    cin>>R>>B>>n>>m;
    prework();
    printf("%.7lf\n",dp(R,B));
    return 0;
}