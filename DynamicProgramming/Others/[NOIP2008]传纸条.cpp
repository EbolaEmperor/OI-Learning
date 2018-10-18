#include<iostream>
#include<cstdio>
using namespace std;

class ty
{
    private:
        int m,n;
        int matrix[53][53];
        int dp[53][53][53][53];
        int max(int a,int b){return (a>b)?a:b;}
    
    public:
        int ans;
        void read()
        {
            cin>>m>>n;
            for(int i=1;i<=m;i++)
                for(int j=1;j<=n;j++)
                    scanf("%d",&matrix[i][j]);
        }
        void init()
        {
            for(int i=1;i<=m;i++)
                for(int j=1;j<=n;j++)
                    for(int ii=1;ii<=m;ii++)
                        for(int jj=1;jj<=n;jj++)
                            dp[i][j][ii][jj]=0;
        }
        void work()
        {
            for(int i=1;i<=m;i++)
                for(int j=1;j<=n;j++)
                    for(int ii=1;ii<=m;ii++)
                        for(int jj=1;jj<=n;jj++)
                        {
                            dp[i][j][ii][jj]=max(max(dp[i-1][j][ii-1][jj],dp[i][j-1][ii-1][jj]),max(dp[i-1][j][ii][jj-1],dp[i][j-1][ii][jj-1]))+matrix[i][j]+matrix[ii][jj];
                            if(i==ii&&j==jj) dp[i][j][ii][jj]-=matrix[i][j];
                        }
            ans=dp[m][n][m][n];
        }
} t;

int main()
{
    t.read();
    t.init();
    t.work();
    cout<<t.ans<<endl;
    return 0;
}
