#include<bits/stdc++.h>
using namespace std;

struct TrieNode
{
	int ch[2];
	int id;
} nd[30000000];
int sz=0;
int root[600010];
int n,m;
bool flag=0;

void insert(int pre,int x)
{
	int now=sz;
	for(int i=24;i>=0;i--)
	{
		nd[now].id=nd[pre].id+1;
		int j=(x>>i)&1;
		nd[now].ch[j]=++sz;
		nd[now].ch[j^1]=nd[pre].ch[j^1];
		now=sz;
		pre=nd[pre].ch[j];
	}
	nd[now].id=nd[pre].id+1;
}

int query(int l,int r,int x)
{
	int ans=0;
	for(int i=24;i>=0;i--)
	{
		int j=((x>>i)&1)^1;
		if(nd[nd[r].ch[j]].id-nd[nd[l].ch[j]].id) ans|=(1<<i);
		else j^=1;
		l=nd[l].ch[j];
		r=nd[r].ch[j];
	}
	return ans;
}

int main()
{
	cin>>n>>m;n++;
	root[1]=++sz;
	insert(0,0);
	int sum=0,x,l,r;
	char opt[5];
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&x);
		sum^=x;
		root[i]=++sz;
		insert(root[i-1],sum);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",opt);
		if(opt[0]=='A')
		{
			scanf("%d",&x);
			sum^=x;
			root[n+1]=++sz;
			insert(root[n],sum);
			n++;
		}
		else
		{
			scanf("%d%d%d",&l,&r,&x);
			printf("%d\n",query(root[l-1],root[r],x^sum));
		}
	}
	return 0;
}
