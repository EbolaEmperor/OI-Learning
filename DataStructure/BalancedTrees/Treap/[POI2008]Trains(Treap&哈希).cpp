#include<bits/stdc++.h>
#define newnode(x) x=new Node,x->son[0]=x->son[1]=null
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}

typedef unsigned long long ULL;
const int N=1010;
ULL f[N],p[N];
char s[N][110];
int tot=0;
int ans[N];

struct Node
{
	Node *son[2];
	int sz,v,tag,r;
	Node(){son[0]=son[1]=NULL;}
};
Node *null;
map<ULL,Node*> rt;

void down(Node* &o,int x)
{
	ans[o->v]=max(ans[o->v],x);
	o->tag=max(o->tag,x);
}

void pushdown(Node* &o)
{
	if(!o->tag) return;
	Node *lc=o->son[0];
	Node *rc=o->son[1];
	if(lc!=null) down(lc,o->tag);
	if(rc!=null) down(rc,o->tag);
	o->tag=0;
}

void maintain(Node* &o){o->sz=o->son[0]->sz+o->son[1]->sz+1;}

void rotate(Node* &o,int d)
{
	Node *k=o->son[d^1];
	pushdown(o);
	pushdown(k);
	o->son[d^1]=k->son[d];
	k->son[d]=o;
	maintain(o);
	maintain(k);
	o=k;
}

void insert(Node* &o,int x)
{
	if(o==null)
	{
		newnode(o);
		o->sz=1;
		o->v=x;
		o->tag=0;
		o->r=rand();
		return;
	}
	pushdown(o);
	if(x<o->v)
	{
		insert(o->son[0],x);
		if(o->son[0]->r>o->r) rotate(o,1);
		else maintain(o);
	}
	else
	{
		insert(o->son[1],x);
		if(o->son[1]->r>o->r) rotate(o,0);
		else maintain(o);
	}
}

void remove(Node* &o,int x)
{
	if(o==null) return;
	pushdown(o);
	if(o->v==x)
	{
		if(o->son[0]==null) o=o->son[1];
		else if(o->son[1]==null) o=o->son[0];
		else
		{
			if(o->son[0]->r>o->son[1]->r) rotate(o,1),remove(o->son[1],x);
			else rotate(o,0),remove(o->son[0],x);
		}
	}
	else if(x<o->v) remove(o->son[0],x);
	else remove(o->son[1],x);
	if(o!=null) maintain(o);
}

void insert(int x)
{
	if(!rt.count(f[x])) rt[f[x]]=null;
	insert(rt[f[x]],x);
	Node *o=rt[f[x]];
	down(o,o->sz);
}

int main()
{
	newnode(null);
	int n=read(),l=read(),m=read();
	p[0]=1;for(int i=1;i<=100;i++) p[i]=131*p[i-1];
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s[i]+1);
		for(int j=1;j<=l;j++)	
			f[i]=f[i]*131+s[i][j];
		insert(i);
	}
	for(int i=1;i<=m;i++)
	{
		int a=read(),b=read(),c=read(),d=read();
		if(a==c)
		{
			remove(rt[f[a]],a);
			f[a]+=p[l-b]*(s[a][d]-s[a][b]);
			f[a]+=p[l-d]*(s[a][b]-s[a][d]);
			swap(s[a][b],s[a][d]);
			insert(a);
			continue;
		}
		remove(rt[f[a]],a);remove(rt[f[c]],c);
		f[a]+=p[l-b]*(s[c][d]-s[a][b]);
		f[c]+=p[l-d]*(s[a][b]-s[c][d]);
		swap(s[a][b],s[c][d]);
		insert(a);insert(c);
	}
	for(int i=1;i<=n;i++) remove(rt[f[i]],i);
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
