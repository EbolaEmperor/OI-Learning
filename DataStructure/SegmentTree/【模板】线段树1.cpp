#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
struct Node
{
	Node *lson,*rson;
	LL val,lazy;
};
Node *root;
LL a[100010];

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->lson=o->rson=NULL;
	o->val=o->lazy=0;
	if(l==r) o->val=a[l];
	else
	{
		int mid=(l+r)/2;
		build(o->lson,l,mid);
		build(o->rson,mid+1,r);
		o->val=o->lson->val+o->rson->val;
	}
}

void pushdown(Node* &o,int l,int r)
{
	o->lson->lazy+=o->lazy;
	o->rson->lazy+=o->lazy;
	int mid=(l+r)/2;
	o->lson->val+=o->lazy*(mid-l+1);
	o->rson->val+=o->lazy*(r-mid);
	o->lazy=0;
}

void add(Node* &o,int l,int r,int needl,int needr,LL k)
{
	if(l>=needl&&r<=needr)
	{
		o->val+=k*(r-l+1);
		o->lazy+=k;
		return;
	}
	pushdown(o,l,r);
	int mid=(l+r)/2;
	if(mid>=needl) add(o->lson,l,mid,needl,needr,k);
	if(mid<needr) add(o->rson,mid+1,r,needl,needr,k);
	o->val=o->lson->val+o->rson->val;
}

LL query(Node* &o,int l,int r,int needl,int needr)
{
	if(l>=needl&&r<=needr) return o->val;
	pushdown(o,l,r);
	int mid=(l+r)/2;
	LL ans=0;
	if(mid>=needl) ans+=query(o->lson,l,mid,needl,needr);
	if(mid<needr) ans+=query(o->rson,mid+1,r,needl,needr);
	return ans;
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	build(root,1,n);
	int opt,l,r;
	LL k;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&opt);
		if(opt==1){scanf("%d%d%lld",&l,&r,&k);add(root,1,n,l,r,k);}
		if(opt==2){scanf("%d%d",&l,&r);printf("%lld\n",query(root,1,n,l,r));}
	}
	return 0;
}
