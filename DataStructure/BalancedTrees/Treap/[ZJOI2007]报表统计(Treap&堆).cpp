#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

int l[501000][2];
char opt[20];
int n,m,min_sort_gap=INF;
priority_queue<int> heap,del_heap;

struct Node
{
	int v,r;
	Node *son[2];
};
Node *root;

void rotate(Node* &o,int d)
{
	Node *k=o->son[d^1];
	o->son[d^1]=k->son[d];
	k->son[d]=o;
	o=k;
}

void insert(Node* &o,int x)
{
	if(o==NULL)
	{
		o=new Node;
		o->v=x;
		o->r=rand();
		o->son[0]=o->son[1]=NULL;
		return;
	}
	if(x<o->v)
	{
		insert(o->son[0],x);
		if(o->son[0]->r>o->r) rotate(o,1);
	}
	if(x>o->v)
	{
		insert(o->son[1],x);
		if(o->son[1]->r>o->r) rotate(o,0);
	}
}

void pre(Node* &o,int x,int &ans)
{
	if(o==NULL) return;
	if(o->v<=x)
	{
		ans=max(ans,o->v);
		pre(o->son[1],x,ans);
	}
	else pre(o->son[0],x,ans);
}

void suc(Node* &o,int x,int &ans)
{
	if(o==NULL) return;
	if(o->v>=x)
	{
		ans=min(ans,o->v);
		suc(o->son[0],x,ans);
	}
	else suc(o->son[1],x,ans);
}

int main()
{
	int x,y,ans;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&l[i][0]);
		l[i][1]=l[i][0];
		if(i>1) heap.push(-abs(l[i][0]-l[i-1][0]));
		ans=-INF;
		pre(root,l[i][0],ans);
		if(ans!=-INF) min_sort_gap=min(min_sort_gap,abs(l[i][0]-ans));
		ans=INF;
		suc(root,l[i][0],ans);
		if(ans!=INF) min_sort_gap=min(min_sort_gap,abs(l[i][0]-ans));
		insert(root,l[i][0]);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%s",opt);
		if(opt[0]=='I')
		{
			scanf("%d%d",&x,&y);
			del_heap.push(-abs(l[x+1][0]-l[x][1]));
			heap.push(-abs(y-l[x][1]));
			heap.push(-abs(y-l[x+1][0]));
			l[x][1]=y;
			ans=-INF;
			pre(root,y,ans);
			if(ans!=-INF) min_sort_gap=min(min_sort_gap,abs(y-ans));
			ans=INF;
			suc(root,y,ans);
			if(ans!=INF) min_sort_gap=min(min_sort_gap,abs(y-ans));
			insert(root,y);
		}
		else if(opt[4]=='G')
		{
			while(heap.top()==del_heap.top()) heap.pop(),del_heap.pop();
			printf("%d\n",-heap.top());
		}
		else printf("%d\n",min_sort_gap);
	}
	return 0;
}
