#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=810;
int mat[N][N],n;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

bool get_inv()
{
    for(int i=1;i<=n;i++)
        mat[i][n+i]=1;
    for(int i=1;i<=n;i++)
    {
        int p=i;
        while(p<=n&&!mat[p][i]) p++;
        if(p>n) return 0;
        for(int j=1;j<=2*n;j++)
            swap(mat[i][j],mat[p][j]);
        int inv=Pow(mat[i][i],ha-2);
        for(int j=1;j<=2*n;j++)
            mat[i][j]=1ll*mat[i][j]*inv%ha;
        for(int j=1;j<=n;j++)
        {
            if(i==j) continue;
            int t=mat[j][i];
            for(int k=1;k<=2*n;k++)
                mat[j][k]=(mat[j][k]-1ll*t*mat[i][k]%ha+ha)%ha;
        }
    }
    return 1;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%d",mat[i]+j);
    bool flag=get_inv();
    if(!flag) return puts("No Solution"),0;
    for(int i=1;i<=n;i++,puts(""))
        for(int j=1;j<=n;j++)
            printf("%d ",mat[i][n+j]);
    return 0;
}