#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct Node
{
	Node *lson,*rson;
	int val,sum;
};

Node *root[200010],*p;
int n;

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->lson=o->rson=NULL;
	o->val=o->sum=0;
	int mid=(l+r)/2;
	if(l==r) o->val=mid,o->sum=1;
	else build(o->lson,l,mid),build(o->rson,mid+1,r);
}

void change(Node* &o,Node *pre,int l,int r,int pos,int x)
{
	o=new Node;
	o->val=pre->val;
	o->sum=pre->sum;
	o->lson=pre->lson;
	o->rson=pre->rson;
	int mid=(l+r)/2;
	if(l==r) o->val=x;
	else if(pos<=mid) change(o->lson,pre->lson,l,mid,pos,x);
	else change(o->rson,pre->rson,mid+1,r,pos,x);
}

int query(Node* &o,int l,int r,int pos)
{
	int mid=(l+r)/2;
	if(l==r) {p=o;return o->val;}
	else if(pos<=mid) return query(o->lson,l,mid,pos);
	else return query(o->rson,mid+1,r,pos);
}

int find(Node* &o,int x)
{
	int k=query(o,1,n,x);
	if(k==x) return k;
	else return find(o,k);
}

void add(Node* &o,int l,int r,int pos)
{
	int mid=(l+r)/2;
	if(l==r) o->sum++;
	else if(pos<=mid) add(o->lson,l,mid,pos);
	else add(o->rson,mid+1,r,pos);
}

void merge(int now,int pre,int a,int b)
{
	int p1=find(root[pre],a);
	Node *pp;pp=p;
	int p2=find(root[pre],b);
	if(p1==p2) {root[now]=root[pre];return;}
	if(pp->sum<p->sum) swap(p1,p2);
	change(root[now],root[pre],1,n,p2,p1);
	if(pp->sum==p->sum) add(root[now],1,n,p1);
}

bool check(int now,int pre,int a,int b)
{
	root[now]=root[pre];
	int p1=find(root[now],a);
	int p2=find(root[now],b);
	return p1==p2;
}

int main()
{
	int m,opt,x,y;
	cin>>n>>m;
	build(root[0],1,n);
	for(int T=1;T<=m;T++)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1) scanf("%d",&y),merge(T,T-1,x,y);
		if(opt==2) root[T]=root[x];
		if(opt==3) scanf("%d",&y),printf("%d\n",check(T,T-1,x,y));
	}
	return 0;
}
