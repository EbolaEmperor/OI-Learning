#include<bits/stdc++.h>
using namespace std;

const int N=110;
double mat[N][N][N],g[N][N];
int n,m,X,Y;

void gauss()
{
    for(int i=0;i<m;i++)
    {
        int p=i;
        while(g[p][i]==0) p++;
        for(int j=0;j<=m;j++) swap(g[i][j],g[p][j]);
        for(int j=0;j<m;j++)
        {
            if(i==j) continue;
            double t=g[j][i]/g[i][i];
            for(int k=i;k<=m;k++)
                g[j][k]-=g[i][k]*t;
        }
    }
}

int main()
{
    scanf("%d%d%d%d",&n,&m,&X,&Y);
    for(int i=0;i<m;i++) mat[n][i][i]=1;
    for(int i=n-1;i>X;i--)
    {
        double d=0.5;
        for(int j=0;j<m;j++,d*=0.5)
            for(int k=0;k<=m;k++)
                mat[i][0][k]+=d*mat[i+1][j][k];
        d*=2;mat[i][0][m]+=2.0-d*2.0;
        for(int k=0;k<=m;k++)
            mat[i][m][k]=(mat[i][0][k]*=1.0/(1.0-d));
        for(int j=m-1;j>0;j--)
        {
            for(int k=0;k<=m;k++)
                mat[i][j][k]+=0.5*(mat[i][j+1][k]+mat[i+1][j][k]);
            mat[i][j][m]+=1.0;
        }
    }
    for(int i=Y-1;i>=0;i--)
    {
        for(int k=0;k<=m;k++)
            mat[X][i][k]+=0.5*(mat[X][i+1][k]+mat[X+1][i][k]);
        mat[X][i][m]+=1.0;
    }
    for(int k=0;k<=m;k++)
        mat[X][m][k]=mat[X][0][k];
    for(int i=m-1;i>Y;i--)
    {
        for(int k=0;k<=m;k++)
            mat[X][i][k]+=0.5*(mat[X][i+1][k]+mat[X+1][i][k]);
        mat[X][i][m]+=1.0;
    }
    for(int i=X-1;i>=0;i--)
    {
        double d=0.5;
        for(int j=0;j<m;j++,d*=0.5)
            for(int k=0;k<=m;k++)
                mat[i][0][k]+=d*mat[i+1][j][k];
        d*=2;mat[i][0][m]+=2.0-d*2.0;
        for(int k=0;k<=m;k++)
            mat[i][m][k]=(mat[i][0][k]*=1.0/(1.0-d));
        for(int j=m-1;j>0;j--)
        {
            for(int k=0;k<=m;k++)
                mat[i][j][k]+=0.5*(mat[i][j+1][k]+mat[i+1][j][k]);
            mat[i][j][m]+=1.0;
        }
    }
    memcpy(g,mat[0],sizeof(g));
    for(int k=0;k<m;k++) g[k][k]-=1.0;
    gauss();
    printf("%.6lf\n",-g[0][m]/g[0][0]);
    return 0;
}
