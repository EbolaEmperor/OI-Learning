#include<bits/stdc++.h>
using namespace std;

struct Node
{
	Node *son[2],*fa;
	int val,sum,flip;
};
Node *root;

void Pushdown(Node* &o)
{
	if(o->son[0]!=NULL) o->son[0]->flip^=1;
	if(o->son[1]!=NULL) o->son[1]->flip^=1;
	swap(o->son[0],o->son[1]);
	o->flip^=1;
}

void Maintain(Node* &o)
{
	o->sum=1;
	if(o->son[0]!=NULL) o->sum+=o->son[0]->sum;
	if(o->son[1]!=NULL) o->sum+=o->son[1]->sum;
}

void Rotate(Node* &o,int d)
{
	if(o->flip) Pushdown(o);
	Node *y=o->fa;
	o->fa=y->fa;
	if(o->fa!=NULL)
	{
		if(o->fa->son[0]==y) o->fa->son[0]=o;
		else o->fa->son[1]=o;
	}
	if(o->son[d]!=NULL) o->son[d]->fa=y;
	y->son[d^1]=o->son[d];
	y->fa=o;
	o->son[d]=y;
	Maintain(y);
	Maintain(o);
}

void Splay(Node* &o,Node* s)
{
	Node *sf=s->fa;
	while(o->fa!=sf)
	{
		Node *y=o->fa;
		Node *z=y->fa;
		if(z==sf)
		{
			if(y->son[0]==o) Rotate(o,1);
			else Rotate(o,0);
		}
		else
			if(y->son[0]==o&&z->son[0]==y) Rotate(y,1),Rotate(o,1);
			else if(y->son[0]==o&&z->son[1]==y) Rotate(o,1),Rotate(o,0);
			else if(y->son[1]==o&&z->son[1]==y) Rotate(y,0),Rotate(o,0);
			else Rotate(o,0),Rotate(o,1);
	}
}

Node *Kth(Node *o,int x)
{
	if(o->flip) Pushdown(o);
	int sz=1;
	if(o->son[0]!=NULL) sz+=o->son[0]->sum;
	if(x==sz) return o;
	else if(x<sz) return Kth(o->son[0],x);
	else return Kth(o->son[1],x-sz);
}

void Build(Node* fa,Node* &o,int l,int r)
{
	int mid=(l+r)/2;
	o=new Node;
	o->val=mid;
	o->flip=0;
	o->son[0]=o->son[1]=NULL;
	o->fa=fa;
	if(l<mid) Build(o,o->son[0],l,mid-1);
	if(r>mid) Build(o,o->son[1],mid+1,r);
	Maintain(o);
}

void DFS(Node *o)
{
	if(o==NULL) return;
	if(o->flip) Pushdown(o);
	DFS(o->son[0]);
	printf("%d ",o->val);
	DFS(o->son[1]);
}

int main()
{
	int n,m,a,b;
	cin>>n>>m;
	Build(NULL,root,1,n);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(a==b) continue;
		Node *x=Kth(root,a);
		Splay(x,root);
		root=x;
		Node *y=Kth(root,b);
		Splay(y,root->son[1]);
		swap(root->val,root->son[1]->val);
		if(root->son[1]->son[0]!=NULL) root->son[1]->son[0]->flip^=1;
	}
	DFS(root);
	return 0;
}
