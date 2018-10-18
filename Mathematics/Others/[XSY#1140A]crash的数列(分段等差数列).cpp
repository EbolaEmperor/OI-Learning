#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=20000000;
LL g[N+10],n;

int main()
{
    g[1]=1;g[2]=3;
    int idx=2;
    for(int i=3;i<=N;i++)
    {
        g[i]=g[i-1]+idx;
        if(i==g[idx]) idx++;
    }
    cin>>n;
    int ans=lower_bound(g+1,g+1+N,n)-g;
    if(ans<=N) cout<<ans<<endl;
    else
    {
        LL cur=N,now=g[N];
        while(cur!=g[idx])
            cur++,now+=idx;
        idx++;
        while(now<n)
        {
            cur+=g[idx]-g[idx-1];
            now+=(g[idx]-g[idx-1])*idx;
            idx++;
        }
        if(now==n) cout<<cur<<endl;
        else
        {
            idx--;
            now-=(g[idx]-g[idx-1])*idx;
            cur-=g[idx]-g[idx-1];
            while(now<n)
            {
                cur++;now+=idx;
                if(cur==g[idx]) idx++;
            }
            cout<<cur<<endl;
        }
    }
    return 0;
}