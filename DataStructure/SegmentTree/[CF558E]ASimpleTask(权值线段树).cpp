#include<bits/stdc++.h>
using namespace std;

int n,q;
char s[100010];
struct Node
{
	Node *lson,*rson;
	int v,add,modify;
};
Node *rt[30];
int sum[30];

void pushdown(Node* &o,int l,int r)
{
	int mid=(l+r)/2,k=o->add,tag=o->modify;
	o->add=o->modify=0;
	if(l==r) return;
	if(tag)
	{
		o->lson->modify=1;
		o->rson->modify=1;
		o->lson->add=0;
		o->rson->add=0;
		o->lson->v=0;
		o->rson->v=0;
	}
	o->lson->add+=k;
	o->rson->add+=k;
	o->lson->v+=k*(mid-l+1);
	o->rson->v+=k*(r-mid);
}

void build(Node* &o,int l,int r)
{
	o=new Node;
	o->v=o->add=o->modify=0;
	o->lson=o->rson=NULL;
	if(l==r) return;
	int mid=(l+r)/2;
	build(o->lson,l,mid);
	build(o->rson,mid+1,r);
}

void add(Node* &o,int l,int r,int x,int y,int k)
{
	if(l>=x&&r<=y)
	{
		o->v+=k*(r-l+1);
		o->add+=k;
		return;
	}
	if(o->add||o->modify) pushdown(o,l,r);
	int mid=(l+r)/2;
	if(mid>=x) add(o->lson,l,mid,x,y,k);
	if(mid<y) add(o->rson,mid+1,r,x,y,k);
	o->v=o->lson->v+o->rson->v;
}

void clear(Node* &o,int l,int r,int x,int y)
{
	if(l>=x&&r<=y)
	{
		o->v=0;
		o->modify=1;
		o->add=0;
		return;
	}
	if(o->add||o->modify) pushdown(o,l,r);
	int mid=(l+r)/2;
	if(mid>=x) clear(o->lson,l,mid,x,y);
	if(mid<y) clear(o->rson,mid+1,r,x,y);
	o->v=o->lson->v+o->rson->v;
}

int query(Node* &o,int l,int r,int x,int y)
{
	if(l>=x&&r<=y) return o->v;
	if(o->add||o->modify) pushdown(o,l,r);
	int mid=(l+r)/2,res=0;
	if(mid>=x) res+=query(o->lson,l,mid,x,y);
	if(mid<y) res+=query(o->rson,mid+1,r,x,y);
	return res;
}

int main()
{
	int l,r,k;
	scanf("%d%d%s",&n,&q,s+1);
	for(int i=0;i<26;i++) build(rt[i],1,n);
	for(int i=1;i<=n;i++) add(rt[s[i]-'a'],1,n,i,i,1);
	for(int T=1;T<=q;T++)
	{
		scanf("%d%d%d",&l,&r,&k);
		memset(sum,0,sizeof(sum));
		for(int i=0;i<26;i++)
		{
			sum[i]=query(rt[i],1,n,l,r);
			clear(rt[i],1,n,l,r);
		}
		if(k==1)
		{
			int p=l;
			for(int i=0;i<26;i++)
				if(sum[i])
				{
					add(rt[i],1,n,p,p+sum[i]-1,1);
					p+=sum[i];
				}
		}
		else
		{
			int p=r;
			for(int i=0;i<26;i++)
				if(sum[i])
				{
					add(rt[i],1,n,p-sum[i]+1,p,1);
					p-=sum[i];
				}
		}
	}
	for(int i=1;i<=n;i++)
		for(int j=0;j<26;j++)
			if(query(rt[j],1,n,i,i)!=0){putchar('a'+j);break;}
	return 0;
}
