#include<bits/stdc++.h>
using namespace std;

const int N=2010;
int f[N][N],h[N],n,m;

int main()
{
    scanf("%d%d",&n,&m);
    static char s[N];
    for(int i=n;i>=1;i--)
    {
        scanf("%s",s+1);
        for(int j=1;j<=m;j++)
            if(s[j]=='*'&&!h[j]) h[j]=i;
    }
    memset(f,0x3f,sizeof(f));
    memset(f[0],0,sizeof(f[0]));
    for(int i=1;i<=m;i++)
        for(int j=0,k=h[i]/2;j<=h[i];j++)
            for(k=min((h[i]-j)/2,k+1);k>=0;k--)
            {
                int now=f[i-1][min(h[i-1],2*(h[i]-j-2*k)+k)]+k+(h[i]-j-2*k);
                if(now<=f[i][j]) f[i][j]=now;
                else break;
            }
    printf("%d\n",f[m][0]);
    return 0;
}