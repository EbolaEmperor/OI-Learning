#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Node
{
	Node *lson,*rson;
	int sum;
};

Node *root[200010];
int a[200010],f[200010];

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->lson=o->rson=NULL;
	o->sum=0;
	if(l==r) return;
	int mid=(l+r)/2;
	build(o->lson,l,mid);
	build(o->rson,mid+1,r);
}

void updata(Node* &o,Node *pre,int l,int r,int x)
{
	o=new Node;
	o->lson=pre->lson;
	o->rson=pre->rson;
	o->sum=pre->sum+1;
	int mid=(l+r)/2;
	if(l==r) return;
	else if(x<=mid) updata(o->lson,pre->lson,l,mid,x);
	else updata(o->rson,pre->rson,mid+1,r,x);
}

int query(Node* &L,Node* &R,int l,int r,int x)
{
	int mid=(l+r)/2;
	if(l==r) return mid;
	int cnt=R->lson->sum-L->lson->sum;
	if(x<=cnt) return query(L->lson,R->lson,l,mid,x);
	else return query(L->rson,R->rson,mid+1,r,x-cnt);
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",a+i),f[i]=a[i];
	sort(f+1,f+1+n);
	int sz=unique(f+1,f+1+n)-(f+1);
	build(root[0],1,sz);
	for(int i=1;i<=n;i++) a[i]=lower_bound(f+1,f+1+sz,a[i])-f;
	for(int i=1;i<=n;i++) updata(root[i],root[i-1],1,sz,a[i]);
	int l,r,x;
	for(int T=1;T<=m;T++)
	{
		scanf("%d%d%d",&l,&r,&x);
		int pos=query(root[l-1],root[r],1,sz,x);
		printf("%d\n",f[pos]);
	}
	return 0;
}
