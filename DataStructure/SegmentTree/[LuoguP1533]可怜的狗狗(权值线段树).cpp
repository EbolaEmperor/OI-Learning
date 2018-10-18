#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Node
{
	Node *lson,*rson;
	int sum;
};

Node *root;
int a[300010],f[300010];
struct B{int l,r,k,id;} b[50010];
int ans[50010];

bool cmp(B x,B y){return x.l<y.l;}

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

void updata(Node* &o,int l,int r,int pos,int v)
{
	o->sum+=v;
	int mid=(l+r)/2;
	if(l==r) return;
	else if(pos<=mid) updata(o->lson,l,mid,pos,v);
	else updata(o->rson,mid+1,r,pos,v);
}

int query(Node* &o,int l,int r,int k)
{
	int mid=(l+r)/2;
	if(l==r) return mid;
	int cnt=o->lson->sum;
	if(k<=cnt) return query(o->lson,l,mid,k);
	else return query(o->rson,mid+1,r,k-cnt);
}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",a+i),f[i]=a[i];
	sort(f+1,f+1+n);
	int sz=unique(f+1,f+1+n)-(f+1);
	build(root,1,sz);
	for(int i=1;i<=n;i++) a[i]=lower_bound(f+1,f+1+sz,a[i])-f;
	for(int T=1;T<=m;T++)
	{
		scanf("%d%d%d",&b[T].l,&b[T].r,&b[T].k);
		b[T].id=T;
	}
	sort(b+1,b+1+m,cmp);
	int l=1,r=0;
	for(int T=1;T<=m;T++)
	{
		while(r<b[T].r) updata(root,1,n,a[++r],1);
		while(l<b[T].l) updata(root,1,n,a[l++],-1);
		ans[b[T].id]=f[query(root,1,n,b[T].k)];
	}
	for(int i=1;i<=m;i++) printf("%d\n",ans[i]);
	system("pause");
	return 0;
}
