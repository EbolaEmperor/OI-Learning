#include<bits/stdc++.h>
#define newnode(x) x=new InsideNode,x->lc=x->rc=null
#define Newnode(x) x=new OutsideNode,x->lc=x->rc=Null
using namespace std;

typedef unsigned int uint;
struct InsideNode
{
	InsideNode *lc,*rc;
	uint s,tag;
	InsideNode(){lc=rc=NULL;s=tag=0;}
};
InsideNode *null;
struct OutsideNode
{
	OutsideNode *lc,*rc;
	InsideNode *root;
	OutsideNode(){lc=rc=NULL;root=null;}
};
OutsideNode *rt,*Null;
int n,m;
int opt[50010],a[50010],b[50010],c[50010];
int Hash[50010];

void add(InsideNode* &o,int l,int r,int nl,int nr)
{
	if(o==null) newnode(o);
	o->s+=nr-nl+1;
	if(l==nl&&r==nr){o->tag++;return;}
	int mid=(l+r)/2;
	if(nr<=mid) add(o->lc,l,mid,nl,nr);
	else if(nl>mid) add(o->rc,mid+1,r,nl,nr);
	else add(o->lc,l,mid,nl,mid),add(o->rc,mid+1,r,mid+1,nr);
} 

void insert(OutsideNode* &o,int l,int r,int x,int nl,int nr)
{
	if(o==Null) Newnode(o);
	add(o->root,1,n,nl,nr);
	if(l==r) return;
	int mid=(l+r)/2;
	if(x<=mid) insert(o->lc,l,mid,x,nl,nr);
	else insert(o->rc,mid+1,r,x,nl,nr);
}

uint query(InsideNode *o,int l,int r,int nl,int nr)
{
	if(o==null) return 0;
	if(l==nl&&r==nr) return o->s;
	int mid=(l+r)/2;
	uint res=o->tag*(nr-nl+1);
	if(nr<=mid) res+=query(o->lc,l,mid,nl,nr);
	else if(nl>mid) res+=query(o->rc,mid+1,r,nl,nr);
	else res+=query(o->lc,l,mid,nl,mid)+query(o->rc,mid+1,r,mid+1,nr);
	return res;
}

int kth(OutsideNode *o,int l,int r,int x,int nl,int nr)
{
	if(l==r) return l;
	int mid=(l+r)/2;
	uint size=query(o->rc->root,1,n,nl,nr);
	if(x<=size) return kth(o->rc,mid+1,r,x,nl,nr);
	else return kth(o->lc,l,mid,x-size,nl,nr);
}

int main()
{
	null=new InsideNode;
	null->lc=null->rc=null;
	Null=new OutsideNode;
	Null->lc=Null->rc=Null;
	rt=Null;
	cin>>n>>m;
	int sz=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d",opt+i,a+i,b+i,c+i);
		if(opt[i]==1) Hash[++sz]=c[i];
	}
	sort(Hash+1,Hash+1+sz);
	int hs=unique(Hash+1,Hash+1+sz)-(Hash+1);
	for(int i=1;i<=m;i++)
		if(opt[i]==1) c[i]=lower_bound(Hash+1,Hash+1+hs,c[i])-Hash;
	for(int i=1;i<=m;i++)
	{
		if(opt[i]==1) insert(rt,1,hs,c[i],a[i],b[i]);
		else printf("%d\n",Hash[kth(rt,1,hs,c[i],a[i],b[i])]);
	}
	return 0;
}
