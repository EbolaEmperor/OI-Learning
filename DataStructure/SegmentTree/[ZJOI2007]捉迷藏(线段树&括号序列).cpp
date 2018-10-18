#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
#define newnode(x) x=new Node,x->lc=x->rc=null
using namespace std;

struct Edge{int from,to,next;} e[200010];
int h[100010],sum=0;
int dfn[100010],idex[300010],dfs_clock=0;
bool black[100010];
struct Node
{
	Node *lc,*rc;
	int c1,c2,l1,l2,r1,r2,dis;
	Node(){lc=rc=NULL;c1=c2=l1=l2=r1=r2=dis=0;}
};
Node *rt,*null;

void add_edge(int u,int v)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int fa)
{
	idex[++dfs_clock]=-1;
	idex[++dfs_clock]=u;
	dfn[u]=dfs_clock;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa) continue;
		dfs(e[tmp].to,u);
	}
	idex[++dfs_clock]=-2;
}

void val(Node* &o,int x)
{
	o->c1=o->c2=0;
	o->l1=o->l2=o->r1=o->r2=o->dis=-INF;
	if(x==-1) o->c2=1;
	else if(x==-2) o->c1=1;
	else if(black[x]) o->l1=o->l2=o->r1=o->r2=0;
}

void maintain(Node* &o)
{
	Node *a=o->lc,*b=o->rc;
	o->c1=a->c1+max(b->c1-a->c2,0);
	o->c2=b->c2+max(a->c2-b->c1,0);
	o->dis=max(max(a->dis,b->dis),max(a->r1+b->l2,a->r2+b->l1));
	o->l1=max(a->l1,max(b->l1+a->c1-a->c2,b->l2+a->c2+a->c1));
	o->l2=max(a->l2,b->l2+a->c2-a->c1);
	o->r1=max(b->r1,max(a->r1-b->c1+b->c2,a->r2+b->c1+b->c2));
	o->r2=max(b->r2,a->r2+b->c1-b->c2);
}

void build(Node* &o,int l,int r)
{
	newnode(o);
	if(l==r){val(o,idex[l]);return;}
	int mid=(l+r)/2;
	build(o->lc,l,mid);
	build(o->rc,mid+1,r);
	maintain(o);
}

void update(Node* &o,int l,int r,int x)
{
	if(l==r){val(o,idex[l]);return;}
	int mid=(l+r)/2;
	if(x<=mid) update(o->lc,l,mid,x);
	else update(o->rc,mid+1,r,x);
	maintain(o);
}

int main()
{
	newnode(null);
	int n,u,v,Q;
	cin>>n;
	for(int i=1;i<=n;i++) black[i]=1;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	build(rt,1,dfs_clock);
	cin>>Q;
	int cnt=n;
	for(int i=1;i<=Q;i++)
	{
		char ch=getchar();
		while(ch!='G'&&ch!='C') ch=getchar();
		if(ch=='G')
		{
			if(cnt==0) puts("-1");
			else if(cnt==1) puts("0");
			else printf("%d\n",rt->dis);
		}
		else
		{
			scanf("%d",&u);
			if(black[u]) cnt--;else cnt++;
			black[u]^=1;
			update(rt,1,dfs_clock,dfn[u]);
		}
	}
	return 0;
}
