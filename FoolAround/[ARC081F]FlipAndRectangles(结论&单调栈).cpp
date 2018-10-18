#include<bits/stdc++.h>
using namespace std;

const int N=2010;
bool mp[N][N],good[N][N];
int deep[N][N];
int L[N],R[N];
int s[N],top;
char ss[N];
int H,W,ans=0;

int main()
{
    scanf("%d%d",&H,&W);
    for(int i=1;i<=H;i++)
    {
        scanf("%s",ss+1);
        for(int j=1;j<=W;j++)
            mp[i][j]=(ss[j]=='#');
    }
    for(int i=1;i<H;i++)
        for(int j=1;j<W;j++)
        {
            int cnt=mp[i][j]+mp[i+1][j]+mp[i][j+1]+mp[i+1][j+1];
            good[i][j]=!(cnt&1);
        }
    for(int i=1;i<=H;i++)
        for(int j=1;j<=W;j++)
            deep[i][j]=good[i][j]?deep[i-1][j]+1:0;
    for(int i=1;i<=H;i++)
    {
        s[top=1]=0;
        for(int j=1;j<W;j++)
        {
            while(top&&deep[i-1][s[top]]>=deep[i-1][j]) top--;
            L[j]=s[top];s[++top]=j;
        }
        s[top=1]=W;
        for(int j=W-1;j>=1;j--)
        {
            while(top&&deep[i-1][s[top]]>=deep[i-1][j]) top--;
            R[j]=s[top];s[++top]=j;
        }
        for(int j=1;j<W;j++)
            ans=max(ans,(deep[i-1][j]+1)*(R[j]-L[j]));
    }
    ans=max(ans,max(H,W));
    printf("%d\n",ans);
    return 0;
}