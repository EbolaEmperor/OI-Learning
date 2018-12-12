#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=15;
int a[N][N],b[N][N];
int pos[N],n,m;
unordered_map<LL,int> f;

int decode(LL stu)
{
    int cnt=0;
    for(int i=n;i>=1;i--)
        pos[i]=stu&15,stu>>=4,cnt+=pos[i];
    return cnt&1;
}

LL compress()
{
    LL stu=0;
    for(int i=1;i<=n;i++)
        stu=stu<<4|pos[i];
    return stu;
}

int dfs(LL stu)
{
    if(f.count(stu)) return f[stu];
    int op=decode(stu);
    int ans=op?INT_MAX:-INT_MAX;
    for(int i=1;i<=n;i++)
    {
        if(pos[i]>=pos[i-1]) continue;
        pos[i]++;
        LL nxt=compress();
        if(op) ans=min(ans,dfs(nxt)-b[i][pos[i]]);
        else ans=max(ans,dfs(nxt)+a[i][pos[i]]);
        pos[i]--;
    }
    return f[stu]=ans;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",a[i]+j);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            scanf("%d",b[i]+j);
    LL mx=0;
    for(int i=1;i<=n;i++)
        mx=mx<<4|m;
    f[mx]=0;pos[0]=m;
    int ans=dfs(0);
    printf("%d\n",ans);
    return 0;
}