#include<iostream>
#include<cstdio>
using namespace std;

struct Node
{
	Node *son[2];
	int v;
	int ord;
	int sum;
};

Node *root;
int a[80010],p[80010];
char opt[20];
int presum,sucsum;

void maintain(Node* &o)
{
	o->sum=1;
	if(o->son[0]!=NULL) o->sum+=o->son[0]->sum;
	if(o->son[1]!=NULL) o->sum+=o->son[1]->sum;
}

void rotate(Node* &o,int d)
{
	Node* k=o->son[d^1];
	o->son[d^1]=k->son[d];
	k->son[d]=o;
	maintain(o);
	maintain(k);
	o=k;
}

void splay(Node* &o,int x)
{
	if(o==NULL||o->ord==x) return;
	else if(x<o->ord) splay(o->son[0],x),rotate(o,1);
	else splay(o->son[1],x),rotate(o,0);
}

void build(Node* &o,int l,int r)
{
	int mid=(l+r)/2;
	o=new Node;
	o->v=a[mid];
	o->ord=mid;
	o->son[0]=o->son[1]=NULL;
	o->sum=1;
	if(l<mid) build(o->son[0],l,mid-1);
	if(r>mid) build(o->son[1],mid+1,r);
	maintain(o);
}

int rank(Node* &o,int x)
{
	if(o==NULL) return -1;
	int ss=0;
	if(o->son[0]!=NULL) ss=o->son[0]->sum;
	if(x==o->ord) return ss;
	else if(x<o->ord) return rank(o->son[0],x);
	else return ss+1+rank(o->son[1],x);
}

int kth(Node* &o,int x)
{
	if(o==NULL) return -1;
	int ss=0;
	if(o->son[0]!=NULL) ss=o->son[0]->sum;
	if(x>ss&&x<=ss+1) return o->v;
	else if(x<=ss) return kth(o->son[0],x);
	else return kth(o->son[1],x-ss-1);
}

void pre(Node* &o,int x,int &k,int &knum)
{
	if(o==NULL) return;
	if(o->ord<x)
	{
		if(o->ord>k) k=o->ord,knum=o->v;
		pre(o->son[1],x,k,knum);
	}
	else pre(o->son[0],x,k,knum);
}

void suc(Node* &o,int x,int &k,int &knum)
{
	if(o==NULL) return;
	if(o->ord>x)
	{
		if(o->ord<k) k=o->ord,knum=o->v;
		suc(o->son[0],x,k,knum);
	}
	else suc(o->son[1],x,k,knum);
}

int main()
{
	int n,m,x,y;
	cin>>n>>m;
	presum=0,sucsum=n+1;
	for(int i=1;i<=n;i++) scanf("%d",a+i),p[a[i]]=i;
	build(root,1,n);
	for(int T=1;T<=m;T++)
	{
		cin>>opt;
		if(opt[0]=='A') cin>>x,printf("%d\n",rank(root,p[x]));
		if(opt[0]=='Q') cin>>x,printf("%d\n",kth(root,x));
		if(opt[0]=='T')
		{
			cin>>x;
			splay(root,p[x]);
			if(root->son[1]==NULL)
			{
				root->son[1]=root->son[0];
				root->son[0]=NULL;
				maintain(root->son[1]);
			}
			else
			{
				while(root->son[1]->son[0]!=NULL) rotate(root->son[1],1);
				root->son[1]->son[0]=root->son[0];
				root->son[0]=NULL;
				maintain(root->son[1]);
			}
			p[x]=presum;
			presum--;
			root->ord=p[x];
		}
		if(opt[0]=='B')
		{
			cin>>x;
			splay(root,p[x]);
			if(root->son[0]==NULL)
			{
				root->son[0]=root->son[1];
				root->son[1]=NULL;
				maintain(root->son[0]);
			}
			else
			{
				while(root->son[0]->son[1]!=NULL) rotate(root->son[0],0);
				root->son[0]->son[1]=root->son[1];
				root->son[1]=NULL;
				maintain(root->son[0]);
			}
			p[x]=sucsum;
			sucsum++;
			root->ord=p[x];
		}
		if(opt[0]=='I')
		{
			cin>>x>>y;
			if(y==0) continue;
			else if(y==-1)
			{
				int pp=-1000000,ppnum;
				pre(root,p[x],pp,ppnum);
				splay(root,p[x]);
				splay(root->son[0],pp);
				swap(root->v,root->son[0]->v);
				swap(p[x],p[ppnum]);
			}
			else
			{
				int ss=1000000,ssnum;
				suc(root,p[x],ss,ssnum);
				splay(root,p[x]);
				splay(root->son[1],ss);
				swap(root->v,root->son[1]->v);
				swap(p[x],p[ssnum]);
			}
		}
	}
	return 0;
}
