#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
struct Pair
{
    LL x,y,fg;
    Pair(LL _x=0,LL _y=0,LL _fg=1):x(_x),y(_y),fg(_fg){}
    bool operator < (const Pair &a) const{return abs(x*y)<abs(a.x*a.y);}
} a,b,ans;

int main()
{
    int T;LL k,p;
    for(scanf("%d",&T);T;T--)
    {
        scanf("%lld%lld",&k,&p);
        a=Pair(k,1,1);
        b=Pair(p-k,1,-1);
        ans=min(a,b);
        while(min(a.x,b.x)>1)
        {
            LL r=a.x/b.x;
            a.x-=r*b.x;
            a.y+=r*b.y;
            ans=min(ans,a);
            swap(a,b);
        }
        printf("%lld %lld\n",ans.x*ans.fg,ans.y);
    }
    return 0;
}