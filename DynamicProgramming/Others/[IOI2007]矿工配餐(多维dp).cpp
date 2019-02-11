#include<bits/stdc++.h>
using namespace std;

char s[100010];
int f[2][4][4][4][4];
int n,ans=0;

void update(int x,int &y,int a1,int a2,int c)
{
    if(x<0) return;
    int res=0;
    if(a1==a2&&a2==c) res=1;
    else if(a1==a2||a2==c||a1==c) res=2;
    else res=3;
    if(!a1||!a2) res--;
    y=max(y,x+res);
}

int main()
{
    scanf("%d%s",&n,s);
    memset(f[0],-1,sizeof(f[0]));
    f[0][0][0][0][0]=0;
    for(int i=0,k=0,c;i<n;i++,k^=1)
    {
        if(s[i]=='M') c=1;
        if(s[i]=='F') c=2;
        if(s[i]=='B') c=3;
        memset(f[k^1],-1,sizeof(f[k^1]));
        for(int a1=0;a1<4;a1++)for(int a2=0;a2<4;a2++)
            for(int b1=0;b1<4;b1++)for(int b2=0;b2<4;b2++)
            {
                update(f[k][a1][a2][b1][b2],f[k^1][a2][c][b1][b2],a1,a2,c);
                update(f[k][a1][a2][b1][b2],f[k^1][a1][a2][b2][c],b1,b2,c);
            }
    }
    for(int a1=0;a1<4;a1++)for(int a2=0;a2<4;a2++)
        for(int b1=0;b1<4;b1++)for(int b2=0;b2<4;b2++)
            ans=max(ans,f[n&1][a1][a2][b1][b2]);
    printf("%d\n",ans);
    return 0;
}