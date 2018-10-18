#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct Node
{
	Node *ls,*rs;
	int mn,mx;
	Node(){ls=rs=NULL;mn=mx=0;}
};
Node* root[N];
int last[N];

void Insert(Node* &o,Node* pre,int l,int r,int k,int x,int y)
{
	o=new Node;*o=*pre;
	if(l==r){o->mn=x;o->mx=y;return;}
	int mid=(l+r)/2;
	if(k<=mid) Insert(o->ls,pre->ls,l,mid,k,x,y);
	else Insert(o->rs,pre->rs,mid+1,r,k,x,y);
	o->mn=min(o->ls->mn,o->rs->mn);
	o->mx=max(o->ls->mx,o->rs->mx);
}

int Query(Node *o,int l,int r,int k)
{
	if(l==r) return (o->mn<=k&&o->mx>=k)?l:0;
	int mid=(l+r)/2;
	if(o->rs->mn<=k&&o->rs->mx>=k)
	{
		int res=Query(o->rs,mid+1,r,k);
		if(res) return res;
	}
	return Query(o->ls,l,mid,k);
}

int main()
{
	root[0]=new Node;
	root[0]->ls=root[0]->rs=root[0];
	root[0]->mn=N+1;
	int n,m,x,y,ans=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		Insert(root[i],root[i-1],1,n,x,last[x]+1,i);
		last[x]=i;
	}
	while(m--)
	{
		scanf("%d%d",&x,&y);
		x=(x+ans)%n+1;y=(y+ans)%n+1;
		if(x>y) swap(x,y);
		ans=Query(root[y],1,n,x);
		printf("%d\n",ans);
	}
	return 0;
}
