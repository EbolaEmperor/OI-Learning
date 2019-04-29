#include<bits/stdc++.h>
using namespace std;

const int N=5010;
struct T{int t,x;} g[N];
unsigned f[N];
int n;

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d",&g[i].t,&g[i].x);
    sort(g+1,g+1+n,[](T a,T b){return a.t<b.t;});
    for(int i=1;i<=n;i++)
    {
        f[i]=UINT_MAX;
        unsigned mx=0;
        for(int j=i;j>=1;j--)
        {
            mx=max(mx,1u*g[j].x);
            f[i]=min(f[i],max(1u*g[i].t,f[j-1])+2u*mx);
        }
    }
    printf("%u\n",f[n]);
    return 0;
}