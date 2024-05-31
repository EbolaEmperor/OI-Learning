#include<iostream>
using namespace std;

const int N = 2010;
int dp[N][N],a1[N],a2[N],n,m;

int main()
{
   cin>>n>>m;
   for(int i=1;i<=n;i++)scanf("%d",&a1[i]);
   for(int i=1;i<=m;i++)scanf("%d",&a2[i]);
   for(int i=1;i<=n;i++)
   for(int j=1;j<=m;j++)
   {
     	dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
     	if(a1[i]==a2[j]) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
   }
   cout<<dp[n][m];
}
