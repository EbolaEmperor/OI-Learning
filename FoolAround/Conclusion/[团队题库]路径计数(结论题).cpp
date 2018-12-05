#include<bits/stdc++.h>
using namespace std;

int main()
{
    int n,x,y,ans=0;
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&x,&y);
        ans+=(x>1);
    }
    printf("%d\n",ans-1);
    return 0;
}