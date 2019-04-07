#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010;
map<LL,LL> f;
int n;LL a[N];

inline void upmax(LL &x,const LL &y){if(y>x) x=y;}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lld",a+i);
    f[a[1]-1]=0;
    for(int i=2;i<=n;i++)
        for(map<LL,LL>::iterator it=f.lower_bound(a[i]);it!=f.end();)
        {
            upmax(f[it->first%a[i]],it->second+(it->first-it->first%a[i])*(i-1));
            upmax(f[a[i]-1],it->second+(it->first-it->first%a[i]-a[i])*(i-1));
            map<LL,LL>::iterator pre=it;it++;f.erase(pre);
        }
    LL ans=0;
    for(map<LL,LL>::iterator it=f.begin();it!=f.end();it++)
        upmax(ans,it->first*n+it->second);
    printf("%lld\n",ans);
    return 0;
}
