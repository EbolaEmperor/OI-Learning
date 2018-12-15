#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int a[N],n,T;
int f[N][2],pre[N][2];
stack<int> ans1,ans2;

int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        f[1][0]=0;f[1][1]=n+1;
        for(int i=2;i<=n;i++)
        {
            f[i][0]=n+1;f[i][1]=0;
            if(a[i]<a[i-1]&&f[i][0]>f[i-1][0]) f[i][0]=f[i-1][0],pre[i][0]=0;
            if(a[i-1]<f[i][0]&&a[i]<f[i-1][1]) f[i][0]=a[i-1],pre[i][0]=1;
            if(a[i]>a[i-1]&&f[i][1]<f[i-1][1]) f[i][1]=f[i-1][1],pre[i][1]=1;
            if(a[i-1]>f[i][1]&&a[i]>f[i-1][0]) f[i][1]=a[i-1],pre[i][1]=0;
        }
        int d;
        if(f[n][0]<=n) d=0;
        else if(f[n][1]>=1) d=1;
        else{puts("NO");continue;}
        for(int i=n;i>=1;d=pre[i][d],i--)
            if(d) ans1.push(a[i]);else ans2.push(a[i]);
        printf("YES\n%d ",ans1.size());
        while(!ans1.empty()) printf("%d ",ans1.top()),ans1.pop();
        printf("\n%d ",ans2.size());
        while(!ans2.empty()) printf("%d ",ans2.top()),ans2.pop();
        puts("");
    }
    return 0;
}