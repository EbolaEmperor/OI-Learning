#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<LL,LL> pll;
const int N=300010;
int n,a[N];
LL b[N],c[N],f[N];
pll d[N];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=2;i<=n;i++) scanf("%lld",b+i);
	for(int i=2;i<=n;i++) scanf("%lld",c+i);
	for(int i=1;i<=n;i++)
	{
		if(b[i]>c[i]) return puts("-1"),0;
		b[i]+=b[i-1];c[i]+=c[i-1];
		d[i]=make_pair(a[i]-c[i],b[i]-a[i]);
	}
	sort(d+1,d+1+n);
	int ans=0;f[1]=-INT_MAX;
	for(int i=1;i<=n;i++)
	{
		int tmp=upper_bound(f+1,f+1+ans,d[i].second)-f;
		f[tmp]=d[i].second;
		if(tmp>ans) ans++;
	}
	printf("%d\n",n-ans);
}
