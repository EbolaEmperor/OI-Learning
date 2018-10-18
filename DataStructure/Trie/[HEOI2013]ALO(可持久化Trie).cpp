#include<bits/stdc++.h>
#define newnode(x) x=new Node(),x->ch[0]=x->ch[1]=null
#define INF 100000
using namespace std;

struct Node
{
	int id;
	Node* ch[2];
};
Node* root[50010];
Node* null;
struct XY{int v,id;} a[50010];
set<int> s;

void insert(Node *pre,int k,int x)
{
	newnode(root[k]);
	Node* now=root[k];
	for(int i=30;i>=0;i--)
	{
		now->id=pre->id+1;
		int j=(x>>i)&1;
		newnode(now->ch[j]);
		now->ch[j^1]=pre->ch[j^1];
		now=now->ch[j];
		pre=pre->ch[j];
	}
	now->id=pre->id+1;
}

int query(Node *p1,Node *p2,int x)
{
	int ans=0;
	for(int i=30;i>=0;i--)
	{
		int j=((x>>i)&1)^1;
		if(p1->ch[j]->id!=p2->ch[j]->id) ans|=(1<<i);
		else j^=1;
		p1=p1->ch[j];
		p2=p2->ch[j];
	}
	return ans;
}

bool cmp(const XY &x,const XY &y){return x.v>y.v;}

int main()
{
	null=new Node();
	null->ch[0]=null->ch[1]=null;
	null->id=-1;
	int n,l,r,ans=0;
	root[0]=null;
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i].v);
		a[i].id=i;
		insert(root[i-1],i,a[i].v);
	}
	sort(a+1,a+1+n,cmp);
	s.insert(-1);s.insert(-2);
	s.insert(INF+1);s.insert(INF+2);
	s.insert(a[1].id);
	set<int>::iterator x,y;
	for(int i=2;i<=n;i++)
	{
		x=y=s.lower_bound(a[i].id);
		x--;x--;y++;
		l=(*x)+1;r=(*y)-1;
		l=max(l,1);r=min(r,n);
		ans=max(ans,query(root[l-1],root[r],a[i].v));
		s.insert(a[i].id);
	}
	cout<<ans<<endl;
	return 0;
}
