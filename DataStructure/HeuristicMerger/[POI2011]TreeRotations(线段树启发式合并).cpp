#include<bits/stdc++.h>
#define newnode(x) x=new Node,x->lson=x->rson=null
using namespace std;

typedef long long LL;
struct Node
{
	Node *lson,*rson;
	LL sum;
	Node(){lson=rson=NULL;sum=0;}
};
Node *root[400010],*null;
int dfn=0,a[400010];
int ls[400010],rs[400010];
LL sl,sr;

int dfs()
{
	int p=++dfn;
	scanf("%d",a+p);
	if(a[p]) return p;
	ls[p]=dfs();
	rs[p]=dfs();
	return p;
}

void maintain(Node *o){o->sum=o->lson->sum+o->rson->sum;}

void insert(Node* &o,int l,int r,int x)
{
	newnode(o);
	if(l==r){o->sum=1;return;}
	int mid=(l+r)/2;
	if(x<=mid) insert(o->lson,l,mid,x);
	else insert(o->rson,mid+1,r,x);
	maintain(o);
}

Node *merge(Node *x,Node *y)
{
	if(x==null) return y;
	if(y==null) return x;
	sl+=x->lson->sum*y->rson->sum;
	sr+=x->rson->sum*y->lson->sum;
	x->lson=merge(x->lson,y->lson);
	x->rson=merge(x->rson,y->rson);
	maintain(x);
	return x;
}

LL solve(int x)
{
	if(a[x]) return 0;
	LL ans=solve(ls[x])+solve(rs[x]);
	sl=sr=0;
	root[x]=merge(root[ls[x]],root[rs[x]]);
	return ans+min(sl,sr);
}

int main()
{
	int n,rt;
	null=new Node;
	null->lson=null->rson=null;
	cin>>n;
	rt=dfs();
	for(int i=1;i<=dfn;i++)
		if(a[i]) insert(root[i],1,n,a[i]);
	printf("%lld\n",solve(rt));
	return 0;
}
