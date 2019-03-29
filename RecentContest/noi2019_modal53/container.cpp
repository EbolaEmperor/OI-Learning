#include<bits/stdc++.h>
using namespace std;

const int ha=1011110011;
const int N=45;
int f[N][N][N],n,m,t;
int C[N][N];

inline void add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int main()
{
    scanf("%d%d%d",&n,&m,&t);
    for(int i=0;i<=m;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%ha;
    }
    f[0][0][m]=1;
    for(int i=0;i<=n+1;i++)
        for(int j=0;j<=t;j++)
            for(int k=0;k<=m-j;k++)
                for(int a=0;a<=j;a++)
                    for(int b=0;b<=k;b++)
                        add(f[i+1][j-a+b][k-b],1ll*f[i][j][k]*C[j][a]%ha*C[k][b]%ha);
    printf("%d\n",f[n+1][0][0]);
    return 0;
}