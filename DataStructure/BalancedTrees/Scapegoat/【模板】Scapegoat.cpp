#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=(1<<20)+5;
	//Input Correlation
	char buf[S],*H,*T;
	inline char Get()
	{
		if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
		if(H==T) return -1;return *H++;
	}
	inline int read()
	{
		int x=0,fg=1;char c=Get();
		while(!isdigit(c)&&c!='-') c=Get();
		if(c=='-') fg=-1,c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x*fg;
	}
	//Output Correlation
	char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
	inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
	template <class I>inline void print(I x)
	{
		if(!x) putc('0');
		if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		putc('\n');
	}
}

using namespace IO;
const double alpha=0.75;
struct Node
{
	Node *ls,*rs;
	int val,size,cnt;
	bool deleted;
	Node(int x=0):val(x){}
	bool isbad(){return ls->cnt>alpha*cnt+5||rs->cnt>alpha*cnt+5;}
	void maintain(){size=ls->size+rs->size+!deleted;cnt=ls->cnt+rs->cnt+1;}
} *rt,*null;
vector<Node*> A;

void flatten(Node *o)
{
	if(o->ls!=null) flatten(o->ls);
	if(!o->deleted) A.push_back(o);
	if(o->rs!=null) flatten(o->rs);
	if(o->deleted) delete o;
}

void rebuild(Node* &o,int l,int r)
{
	int mid=(l+r)/2;
	o=A[mid-1];o->ls=o->rs=null;
	if(l<mid) rebuild(o->ls,l,mid-1);
	if(r>mid) rebuild(o->rs,mid+1,r);
	o->maintain();
}

void rebuild(Node* &o)
{
	A.clear();
	flatten(o);
	rebuild(o,1,A.size());
}

void insert(Node* &o,int x)
{
	if(o==null)
	{
		o=new Node(x);
		o->ls=o->rs=null;
		o->size=o->cnt=1;
		o->deleted=0;
		return;
	}
	if(o->isbad()) rebuild(o);
	if(x>=o->val) insert(o->rs,x);
	else insert(o->ls,x);
	o->maintain();
}

void remove(Node *o,int k)
{
	o->size--;
	if(!o->deleted&&k==o->ls->size+1)
	{
		o->deleted=1;
		return;
	}
	if(k<=o->ls->size+!o->deleted) remove(o->ls,k);
	else remove(o->rs,k-o->ls->size-!o->deleted);
}

int Rank(Node *o,int x)
{
	int ans=1;
	while(o!=null)
	{
		if(o->val>=x) o=o->ls;
		else
		{
			ans+=o->ls->size+!o->deleted;
			o=o->rs;
		}
	}
	return ans;
}

int Kth(Node *o,int k)
{
	while(o!=null)
	{
		if(!o->deleted&&o->ls->size+1==k) return o->val;
		if(o->ls->size>=k) o=o->ls;
		else
		{
			k-=o->ls->size+!o->deleted;
			o=o->rs;
		}
	}
}

int main()
{
	null=new Node;rt=null;
	int n=read(),op,x;
	while(n--)
	{
		op=read();x=read();
		if(op==1) insert(rt,x);
	    if(op==2) remove(rt,Rank(rt,x));
	    if(op==3) print(Rank(rt,x));
		if(op==4) print(Kth(rt,x));
	    if(op==5) print(Kth(rt,Rank(rt,x)-1));
	    if(op==6) print(Kth(rt,Rank(rt,x+1)));
	}
	flush();
	return 0;
}
