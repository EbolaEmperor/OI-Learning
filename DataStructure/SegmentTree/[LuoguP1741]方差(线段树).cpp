#include<iostream>
#include<cstdio>
using namespace std;

struct Node
{
	Node *lson,*rson;
	double sum,sqrsum,lazy;
};

Node *root;
double a[100005];
int n,m;

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->sum=o->sqrsum=o->lazy=0.0;
	o->lson=o->rson=NULL;
	int mid=(l+r)/2;
	if(l==r)
	{
		o->sum=a[mid];
		o->sqrsum=a[mid]*a[mid];
	}
	else
	{
		build(o->lson,l,mid);
		build(o->rson,mid+1,r);
		o->sum=o->lson->sum+o->rson->sum;
		o->sqrsum=o->lson->sqrsum+o->rson->sqrsum;
	}
}

void pushdown(Node* &o,int l,int r)
{
	int mid=(l+r)/2;
	o->lson->lazy+=o->lazy;
	o->rson->lazy+=o->lazy;
	o->lson->sqrsum+=2*o->lazy*o->lson->sum+(mid+1-l)*o->lazy*o->lazy;
	o->rson->sqrsum+=2*o->lazy*o->rson->sum+(r-mid)*o->lazy*o->lazy;
	o->lson->sum+=o->lazy*(mid+1-l);
	o->rson->sum+=o->lazy*(r-mid);
	o->lazy=0.0;
}

void add(Node* &o,int l,int r,int needl,int needr,double k)
{
	if(l>=needl&&r<=needr)
	{
		o->lazy+=k;
		o->sqrsum+=2*k*o->sum+(r+1-l)*k*k;
		o->sum+=k*(r+1-l);
	}
	else
	{
		int mid=(l+r)/2;
		pushdown(o,l,r);
		if(needl<=mid) add(o->lson,l,mid,needl,needr,k);
		if(needr>mid) add(o->rson,mid+1,r,needl,needr,k);
		o->sum=o->lson->sum+o->rson->sum;
		o->sqrsum=o->lson->sqrsum+o->rson->sqrsum;
	}
}

double query_sum(Node* &o,int l,int r,int needl,int needr)
{
	if(l>=needl&&r<=needr)
		return o->sum;
	else
	{
		int mid=(l+r)/2;
		double ret=0.0;
		pushdown(o,l,r);
		if(needl<=mid) ret+=query_sum(o->lson,l,mid,needl,needr);
		if(needr>mid) ret+=query_sum(o->rson,mid+1,r,needl,needr);
		return ret;
	}
}

double query_sqrsum(Node* &o,int l,int r,int needl,int needr)
{
	if(l>=needl&&r<=needr)
		return o->sqrsum;
	else
	{
		int mid=(l+r)/2;
		double ret=0.0;
		pushdown(o,l,r);
		if(needl<=mid) ret+=query_sqrsum(o->lson,l,mid,needl,needr);
		if(needr>mid) ret+=query_sqrsum(o->rson,mid+1,r,needl,needr);
		return ret;
	}
}

int main()
{
	int opt,x,y;
	double k;
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%lf",a+i);
	build(root,1,n);
	for(int T=1;T<=m;T++)
	{
		scanf("%d",&opt);
		if(opt==1) 
		{
			scanf("%d%d%lf",&x,&y,&k);
			add(root,1,n,x,y,k);
		}
		if(opt==2)
		{
			scanf("%d%d",&x,&y);
			double ave=query_sum(root,1,n,x,y)/(y+1-x);
			printf("%.4lf\n",ave);
		}
		if(opt==3)
		{
			scanf("%d%d",&x,&y);
			double ave=query_sum(root,1,n,x,y)/(y+1-x);
			double ans=(query_sqrsum(root,1,n,x,y)-2*ave*query_sum(root,1,n,x,y))/(y+1-x)+ave*ave;
			printf("%.4lf\n",ans);
		}
	}
	return 0;
}
