#include<bits/stdc++.h>
using namespace std;

struct Node
{
	Node *son[2];
	int val,sum;
	bool flip;
};
Node *root;

void maintain(Node* &o)
{
	o->sum=1;
	if(o->son[0]!=NULL) o->sum+=o->son[0]->sum;
	if(o->son[1]!=NULL) o->sum+=o->son[1]->sum;
}

void pushdown(Node* &o)
{
	o->flip^=1;
	if(o->son[0]!=NULL) o->son[0]->flip^=1;
	if(o->son[1]!=NULL) o->son[1]->flip^=1;
	swap(o->son[0],o->son[1]);
}

void rotate(Node* &o,int d)
{
	Node *k=o->son[d^1];
	o->son[d^1]=k->son[d];
	k->son[d]=o;
	maintain(o);
	maintain(k);
	o=k;
}

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->son[0]=o->son[1]=NULL;
	int mid=(l+r)/2;
	o->val=mid;
	o->flip=0;
	if(l<mid) build(o->son[0],l,mid-1);
	if(r>mid) build(o->son[1],mid+1,r);
	maintain(o);
}

void splay(Node* &o,int x)
{
	if(o==NULL) return;
	if(o->flip) pushdown(o);
	int sz=1;
	if(o->son[0]!=NULL) sz+=o->son[0]->sum;
	if(x<sz) splay(o->son[0],x),rotate(o,1);
	else if(x>sz) splay(o->son[1],x-sz),rotate(o,0);
}

void DFS(Node* &o)
{
	if(o==NULL) return;
	if(o->flip) pushdown(o);
	DFS(o->son[0]);
	printf("%d ",o->val);
	DFS(o->son[1]);
}

int main()
{
	int n,m,l,r;
	cin>>n>>m;
	build(root,1,n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&l,&r);
		if(l==r) continue;
		splay(root,l);
		int sz=1;
		if(root->son[0]!=NULL) sz+=root->son[0]->sum;
		splay(root->son[1],r-sz);
		swap(root->val,root->son[1]->val);
		if(root->son[1]->son[0]!=NULL) root->son[1]->son[0]->flip^=1;
	}
	DFS(root);
	return 0;
}
