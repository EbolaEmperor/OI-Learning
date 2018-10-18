#include<iostream>
#include<cstdio>
using namespace std;

struct Node
{
	Node *lson,*rson;
	long long sum,add,mul;
};

Node *root;
int n,m,p;
long long a[100005];

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->lson=o->rson=NULL;
	o->sum=o->add=0;
	o->mul=1;
	int mid=(l+r)/2;
	if(l==r) o->sum=a[mid]%p;
	else
	{
		build(o->lson,l,mid);
		build(o->rson,mid+1,r);
		o->sum=(o->lson->sum+o->rson->sum)%p;
	}
}

void pushdown(Node* &o,int l,int r)
{
	o->lson->mul=(o->lson->mul*o->mul)%p;
	o->rson->mul=(o->rson->mul*o->mul)%p;
	o->lson->add=(o->lson->add*o->mul)%p;
	o->rson->add=(o->rson->add*o->mul)%p;
	o->lson->sum=(o->lson->sum*o->mul)%p;
	o->rson->sum=(o->rson->sum*o->mul)%p;
	o->mul=1;
	o->lson->add=(o->lson->add+o->add)%p;
	o->rson->add=(o->rson->add+o->add)%p;
	int mid=(l+r)/2;
	o->lson->sum=(o->lson->sum+o->add*(mid+1-l))%p;
	o->rson->sum=(o->rson->sum+o->add*(r-mid))%p;
	o->add=0;
}

void add(Node* &o,int l,int r,int needl,int needr,int k)
{
	if(l>=needl&&r<=needr)
	{
		o->add=(o->add+k)%p;
		o->sum=(o->sum+k*(r+1-l))%p;
	}
	else
	{
		int mid=(l+r)/2;
		if(o->add!=0||o->mul!=1) pushdown(o,l,r);
		if(needl<=mid) add(o->lson,l,mid,needl,needr,k);
		if(needr>mid) add(o->rson,mid+1,r,needl,needr,k);
		o->sum=(o->lson->sum+o->rson->sum)%p;
	}
}

void mult(Node* &o,int l,int r,int needl,int needr,int k)
{
	if(l>=needl&&r<=needr)
	{
		o->sum=(o->sum*k)%p;
		o->mul=(o->mul*k)%p;
		o->add=(o->add*k)%p;
	}
	else
	{
		int mid=(l+r)/2;
		if(o->add!=0||o->mul!=1) pushdown(o,l,r);
		if(needl<=mid) mult(o->lson,l,mid,needl,needr,k);
		if(needr>mid) mult(o->rson,mid+1,r,needl,needr,k);
		o->sum=(o->lson->sum+o->rson->sum)%p;
	}
}

long long query(Node* &o,int l,int r,int needl,int needr)
{
	if(l>=needl&&r<=needr)
		return o->sum%p;
	else
	{
		int mid=(l+r)/2;
		long long ret=0;
		if(o->add!=0||o->mul!=1) pushdown(o,l,r);
		if(needl<=mid) ret=(ret+query(o->lson,l,mid,needl,needr))%p;
		if(needr>mid) ret=(ret+query(o->rson,mid+1,r,needl,needr))%p;
		return ret%p;
	}
}

int main()
{
	int opt,x,y,k;
	scanf("%d%d%d",&n,&m,&p);
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	build(root,1,n);
	for(int T=1;T<=m;T++)
	{
		scanf("%d",&opt);
		if(opt==1) scanf("%d%d%d",&x,&y,&k),mult(root,1,n,x,y,k);
		if(opt==2) scanf("%d%d%d",&x,&y,&k),add(root,1,n,x,y,k);
		if(opt==3) scanf("%d%d",&x,&y),printf("%lld\n",query(root,1,n,x,y));
	}
	return 0;
}
