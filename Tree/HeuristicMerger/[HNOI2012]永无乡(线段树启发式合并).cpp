#include<bits/stdc++.h>
#define newnode(x) x=new Node,x->lc=x->rc=null
using namespace std;

int fa[100010];
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}

struct Node
{
	Node *lc,*rc;
	int s;
	Node(){lc=rc=NULL;s=0;}
};
Node *rt[100010],*null;
int idex[100010];

void insert(Node* &o,int l,int r,int x)
{
	newnode(o);o->s=1;
	if(l==r) return;
	int mid=(l+r)/2;
	if(x<=mid) insert(o->lc,l,mid,x);
	else insert(o->rc,mid+1,r,x);
}

Node *merge(Node *p1,Node *p2,int l,int r)
{
	if(p1==null) return p2;
	if(p2==null) return p1;
	int mid=(l+r)/2;
	p1->lc=merge(p1->lc,p2->lc,l,mid);
	p1->rc=merge(p1->rc,p2->rc,mid+1,r);
	p1->s=p1->lc->s+p1->rc->s;
	return p1;
}

int kth(Node *o,int l,int r,int x)
{
	if(l==r) return l;
	int size=o->lc->s;
	int mid=(l+r)/2;
	if(x<=size) return kth(o->lc,l,mid,x);
	else return kth(o->rc,mid+1,r,x-size);
}

int main()
{
	newnode(null);
	int n,m,x,y;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		insert(rt[i],1,n,x);
		idex[x]=i;
		fa[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		x=find(x);y=find(y);
		if(x==y) continue;
		rt[x]=merge(rt[x],rt[y],1,n);
		fa[y]=x;
	}
	cin>>m;
	for(int i=1;i<=m;i++)
	{
		char ch=getchar();
		while(ch!='Q'&&ch!='B') ch=getchar();
		scanf("%d%d",&x,&y);
		if(ch=='B')
		{
			x=find(x);y=find(y);
			if(x==y) continue;
			rt[x]=merge(rt[x],rt[y],1,n);
			fa[y]=x;
		}
		else
		{
			x=find(x);
			if(rt[x]->s<y){puts("-1");continue;}
			printf("%d\n",idex[kth(rt[x],1,n,y)]);
		}
	}
	return 0;
}
