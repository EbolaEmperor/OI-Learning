#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

typedef long long LL;
LL c[13][100010];
int n,k;

void Add(int k,int p,LL x){for(;p<=n+1;p+=lowbit(p)) c[k][p]+=x;}
LL Sum(int k,int p){LL res=0;for(;p;p-=lowbit(p)) res+=c[k][p];return res;}

int main()
{
	int x;
	scanf("%d%d",&n,&k);
	Add(0,1,1);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		for(int j=1;j<=k+1;j++)
			Add(j,x+1,Sum(j-1,x));
	}
	printf("%lld\n",Sum(k+1,n+1));
	return 0;
}
