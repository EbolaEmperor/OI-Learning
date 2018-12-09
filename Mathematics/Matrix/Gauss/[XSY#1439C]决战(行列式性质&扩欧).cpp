#include<bits/stdc++.h>
using namespace std;

int n,h[7],ans[7][7],fg=1;

int exgcd(int a,int b,int &x,int &y)
{
    if(b==0){x=1;y=0;return a;}
    int g=exgcd(b,a%b,x,y);
    int t=x;x=y;y=t-(a/b)*y;
    return g;
}

void swapc(int a,int b)
{
    for(int i=2;i<=n;i++)
        swap(ans[i][a],ans[i][b]);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",h+i);
    int a,b,x,y;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            if(__gcd(h[i],h[j])==1) a=i,b=j;
    if(a==2) swap(a,b);
    if(a!=1) fg=-fg;
    if(b!=2) fg=-fg;
    int g=exgcd(h[a],-h[b],y,x);
    if(fg!=g) x=-x,y=-y,g=-g;
    ans[2][1]=x;ans[2][2]=y;
    ans[3][3]=ans[4][4]=ans[5][5]=1;
    swapc(1,a);swapc(2,b);
    for(int i=1;i<=n;i++) printf("%d ",h[i]);puts("");
    for(int i=2;i<=n;i++,puts(""))
        for(int j=1;j<=n;j++)
            printf("%d ",ans[i][j]);
    return 0;
}