#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct Node
{
	Node *lson,*rson;
	int state,lazy;
};

Node *root;

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->lson=o->rson=NULL;
	o->lazy=0;
	o->state=1;
	if(l<r)
	{
		int mid=(l+r)/2;
		build(o->lson,l,mid);
		build(o->rson,mid+1,r);
	}
}

void pushdown(Node* &o,int l,int r)
{
	o->lson->lazy=o->lazy;
	o->rson->lazy=o->lazy;
	o->lson->state=o->lazy;
	o->rson->state=o->lazy;
	o->lazy=0;
}

void color(Node* &o,int l,int r,int needl,int needr,int c)
{
	if(l>=needl&&r<=needr)
	{
		o->state=1<<(c-1);
		o->lazy=1<<(c-1);
	}
	else
	{
		int mid=(l+r)/2;
		if(o->lazy>0) pushdown(o,l,r);
		if(needl<=mid) color(o->lson,l,mid,needl,needr,c);
		if(needr>mid) color(o->rson,mid+1,r,needl,needr,c);
		o->state=o->lson->state|o->rson->state;
	}
}

int query(Node* &o,int l,int r,int needl,int needr)
{
	if(l>=needl&&r<=needr)
		return o->state;
	else
	{
		int mid=(l+r)/2,state=0;
		if(o->lazy>0) pushdown(o,l,r);
		if(needl<=mid) state|=query(o->lson,l,mid,needl,needr);
		if(needr>mid) state|=query(o->rson,mid+1,r,needl,needr);
		return state;
	}
}

int count(int x)
{
	int cnt=0;
	while(x>0)
	{
		if(x%2==1) cnt++;
		x>>=1;
	}
	return cnt;
}

int main()
{
	int l,t,o,x,y,k;
	char opt;
	scanf("%d%d%d",&l,&t,&o);
	build(root,1,l);
	for(int i=1;i<=o;i++)
	{
		opt=' ';
		while(opt!='C'&&opt!='P') opt=getchar();
		scanf("%d%d",&x,&y);
		if(x>y) swap(x,y);
		if(opt=='C') scanf("%d",&k),color(root,1,l,x,y,k);
		if(opt=='P') {int ans=query(root,1,l,x,y);printf("%d\n",count(ans));};
	}
}
