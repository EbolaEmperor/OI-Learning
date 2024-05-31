#include<bits/stdc++.h>
using namespace std;

const int N = 100010;

int LIS(int *a,int n)
{
    int ans=0;
    static int g[N];
    for(int i=1;i<=n;i++) g[i]=0x7fffffff;
    for(int i=1;i<=n;i++)
    {
        int p=lower_bound(g+1,g+1+n,a[i])-(g+1);
        ans=max(ans,p+1);
        g[p+1]=min(g[p+1],a[i]);
    }
    return ans;
}

int LCS(int *a, int *b, int n){
    static int tmp[N], c[N];
    for(int i=1;i<=n;i++) tmp[b[i]]=i;
    for(int i=1;i<=n;i++) c[i]=tmp[a[i]];
    return LIS(c,n);
}

int main()
{
    static int a[N],b[N];
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    for(int i=1;i<=n;i++) scanf("%d",b+i);
    cout<<LCS(a,b,n)<<endl;
    return 0;
}
