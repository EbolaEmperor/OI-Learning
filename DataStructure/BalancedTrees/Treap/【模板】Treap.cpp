#include<bits/stdc++.h>
using namespace std;

struct Node
{
	Node *son[2];
	int val,sum,cnt,r;
};
Node *root;

void maintain(Node* &o)
{
	if(o==NULL) return;
	o->sum=o->cnt;
	if(o->son[0]!=NULL) o->sum+=o->son[0]->sum;
	if(o->son[1]!=NULL) o->sum+=o->son[1]->sum;
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

void Insert(Node* &o,int x)
{
	if(o==NULL)
	{
		o=new Node;
		o->son[0]=o->son[1]=NULL;
		o->val=x;
		o->cnt=o->sum=1;
		o->r=rand();
		return;
	}
	if(o->val==x) o->cnt++;
	else if(o->val<x)
	{
		Insert(o->son[1],x);
		if(o->son[1]->r>o->r) rotate(o,0);
	}
	else
	{
		Insert(o->son[0],x);
		if(o->son[0]->r>o->r) rotate(o,1);
	}
	maintain(o);
}

void Remove(Node* &o,int x)
{
	if(o==NULL) return;
	if(o->val==x)
	{
		if(o->cnt>1) o->cnt--;
		else
		{
			if(o->son[0]==NULL) o=o->son[1];
			else if(o->son[1]==NULL) o=o->son[0];
			else
			{
				if(o->son[0]->r<o->son[1]->r) rotate(o,0),Remove(o->son[0],x);
				else rotate(o,1),Remove(o->son[1],x);
			}
		}
	}
	else if(o->val<x) Remove(o->son[1],x);
	else Remove(o->son[0],x);
	maintain(o);
}

int Rank(Node* &o,int x)
{
	if(o==NULL) return 0;
	int sz=0;
	if(o->son[0]!=NULL) sz=o->son[0]->sum;
	if(o->val==x) return sz+1;
	else if(o->val>x) return Rank(o->son[0],x);
	else return Rank(o->son[1],x)+sz+o->cnt;
}

int Kth(Node* &o,int x)
{
	if(o==NULL) return 0;
	int sz=0;
	if(o->son[0]!=NULL) sz=o->son[0]->sum;
	if(x>sz&&x<=sz+o->cnt) return o->val;
	else if(x<=sz) return Kth(o->son[0],x);
	else return Kth(o->son[1],x-sz-o->cnt);
}

void Pre(Node* &o,int x,int &ans)
{
	if(o==NULL) return;
	if(o->val<x)
	{
		ans=max(ans,o->val);
		Pre(o->son[1],x,ans);
	}
	else Pre(o->son[0],x,ans);
}

void Suc(Node* &o,int x,int &ans)
{
	if(o==NULL) return;
	if(o->val>x)
	{
		ans=min(ans,o->val);
		Suc(o->son[0],x,ans);
	}
	else Suc(o->son[1],x,ans);
}

int main()
{
	int n,opt,x;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1) Insert(root,x);
		if(opt==2) Remove(root,x);
		if(opt==3) printf("%d\n",Rank(root,x));
		if(opt==4) printf("%d\n",Kth(root,x));
		if(opt==5) {int ans=-0x7fffffff;Pre(root,x,ans);printf("%d\n",ans);}
		if(opt==6) {int ans=0x7fffffff;Suc(root,x,ans);printf("%d\n",ans);}
	}
	return 0;
}
