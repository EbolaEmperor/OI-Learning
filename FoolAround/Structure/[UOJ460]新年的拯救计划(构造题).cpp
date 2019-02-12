#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,m;
    scanf("%d",&n);
    printf("%d\n",m=n/2);
    for(int i=1;i<=m;i++)
    {
        for(int j=1;j<m;j++)
            printf("%d %d ",i,i+j);
        for(int j=m+1;j<n;j++)
            printf("%d %d ",i+m,(i+j-1)%n+1);
        printf("%d %d\n",i,i+m);
    }
    return 0;
}