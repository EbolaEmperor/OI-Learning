#include<bits/stdc++.h>
using namespace std;

const int ha=1004535809,N=110;
int C[N][N],f[N][N][N],n;
// f[i][j][k]: 考虑了前i种序号，前i种当中至多选了j种，序列长度为k

int main()
{
    scanf("%d",&n);
    for(int i=0;i<=n;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%ha;
    }
    f[0][0][0]=1;
    for(int i=1,deg;i<=n;i++)
    {
        scanf("%d",&deg);
        memcpy(f[i],f[i-1],sizeof(f[i])); // 不选i号
        for(int j=1;j<=i;j++)
            for(int k=0;k<=n;k++)
                for(int c=0;c<=k&&c<deg;c++)
                    f[i][j][k]=(f[i][j][k]+1ll*f[i-1][j-1][k-c]*C[k][c])%ha; // 选c个i号
    }
    printf("%d ",n);
    for(int i=2;i<=n;i++)
        printf("%d ",f[n][i][i-2]);
    return puts(""),0;
}