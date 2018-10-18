#include<iostream>
#include<cstdio>
#include<cstdlib>
#define INF 0x7fffffff
#define MOD 1000000
using namespace std;

struct Node
{
	Node* son[2];
	long long v;
	int r;
};

Node *root_pet,*root_person;

void rotate(Node* &o,int d)
{
	Node* k=o->son[d^1];
	o->son[d^1]=k->son[d];
	k->son[d]=o;
	o=k;
}

void insert(Node* &o,long long x)
{
	if(o==NULL)
	{
		o=new Node;
		o->son[0]=o->son[1]=NULL;
		o->v=x;
		o->r=rand();
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

void remove(Node* &o,long long x)
{
	if(o==NULL) return;
	if(x==o->v)
	{
		if(o->son[0]==NULL) o=o->son[1];
		else if(o->son[1]==NULL) o=o->son[0];
		else
		{
			if(o->son[0]->r>o->son[1]->r) rotate(o,1),remove(o->son[1],x);
			else rotate(o,0),remove(o->son[0],x);
		}
	}
	else if(x<o->v) remove(o->son[0],x);
	else remove(o->son[1],x);
}

void pre(Node* &o,int x,long long &k)
{
	if(o==NULL) return;
	if(o->v==x) {k=o->v;return;}
	else if(o->v<x)
	{
		if(o->v>k) k=o->v;
		pre(o->son[1],x,k);
	}
	else pre(o->son[0],x,k);
}

void suc(Node* &o,int x,long long &k)
{
	if(o==NULL) return;
	if(o->v==x) {k=o->v;return;}
	else if(o->v>x)
	{
		if(o->v<k) k=o->v;
		suc(o->son[0],x,k);
	}
	else suc(o->son[1],x,k);
}

int main()
{
	root_person=root_pet=NULL;
	int sum=0;
	long long n,a,b;
	cin>>n;
	for(int T=1;T<=n;T++)
	{
		scanf("%lld%lld",&a,&b);
		if(a==0)
		{
			if(root_pet!=NULL||root_person==NULL) insert(root_pet,b);
			else
			{
				long long p=-INF,s=INF;
				pre(root_person,b,p);
				suc(root_person,b,s);
				int ans=min(abs(b-p),abs(b-s));
				if(ans==abs(b-p)) remove(root_person,p);else remove(root_person,s);
				sum=(sum+ans)%MOD;
			}
		}
		if(a==1)
		{
			if(root_person!=NULL||root_pet==NULL) insert(root_person,b);
			else
			{
				long long p=-INF,s=INF;
				pre(root_pet,b,p);
				suc(root_pet,b,s);
				int ans=min(abs(b-p),abs(b-s));
				if(ans==abs(b-p)) remove(root_pet,p);else remove(root_pet,s);
				sum=(sum+ans)%MOD;
			}
		}
	}
	cout<<sum<<endl;
}
