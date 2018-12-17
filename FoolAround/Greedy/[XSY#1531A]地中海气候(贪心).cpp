#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010;
struct NUM{int x,p;} a[N];
int n,m;
LL ans[N];
int p[N],pp[N];
bool done[N];

inline int fg(int x){return (x&1)?-1:1;}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i].x);
        a[i].p=i;
    }
    for(int i=1;i<=m;i++) scanf("%d",p+i),pp[i]=p[i];
    sort(a+1,a+1+n,[](NUM a,NUM b){return a.x<b.x;});
    for(int i=n;i>=1;i--)
    {
        int pos=a[i].p;
        for(int j=1;j<=m;j++)
        {
            while(done[pp[j]]) pp[j]++;
            if(pos<=pp[j]) ans[j]+=fg(pp[j]-p[j])*a[i].x,pp[j]++;
            else ans[j]+=fg(pos-p[j])*a[i].x;
        }
        done[pos]=1;
    }
    for(int i=1;i<=m;i++)
        printf("%lld\n",ans[i]);
    return 0;
}