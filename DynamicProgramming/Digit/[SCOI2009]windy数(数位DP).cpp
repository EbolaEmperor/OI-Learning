#include<bits/stdc++.h>
using namespace std;

int a,b,f[15][15][2],lim[15];

int solve(int n)
{
    if(!n) return 0;
    int x=n,len=0,ans=0;
    while(x) lim[len++]=x%10,x/=10;
    reverse(lim,lim+len);
    memset(f,0,sizeof(f));
    for(int i=1;i<lim[0];i++) f[0][i][0]=1;
    f[0][lim[0]][1]=1;
    for(int i=1;i<len;i++)
    {
        for(int j=1;j<10;j++) f[i][j][0]++;
        for(int k=0;k<10;k++)
        {
            for(int j=0;j<10;j++)if(abs(j-k)>=2) f[i][j][0]+=f[i-1][k][0];
            for(int j=0;j<lim[i];j++)if(abs(j-k)>=2) f[i][j][0]+=f[i-1][k][1];
            if(abs(k-lim[i])>=2) f[i][lim[i]][1]+=f[i-1][k][1];
        }
    }
    for(int i=0;i<10;i++)
        ans+=f[len-1][i][0]+f[len-1][i][1];
    return ans;
}

int main()
{
    cin>>a>>b;
    printf("%d\n",solve(b)-solve(a-1));
    return 0;
}