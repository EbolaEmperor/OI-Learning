#include<bits/stdc++.h>
using namespace std;
 
typedef long long LL;
const int N=1010;
int n,m,val[N];
 
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",val+i);
    for(int i=1,opt,l,r,x;i<=m;i++)
    {
        scanf("%d%d%d",&opt,&l,&r);
        if(opt==1)
        {
            scanf("%d",&x);
            sort(val+l,val+r+1);
            if(!x) reverse(val+l,val+r+1);
        }
        else
        {
            LL prod=1;
            for(int j=l;j<=r;j++) prod*=val[j];
            while(prod>=10) prod/=10;
            printf("%lld\n",prod);
        }
    }
    return 0;
}