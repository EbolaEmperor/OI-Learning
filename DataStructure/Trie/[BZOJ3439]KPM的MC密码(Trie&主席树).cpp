#include<bits/stdc++.h>
#define newseg(x) x=new Segment,x->lc=x->rc=null;
using namespace std;

struct Trie
{
	Trie *ch[26];
	vector<int> v;
	Trie(){for(int i=0;i<26;i++)ch[i]=NULL;}
};
Trie *root;
char s[500010];
int dfnl[500010],dfnr[500010],idex[500010],dfs_clock=0;

void insert(int id,char *s)
{
	Trie* o=root;
	int l=strlen(s);
	for(int i=l-1;i>=0;i--)
	{
		if(o->ch[s[i]-'a']==NULL)
			o->ch[s[i]-'a']=new Trie;
		o=o->ch[s[i]-'a'];
	}
	o->v.push_back(id);
}

int dfs(Trie *o)
{
	for(int i=0;i<o->v.size();i++)
		dfnl[o->v[i]]=dfs_clock+1;
	for(int i=0;i<o->v.size();i++)
		idex[++dfs_clock]=o->v[i];
	for(int i=0;i<26;i++)
		if(o->ch[i]) dfs(o->ch[i]);
	for(int i=0;i<o->v.size();i++)
		dfnr[o->v[i]]=dfs_clock;
}

struct Segment
{
	Segment *lc,*rc;
	int s;
	Segment(){lc=rc=NULL;s=0;}
};
Segment *rt[100010],*null;

void build(Segment* &o,Segment *pre,int l,int r,int x)
{
	newseg(o);
	o->s=pre->s+1;
	if(l==r) return;
	int mid=(l+r)/2;
	if(x<=mid) o->rc=pre->rc,build(o->lc,pre->lc,l,mid,x);
	else o->lc=pre->lc,build(o->rc,pre->rc,mid+1,r,x);
}

int kth(Segment *R,Segment *L,int l,int r,int x)
{
	if(l==r) return l;
	int size=R->lc->s-L->lc->s;
	int mid=(l+r)/2;
	if(x<=size) return kth(R->lc,L->lc,l,mid,x);
	else return kth(R->rc,L->rc,mid+1,r,x-size);
}

int main()
{
	newseg(null);
	int n,k;cin>>n;
	root=new Trie;
	for(int i=1;i<=n;i++) scanf("%s",s),insert(i,s);
	dfs(root);
	rt[0]=null;
	for(int i=1;i<=n;i++) build(rt[i],rt[i-1],1,n,idex[i]);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&k);
		if(rt[dfnr[i]]->s-rt[dfnl[i]-1]->s<k){puts("-1");continue;}
		printf("%d\n",kth(rt[dfnr[i]],rt[dfnl[i]-1],1,n,k));
	}
	return 0;
}
