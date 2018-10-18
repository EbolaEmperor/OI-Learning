#include<bits/stdc++.h>
using namespace std;

const int N=510;
int a[N*N],X[N],n;
int c[N],cnt[N];
int pos[N][N],num[N];

bool check()
{
    for(int i=1;i<=n*n;i++)
        pos[a[i]][++num[a[i]]]=i;
    for(int i=1;i<=n;i++)
        if(pos[i][i]!=X[i]) return 0;
    return 1;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",X+i);
    for(int i=1;i<=n;i++) c[i]=i,a[X[i]]=i;
    sort(c+1,c+1+n,[](int x,int y){return X[x]<X[y];});
    for(int i=1;i<=n;i++) cnt[i]=i-1;
    for(int i=1;i<=n*n;i++)
    {
        if(a[i]) continue;
        for(int j=1;j<=n;j++)
            if(cnt[c[j]]){a[i]=c[j];cnt[c[j]]--;break;}
    }
    for(int i=1;i<=n;i++) cnt[i]=n-i;
    for(int i=n*n;i>=1;i--)
    {
        if(a[i]) continue;
        for(int j=n;j>=1;j--)
            if(cnt[c[j]]){a[i]=c[j];cnt[c[j]]--;break;}
    }
    if(check())
    {
        puts("Yes");
        for(int i=1;i<=n*n;i++)
            printf("%d ",a[i]);
    }
    else puts("No");
    return 0;
}