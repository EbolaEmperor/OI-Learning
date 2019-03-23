#include<bits/stdc++.h>
using namespace std;
 
const int ha=1e9+7;
const int N=5010;
int sumx[N][N],sumy[N][N],C[N][N],n,ty;
int ans1,ans2,ans3;
 
void prework()
{
    for(int i=0;i<=n;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%ha;
    }
    for(int x=0;x<=5000;x++)
        for(int y=1;y<=5000;y++)
            sumx[x][y]+=sumx[x][y-1];
    for(int y=0;y<=5000;y++)
        for(int x=1;x<=5000;x++)
            sumy[y][x]+=sumy[y][x-1];
}
 
void gao()
{
    for(int x=1;x<5000;x++)
        for(int y=1;y<5000;y++)
        {
            int tmp=min(min(sumx[x][y-1],sumx[x][5000]-sumx[x][y]),min(sumy[y][x-1],sumy[y][5000]-sumy[y][x]));
            if(tmp>ans1) ans1=tmp,ans2=1;
            else if(tmp==ans1) ans2++;
        }
    for(int x=1;x<5000;x++)
        for(int y=1;y<5000;y++)
        {
            int s1=sumx[x][y-1],s2=sumx[x][5000]-sumx[x][y];
            int s3=sumy[y][x-1],s4=sumy[y][5000]-sumy[y][x];
            int tmp=min(min(s1,s2),min(s3,s4));
            if(tmp<ans1) continue;
            ans3=(ans3+1ll*C[s1][tmp]*C[s2][tmp]%ha*C[s3][tmp]%ha*C[s4][tmp])%ha;
        }
}
 
int main()
{
    scanf("%d%d",&n,&ty);
    for(int i=1,x,y;i<=n;i++)
        scanf("%d%d",&x,&y),sumx[x][y]++,sumy[y][x]++;
    prework();gao();
    printf("%d ",ans1);
    if(ty>=2) printf("%d ",ans2);
    if(ty>=3) printf("%d ",ans3);
    return puts(""),0;
}