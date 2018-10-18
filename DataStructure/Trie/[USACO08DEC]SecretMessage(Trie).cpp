#include<bits/stdc++.h>
#define newnode(x) x=new Node,x->ch[0]=x->ch[1]=null;
using namespace std;

struct Node
{
	Node* ch[2];
	int ed,sm;
	Node(){ch[0]=ch[1]=NULL;ed=sm=0;}
};
Node* root;
Node* null;
int a[500010],sz;

void insert()
{
	Node* p=root;
	for(int i=1;i<=sz;i++)
	{
		int j=a[i];
		if(p->ch[j]==null) newnode(p->ch[j]);
		p=p->ch[j];
		p->sm++;
	}
	p->ed++;
}

int query()
{
	int ans=0;
	Node* p=root;
	for(int i=1;i<=sz;i++)
	{
		int j=a[i];
		p=p->ch[j];
		ans+=p->ed;
	}
	return ans+p->sm-p->ed;
}

int main()
{
	null=new Node;
	null->ch[0]=null->ch[1]=null;
	newnode(root);
	int m,n;
	cin>>m>>n;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&sz);
		for(int j=1;j<=sz;j++) scanf("%d",a+j);
		insert();
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&sz);
		for(int j=1;j<=sz;j++) scanf("%d",a+j);
		printf("%d\n",query());
	}
	return 0;
}
