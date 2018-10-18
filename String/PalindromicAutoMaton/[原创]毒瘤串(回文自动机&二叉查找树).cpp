#include<bits/stdc++.h>
#define New(x) x=new Node,x->lc=x->rc=null
using namespace std;

typedef long long LL;
const int MAXN=3000010;
int ch[MAXN][4],sz;
int fail[MAXN],lst;
int len[MAXN],cnt[MAXN];
int s[MAXN],n;
LL f[MAXN];

int newnode(int l){len[++sz]=l;return sz;}

void init()
{
	lst=n=0;
	sz=-1;
	newnode(0);
	newnode(-1);
	fail[0]=1;
	s[0]=5;
}

int find(int p)
{
	while(s[n]!=s[n-len[p]-1]) p=fail[p];
	return p;
}

void insert(int c)
{
	s[++n]=c;
	int cur=s[n]>s[n-1]?1:find(lst);
	if(!ch[cur][c])
	{
		int now=newnode(len[cur]+2);
		fail[now]=ch[find(fail[cur])][c];
		ch[cur][c]=now;
	}
	lst=ch[cur][c];
	cnt[lst]++;
}

int read()
{
	int x=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

struct Node
{
	Node *lc,*rc;
	LL v,cnt,size;
	Node(){lc=rc=NULL;v=cnt=size=0;}
};
Node *rt,*null;

void build(Node* &o,int l,int r)
{
	New(o);
	LL mid=(l+r)/2;
	o->v=mid;
	o->cnt=f[mid];
	o->size=f[mid];
	if(l==r) return;
	if(l<mid) build(o->lc,l,mid-1);
	if(r>mid) build(o->rc,mid+1,r);
	o->size=o->lc->size+o->rc->size+o->cnt;
}

LL Kth(Node *o,LL k)
{
	LL sz=o->lc->size;
	if(k>sz&&k<=sz+o->cnt) return o->v;
	else if(k<=sz) return Kth(o->lc,k);
	else return Kth(o->rc,k-sz-o->cnt);
}

LL Rank(Node *o,LL x)
{
	LL sz=o->lc->size;
	if(o->v==x) return sz+1;
	else if(o->v>x) return Rank(o->lc,x);
	else return Rank(o->rc,x)+sz+o->cnt;
}

int main()
{
	New(null);
	int l=read();
	init();
	for(int i=0;i<l;i++)
		insert(read());
	int mx=0;
	for(int i=sz;i>=2;i--)
	{
		cnt[fail[i]]+=cnt[i];
		f[len[i]]+=cnt[i];
		mx=max(mx,len[i]);
	}
	build(rt,1,mx);
	int Q=read(),opt,x;
	for(int i=1;i<=Q;i++)
	{
		opt=read();x=read();
		if(opt==1926) printf("%lld\n",Kth(rt,x));
		else printf("%lld\n",Rank(rt,x));
	}
	return 0;
}
