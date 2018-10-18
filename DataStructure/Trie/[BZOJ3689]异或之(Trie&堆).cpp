#include<bits/stdc++.h>
#define newtrie(x) x=new Trie,x->ch[0]=x->ch[1]=null
using namespace std;

struct Trie
{
	Trie *ch[2];
	int size;
	Trie(){size=0;ch[0]=ch[1]=NULL;}
};
Trie *rt,*null;
struct QUE
{
	int a,k,v;
	QUE(int x=0,int y=0,int z=0):a(x),k(y),v(z){}
} t[100010];
priority_queue<QUE> h;

bool operator < (const QUE &x,const QUE &y){return x.v>y.v;}

void insert(int x)
{
	Trie *p=rt;
	for(int i=30;i>=0;i--)
	{
		int j=(x>>i)&1;
		if(p->ch[j]==null) newtrie(p->ch[j]);
		p=p->ch[j];
		p->size++;
	}
}

int kth(int x,int k)
{
	Trie *p=rt;
	int ans=0;
	for(int i=30;i>=0;i--)
	{
		int j=(x>>i)&1;
		if(p->ch[j]->size<k)
			k-=p->ch[j]->size,j^=1,ans|=(1<<i);
		p=p->ch[j];
	}
	return ans;
}

int main()
{
	newtrie(null);
	newtrie(rt);
	int n,k;cin>>n>>k;
	for(int i=1;i<=n;i++)
		scanf("%d",&t[i].a),insert(t[i].a);
	for(int i=1;i<=n;i++)
	{
		t[i].k=2;
		t[i].v=kth(t[i].a,2);
		h.push(t[i]);
	}
	printf("%d\n",h.top().v);
	for(int i=2;i<=2*k-1;i++)
	{
		QUE q=h.top();h.pop();q.k++;
		if(q.k<=n) q.v=kth(q.a,q.k),h.push(q);
		if(i&1) printf("%d ",h.top().v);
	}
	return 0;
}
