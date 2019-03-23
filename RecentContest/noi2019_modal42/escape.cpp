#include<bits/stdc++.h>
using namespace std;

const int N=1010;
int f[N][N*20],n,m,r,a[N],b[N];

inline void upmax(int &x,const int &y){if(y>x) x=y;}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
        scanf("%d%d",a+i,b+i),upmax(r,a[i]+b[i]);
    for(int i=1;i<m;i++) f[1][i]=i;
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<a[i];j++) upmax(f[i+1][j+b[i]],f[i][j]+b[i]);
        for(int j=a[i];j<a[i]+b[i];j++) upmax(f[i+1][j-a[i]],f[i][j]);
        for(int j=a[i]+b[i];j<=r;j++) upmax(f[i+1][j],f[i][j]);
        int mx=0;
        for(int j=0;j<a[i];j++) upmax(mx,f[i][j]);
        for(int j=0;j<b[i];j++) upmax(f[i+1][j],mx+j);
    }
    int ans=m-1;
    for(int j=0;j<=r;j++)
        upmax(ans,f[n][j]);
    printf("%d\n",ans);
    return 0;
}