#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct Node
{
	Node* son[2];
	char v;
	int sum;
};

Node *root,*tmp;
char s[2100000],opt[20];

void maintain(Node* &o)
{
	o->sum=1;
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

void splay(Node* &o,int k)
{
	if(o==NULL) return;
	int ss=0;
	if(o->son[0]!=NULL) ss=o->son[0]->sum;
	if(k>ss&&k<=ss+1) return;
	else if(k<=ss) splay(o->son[0],k),rotate(o,1);
	else if(k>ss+1) splay(o->son[1],k-ss-1),rotate(o,0);
}

void build(Node* &o,int l,int r)
{
	int mid=(l+r)/2;
	o=new Node;
	o->son[0]=o->son[1]=NULL;
	o->v=s[mid];
	o->sum=1;
	if(l<mid) build(o->son[0],l,mid-1);
	if(r>mid) build(o->son[1],mid+1,r);
	maintain(o);
}

void DFS(Node* &o)
{
	if(o->son[0]!=NULL) DFS(o->son[0]);
	printf("%c",o->v);
	if(o->son[1]!=NULL) DFS(o->son[1]);
}

int main()
{
	int t,pos=0,x;
	cin>>t;
	for(int T=1;T<=t;T++)
	{
		scanf("%s",opt);
		if(opt[0]=='P') pos--;
		if(opt[0]=='N') pos++;
		if(opt[0]=='M') scanf("%d",&x),pos=x;
		if(opt[0]=='I')
		{
			scanf("%d",&x);
			for(int i=1;i<=x;i++)
			{
				s[i]=getchar();
				if(s[i]<32||s[i]>126) i--;
			}
			tmp=NULL;
			build(tmp,1,x);
			if(root==NULL) root=tmp;
			else if(pos==0)
			{
				splay(root,1);
				root->son[0]=tmp;
				maintain(root);
			}
			else
			{
				splay(root,pos);
				if(root->son[1]==NULL)
				{
					root->son[1]=tmp;
					maintain(root);
				}
				else
				{
					while(root->son[1]->son[0]!=NULL) rotate(root->son[1],1);
					root->son[1]->son[0]=tmp;
					maintain(root->son[1]);
					maintain(root);
				}
			}
		}
		if(opt[0]=='D')
		{
			scanf("%d",&x);
			if(pos==0)
			{
				if(pos+x==root->sum) root=NULL;
				else
				{
					splay(root,pos+x+1);
					root->son[0]=NULL;
					maintain(root);
				}
			}
			else
			{
				splay(root,pos);
				if(pos+x==root->sum)
				{
					root->son[1]=NULL;
					maintain(root);
				}
				else
				{
					int ss=0;
					if(root->son[0]!=NULL) ss=root->son[0]->sum;
					splay(root->son[1],pos+x-ss);
					root->son[1]->son[0]=NULL;
					maintain(root->son[1]);
					maintain(root);
				}
			}
		}
		if(opt[0]=='G')
		{
			scanf("%d",&x);
			if(pos==0)
			{
				if(pos+x==root->sum) DFS(root);
				else
				{
					splay(root,pos+x+1);
					DFS(root->son[0]);
				}
			}
			else
			{
				splay(root,pos);
				if(pos+x==root->sum) DFS(root->son[1]);
				else
				{
					int ss=0;
					if(root->son[0]!=NULL) ss=root->son[0]->sum;
					splay(root->son[1],pos+x-ss);
					DFS(root->son[1]->son[0]);
				}
			}
			printf("\n");
		}
	}
	return 0;
}
