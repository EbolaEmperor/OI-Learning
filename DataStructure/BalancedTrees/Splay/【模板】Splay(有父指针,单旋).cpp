#include<iostream>
#include<cstdio>
using namespace std;

struct Node
{
	Node* son[2];
	Node* father;
	int v;
	int sum;
	int flip;     //翻转标记
};

Node *root;

void maintain(Node* &o)
{
	o->sum=1;
	if(o->son[0]!=NULL) o->sum+=o->son[0]->sum;
	if(o->son[1]!=NULL) o->sum+=o->son[1]->sum;
}

void rotate(Node* &o,bool d)
{
	Node* k=o->son[d^1];
	o->son[d^1]=k->son[d];
	if(o->son[d^1]!=NULL) o->son[d^1]->father=o;
	k->son[d]=o;
	k->father=o->father;
	o->father=k;
	maintain(o);
	maintain(k);
	o=k;
}

void build(Node* &o,int l,int r)
{
	int mid=(l+r)/2;
	o->v=mid;
	o->flip=0;
	o->son[0]=o->son[1]=NULL;
	if(mid>l)
	{
		o->son[0]=new Node;
		o->son[0]->father=o;
		build(o->son[0],l,mid-1);
	}
	if(mid<r)
	{
		o->son[1]=new Node;
		o->son[1]->father=o;
		build(o->son[1],mid+1,r);
	}
	maintain(o);
}

void pushdown(Node* &o)
{
	swap(o->son[0],o->son[1]);
	if(o->son[0]!=NULL) o->son[0]->flip^=1;
	if(o->son[1]!=NULL) o->son[1]->flip^=1;
	o->flip^=1;
}

Node *kth(Node* &o,int k)
{
	if(o==NULL) return NULL;
	if(o->flip) pushdown(o);
	int ss=0;
	if(o->son[0]!=NULL) ss=o->son[0]->sum;
	if(k==ss+1) return o;
	if(k<=ss) return kth(o->son[0],k);
	if(k>ss+1) return kth(o->son[1],k-ss-1);
}

void splay(Node* &o,Node* goal)
{
	if(o==goal) return;
	while(o->father!=goal)
	{
		Node *p=o->father;
		Node *q=p->father;
		if(o==p->son[0]&&p==q->son[0]) rotate(q->son[0],1);
		else if(o==p->son[1]&&p==q->son[1]) rotate(q->son[1],0);
		else if(o==p->son[1]&&p==q->son[0]) rotate(q->son[0],0);
		else if(o==p->son[0]&&p==q->son[1]) rotate(q->son[1],1);
	}
	Node *f=o->father;
	if(f->father==NULL)
		if(o==f->son[0]) rotate(f,1),o=f;else rotate(f,0),o=f;
	else
	{
		Node *gf=f->father;
		if(f==gf->son[0]&&o==f->son[0]) rotate(gf->son[0],1),o=gf->son[0];
		else if(f==gf->son[1]&&o==f->son[1]) rotate(gf->son[1],0),o=gf->son[1];
		else if(f==gf->son[0]&&o==f->son[1]) rotate(gf->son[0],0),o=gf->son[0];
		else if(f==gf->son[1]&&o==f->son[0]) rotate(gf->son[1],1),o=gf->son[1];
	}
}

void DFS(Node* &o)
{
	if(o->flip) pushdown(o);
	if(o->son[0]!=NULL) DFS(o->son[0]);
	printf("%d ",o->v);
	if(o->son[1]!=NULL) DFS(o->son[1]);
}

int main()
{
	int n,m,l,r;
	Node *p1,*p2;
	cin>>n>>m;
	root=new Node;
	root->son[0]=root->son[1]=root->father=NULL;
	build(root,1,n);
	for(int T=1;T<=m;T++)
	{
		scanf("%d%d",&l,&r);
		if(l==r) continue;
		p1=kth(root,l);
		splay(p1,root);
		root=p1;
		p2=kth(root,r);
		splay(p2,root->son[1]);
		swap(root->v,root->son[1]->v);
		if(root->son[1]->son[0]!=NULL) root->son[1]->son[0]->flip^=1;
	}
	DFS(root);
	printf("\n");
	return 0;
}
