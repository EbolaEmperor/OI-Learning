#include<bits/stdc++.h>
using namespace std;

priority_queue<int> pq;
long long ans=0;
int n;

int main()
{
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++)
    {
        scanf("%d",&x);
        pq.push(x);
        if(x<pq.top())
        {
            ans+=abs(x-pq.top());
            pq.pop();
            pq.push(x);
        }
    }
    printf("%lld\n",ans);
    return 0;
}