#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

int a[20005],b[20005];

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	while(n&&m)
	{
		for(int i=0;i<n;i++) scanf("%d",a+i);
		for(int i=0;i<m;i++) scanf("%d",b+i);
		sort(a,a+n);
		sort(b,b+m);
		int cur=0,cost=0;
		for(int i=0;i<m;i++)
			if(b[i]>=a[cur])
			{
				cost+=b[i];
				cur++;
				if(cur==n) break;
			}
		if(cur==n) printf("%d\n",cost);
		else puts("Loowater is doomed!");
		scanf("%d%d",&n,&m);
	}
	return 0;
}
