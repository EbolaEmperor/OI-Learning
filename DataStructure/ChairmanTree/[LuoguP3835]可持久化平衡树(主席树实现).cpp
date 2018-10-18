#include<bits/stdc++.h>
using namespace std;

int read()
{
	int x=0,fg=1;char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-') fg=-1,c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return fg*x;
}

struct Node
{
	int v,mn,mx;
	Node *ls,*rs;
	Node(){v=0;ls=rs=NULL;mn=1e8;mx=0;}
};
Node* root[500010];
struct Qry{int v,opt,x;}qry[500010];
int Hash[500010],idx[500010],ans;

void maintain(Node *o)
{
	o->mn=min(o->ls->mn,o->rs->mn);
	o->mx=max(o->ls->mx,o->rs->mx);
}

void insert(Node* &o,Node *pre,int l,int r,int x)
{
	o=new Node;
	o->v=pre->v+1;
	o->ls=pre->ls;
	o->rs=pre->rs;
	if(l==r){o->mn=o->mx=l;return;}
	int mid=(l+r)/2;
	if(x<=mid) insert(o->ls,pre->ls,l,mid,x);
	else insert(o->rs,pre->rs,mid+1,r,x);
	maintain(o);
}

void remove(Node* &o,Node *pre,int l,int r,int x)
{
	if(pre->v==1){o=root[0];return;}
	o=new Node;
	o->v=pre->v-1;
	o->ls=pre->ls;
	o->rs=pre->rs;
	if(l==r) return;
	int mid=(l+r)/2;
	if(x<=mid) remove(o->ls,pre->ls,l,mid,x);
	else remove(o->rs,pre->rs,mid+1,r,x);
	maintain(o);
}

bool find(Node *o,int l,int r,int x)
{
	if(o==root[0]) return false;
	if(l==r) return true;
	int mid=(l+r)/2;
	if(x<=mid) return find(o->ls,l,mid,x);
	else return find(o->rs,mid+1,r,x);
}

int rank(Node *o,int l,int r,int x)
{
	if(l==r) return 1;
	int mid=(l+r)/2;
	if(x<=mid) return rank(o->ls,l,mid,x);
	else return rank(o->rs,mid+1,r,x)+o->ls->v;
}

int kth(Node *o,int l,int r,int k)
{
	if(l==r) return l;
	int mid=(l+r)/2,size=o->ls->v;
	if(k<=size) return kth(o->ls,l,mid,k);
	else return kth(o->rs,mid+1,r,k-size);
}

void pre(Node *o,int l,int r,int x)
{
	if(o==root[0]||l==r) return;
	int mid=(l+r)/2;
	if(x<=mid) pre(o->ls,l,mid,x);
	else ans=max(ans,o->ls->mx),pre(o->rs,mid+1,r,x);
}

void suc(Node *o,int l,int r,int x)
{
	if(o==root[0]||l==r) return;
	int mid=(l+r)/2;
	if(x>mid) suc(o->rs,mid+1,r,x);
	else ans=min(ans,o->rs->mn),suc(o->ls,l,mid,x);
}

int main()
{
	int n=read(),v,opt,x,m=0;
	root[0]=new Node;
	root[0]->ls=root[0]->rs=root[0];
	for(int T=1;T<=n;T++)
	{
		qry[T].v=read();
		qry[T].opt=read();
		qry[T].x=read();
		if(qry[T].opt!=4)
			Hash[++m]=qry[T].x;
	}
	sort(Hash+1,Hash+1+m);
	int tot=unique(Hash+1,Hash+1+m)-(Hash+1);
	for(int i=1;i<=n;i++)
		if(qry[i].opt!=4) qry[i].x=lower_bound(Hash+1,Hash+1+tot,qry[i].x)-Hash;
	for(int T=1;T<=n;T++)
	{
		v=qry[T].v;opt=qry[T].opt;x=qry[T].x;
		if(opt==1) insert(root[T],root[v],1,tot,x);
		if(opt==2)
		{
			if(find(root[v],1,tot,x))
				remove(root[T],root[v],1,tot,x);
			else root[T]=root[v];
		}
		if(opt==3) printf("%d\n",rank(root[v],1,tot,x));
		if(opt==4) printf("%d\n",Hash[kth(root[v],1,tot,x)]);
		if(opt==5)
		{
			ans=0;pre(root[v],1,tot,x);
			printf("%d\n",Hash[ans]);
		}
		if(opt==6)
		{
			ans=tot+1;suc(root[v],1,tot,x);
			printf("%d\n",Hash[ans]);
		}
		if(opt>=3) root[T]=root[v];
	}
	return 0;
}
