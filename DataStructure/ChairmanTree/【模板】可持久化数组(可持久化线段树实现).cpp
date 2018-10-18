#include<bits/stdc++.h>
using namespace std;

struct Node
{
	Node *lson,*rson;
	int val;
};
Node *root[1000010];
int a[1000010];

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->lson=o->rson=NULL;
	if(l==r) o->val=a[l];
	else
	{
		int mid=(l+r)/2;
		o->val=0;
		build(o->lson,l,mid);
		build(o->rson,mid+1,r);
	}
}

void change(Node* &o,Node* &pre,int l,int r,int p,int k)
{
	o=new Node;
	o->lson=pre->lson;
	o->rson=pre->rson;
	o->val=pre->val;
	int mid=(l+r)/2;
	if(l==r) o->val=k;
	else if(p<=mid) change(o->lson,pre->lson,l,mid,p,k);
	else change(o->rson,pre->rson,mid+1,r,p,k);
}

int query(Node* &o,int l,int r,int p)
{
	int mid=(l+r)/2;
	if(l==r) return o->val;
	else if(p<=mid) return query(o->lson,l,mid,p);
	else return query(o->rson,mid+1,r,p);
}

int main()
{
	int n,m;
	int his,opt,p,k;
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	build(root[0],1,n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&his,&opt,&p);
		if(opt==1) {scanf("%d",&k);change(root[i],root[his],1,n,p,k);}
		if(opt==2) {printf("%d\n",query(root[his],1,n,p));root[i]=root[his];}
	}
	return 0;
}
