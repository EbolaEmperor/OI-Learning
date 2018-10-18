#include<bits/stdc++.h>
#define MAX 200000
using namespace std;

const int N=100010;
struct Node
{
	Node *ls,*rs;
	int num;
};
Node* root[N<<1];

void Insert(Node* &o,Node* pre,int l,int r,int k)
{
	o=new Node;*o=*pre;
	o->num++;
	if(l==r) return;
	int mid=(l+r)/2;
	if(k<=mid) Insert(o->ls,pre->ls,l,mid,k);
	else Insert(o->rs,pre->rs,mid+1,r,k);
}

int Query(Node *L,Node *R,int l,int r,int nl,int nr)
{
	if(nr<nl) return 0;
	if(l>=nl&&r<=nr) return R->num-L->num;
	int mid=(l+r)/2,res=0;
	if(nl<=mid) res+=Query(L->ls,R->ls,l,mid,nl,nr);
	if(nr>mid) res+=Query(L->rs,R->rs,mid+1,r,nl,nr);
	return res;
}

int main()
{
	root[0]=new Node;
	root[0]->ls=root[0]->rs=root[0];
	int n,m,a,x,l,r,nl,nr;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a);
		Insert(root[i],root[i-1],0,MAX,a);
	}
	while(m--)
	{
		scanf("%d%d%d%d",&a,&x,&l,&r);
		int ans=0,fg;
		for(int i=17;i>=0;i--)
		{
			if(a&(1<<i)) nl=ans,nr=ans+(1<<i)-1,fg=0;
			else nl=ans+(1<<i),nr=ans+(1<<i+1)-1,fg=1;
			nl=max(nl-x,0);nr=min(nr-x,MAX);
			if(!Query(root[r],root[l-1],0,MAX,nl,nr)) fg^=1;
			ans|=fg<<i;
		}
		printf("%d\n",a^ans);
	}
	return 0;
}
