#include<bits/stdc++.h>
using namespace std;

typedef pair<unsigned,int> pui;
const int N=500010,P=N*35;
priority_queue<pui> pq;
int ch[P][2],sz[P],tot=1;
int cur[N],n,m;
unsigned a[N];

void insert(unsigned x)
{
	int o=1;
	for(int i=31;i>=0;i--)
	{
		sz[o]++;
		int j=(x>>i)&1;
		if(!ch[o][j]) ch[o][j]=++tot;
		o=ch[o][j];
	}
	sz[o]++;
}

unsigned query(unsigned x,int k)
{
	int o=1;unsigned res=0;
	for(int i=31;i>=0;i--)
	{
		int j=(x>>i)&1;
		if(sz[ch[o][j^1]]>=k) o=ch[o][j^1],res|=1u<<i;
		else k-=sz[ch[o][j^1]],o=ch[o][j];
	}
	return res;
}

int main()
{
	scanf("%d%d",&n,&m);
	insert(0);
	for(int i=1;i<=n;i++)
		scanf("%u",a+i),insert(a[i]^=a[i-1]);
	for(int i=0;i<=n;i++)
		pq.push(pui(query(a[i],cur[i]=1),i));
	long long ans=0;
	for(int i=1,u;i<=2*m;i++)
	{
		pui tmp=pq.top();pq.pop();
		ans+=tmp.first;u=tmp.second;
		if(cur[u]<n) pq.push(pui(query(a[u],++cur[u]),u));
	}
	printf("%lld\n",ans/2);
	return 0;
}