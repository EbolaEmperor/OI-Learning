#include<bits/stdc++.h>
using namespace std;

const int ha=1000000007;
int n,m,K,f[35][35][520];
int add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int main()
{
    scanf("%d%d%d",&n,&m,&K);
    f[1][0][0]=1;
    for(int i=2;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
            for(int s=0;s<(1<<K+1);s+=2)
                f[i][j][s>>1]=f[i-1][j][s];
        for(int k=1;k<=K&&k<i;k++)
            for(int j=0;j<m;j++)
                for(int s=0;s<(1<<K+1);s++)
                    add(f[i][j+1][s^(1<<K)^(1<<K-k)],f[i][j][s]);
    }
    int ans=0;
    cout<<f[n][m][0]<<endl;
    return 0;
}