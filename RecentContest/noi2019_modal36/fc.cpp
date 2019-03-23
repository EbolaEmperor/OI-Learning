#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,LL> pil;
const int N=1000010;
int n,t[N],a[N];
vector<pil> upd[N];
LL bit[N],f[N];

inline int lowbit(const int &x){return x&-x;}
inline void upmax(LL &x,const LL &y){if(y>x) x=y;}
void update(int p,LL x){for(;p<=n;p+=lowbit(p)) upmax(bit[p],x);}
LL query(int p){LL res=0;for(;p;p-=lowbit(p)) upmax(res,bit[p]);return res;}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",t+i);
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    LL ans=0;
    for(int i=1;i<=n;i++)
    {
        for(auto p : upd[i]) update(p.first,p.second);
        f[i]=query(max(i-t[i],0))+(LL)a[i]*t[i];
        if(t[i]==0) update(i,f[i]);
        else if(i+t[i]<=n) upd[i+t[i]].emplace_back(pil(i,f[i]));
        ans=max(ans,f[i]);
    }
    printf("%lld\n",ans);
    return 0;
}