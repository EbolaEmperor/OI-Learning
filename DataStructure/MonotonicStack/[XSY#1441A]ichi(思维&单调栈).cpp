#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010;
struct node{int h,l,rest;};
stack<node> stk;
int n,k,h[N];

int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++)
        scanf("%d",h+i);
    stk.push({0,0,0});
    LL ans=0;
    for(int i=1;i<=n+1;i++)
    {
        int rest=0,left=i;
        while(stk.size()>1&&stk.top().h>=h[i])
        {
            node top=stk.top();stk.pop();
            top.rest+=rest;left=top.l;
            int d=max(stk.top().h,h[i]);
            LL S=1ll*(top.h-d)*(i-top.l)-top.rest;
            if(S<=0) rest=-S;
            else
            {
                LL cnt=(S-1)/k+1;
                ans+=cnt;
                rest=k*cnt-S;
            }
        }
        stk.push({h[i],left,rest});
    }
    printf("%lld\n",ans);
    return 0;
}