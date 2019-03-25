#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n;cin>>n;
    if(~n&1)
    {
        int m=n*(n-1)/2-n/2;
        printf("%d\n",m);
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
            {
                if(i+j==n+1) continue;
                printf("%d %d\n",i,j);
            }
    }
    else
    {
        int m=(n-1)*(n-2)/2-(n-1)/2+(n-1);
        printf("%d\n",m);
        for(int i=1;i<n;i++)
            for(int j=i+1;j<n;j++)
            {
                if(i+j==n) continue;
                printf("%d %d\n",i,j);
            }
        for(int i=1;i<n;i++)
            printf("%d %d\n",i,n);
    }
    return 0;
}