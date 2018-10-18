#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
using namespace std;

struct Node
{
	int v;     //键值
	int r;     //优先级
	Node *son[2];
};

Node* root;

int abs(int a){return a>=0?a:-a;}

void rotate(Node* &o,int d)     //d=0左旋，d=1右旋
{
	Node* k=o->son[d^1];
	o->son[d^1]=k->son[d];
	k->son[d]=o;
	o=k;
}

void insert(Node* &o,int x)
{
	if(o==NULL)
	{
		o=new Node;
		o->son[0]=o->son[1]=NULL;
		o->r=rand();
		o->v=x;
	}
	else if(x<o->v)
	{
		insert(o->son[0],x);
		if(o->son[0]->r>o->r) rotate(o,1);
	}
	else if(x>o->v)
	{
		insert(o->son[1],x);
		if(o->son[1]->r>o->r) rotate(o,0);
	}
}

void pre(Node* &o,int x,int &k)
{
	if(o==NULL) return;
	if(o->v==x) k=o->v;
	else if(o->v<x)
	{
		if(o->v>k) k=o->v;
		pre(o->son[1],x,k);
	}
	else pre(o->son[0],x,k);
}

void suc(Node* &o,int x,int &k)
{
	if(o==NULL) return;
	if(o->v==x) k=o->v;
	else if(o->v>x)
	{
		if(o->v<k) k=o->v;
		suc(o->son[0],x,k);
	}
	else suc(o->son[1],x,k);
}

int main()
{
	int n,x;
	cin>>n;
	scanf("%d",&x);
	int ans=x;
	insert(root,x);
	for(int T=1;T<n;T++)
	{
		scanf("%d",&x);
		int p=-2000000,s=2000000;
		pre(root,x,p);
		suc(root,x,s);
		insert(root,x);
		ans+=min(abs(x-p),abs(x-s));
	}
	cout<<ans<<endl;
	return 0;
}
