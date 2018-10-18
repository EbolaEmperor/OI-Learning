#include<bits/stdc++.h>
using namespace std;

const int N=400100;
struct Node{int ch[2];} nd[N*31];
int sz;
int a[N],n;
int lx[N],rx[N];

void insert(int x)
{
	int now=0;
	for(int i=30;i>=0;i--)
	{
		int j=(x>>i)&1;
		if(!nd[now].ch[j])nd[now].ch[j]=++sz;
		now=nd[now].ch[j];
	}
}

int query(int x)
{
	int ans=0,now=0;
	for(int i=30;i>=0;i--)
	{
		int j=((x>>i)&1)^1;
		if(nd[now].ch[j]) ans|=(1<<i);
		else j^=1;
		now=nd[now].ch[j];
	}
	return ans;
}

int main()
{
	scanf("%d",&n);n++;
	for(int i=2;i<=n;i++) scanf("%d",a+i);
	int sum=0;
	insert(0);
	lx[1]=0;
	for(int i=2;i<=n;i++)
	{
		sum^=a[i];
		insert(sum);
		lx[i]=query(sum);
		lx[i]=max(lx[i],lx[i-1]);
	}
	sz=0;sum=0;
	memset(nd,0,sizeof(nd));
	insert(0);
	for(int i=2;i<=n/2+1;i++) swap(a[i],a[n-i+2]);
	rx[1]=0;
	for(int i=2;i<=n;i++)
	{
		sum^=a[i];
		insert(sum);
		rx[i]=query(sum);
		rx[i]=max(rx[i],rx[i-1]);
	}
	for(int i=2;i<=n/2+1;i++) swap(rx[i],rx[n-i+2]);
	int ans=0;
	for(int i=2;i<n;i++) ans=max(ans,lx[i]+rx[i]);
	cout<<ans<<endl;
	return 0;
}
