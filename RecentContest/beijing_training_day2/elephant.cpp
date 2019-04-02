#include<bits/stdc++.h>
#define fr first
#define se second
using namespace std;

typedef pair<int,int> pii;
const int ha=323232323;
const int N=100010;
int qwq,m,n,q;

namespace Matrix
{
	struct Matrix
	{
		int a[2][2],n,m;
		int* operator [] (const int &x){return a[x];}
		Matrix(int _n=0,int _m=0):n(_n),m(_m){memset(a,0,sizeof(a));}
		Matrix operator * (Matrix &b)
		{
			Matrix res(n,b.m);
			for(int i=0;i<n;i++)
				for(int j=0;j<b.m;j++)
					for(int k=0;k<m;k++)
						res[i][j]=(res[i][j]+1ll*a[i][k]*b[k][j])%ha;
			return res;
		}
		friend Matrix operator ^ (Matrix a,int b)
		{
			Matrix res(a.n,a.m);
			res[0][0]=res[1][1]=1;
			for(;b;b>>=1,a=a*a)
				if(b&1) res=res*a;
			return res;
		}
	} mat1(2,2),mat2(2,1);
	void matrix_init()
	{
		mat1[0][1]=1;
		mat1[1][0]=(m-1)%ha;
		mat1[1][1]=(m-2)%ha;
		mat2[1][0]=(m-1)%ha;
	}
	int getf(int a)
	{
		if(a==-1) return 1;
		Matrix tmp=mat1;
		tmp=tmp^a;
		tmp=tmp*mat2;
		return tmp[0][0];
	}
}

namespace Treap1
{
	int lc[N],rc[N],sz[N],val[N],mn[N],tag[N],rev[N],rnd[N],rt=0;
	void pushdown(int o)
	{
		if(rev[o])
		{
			if(lc[o]) rev[lc[o]]^=1;
			if(rc[o]) rev[rc[o]]^=1;
			swap(lc[o],rc[o]);
			rev[o]=0;
		}
		if(tag[o])
		{
			if(lc[o])
			{
				val[lc[o]]+=tag[o];
				mn[lc[o]]+=tag[o];
				tag[lc[o]]+=tag[o];
			}
			if(rc[o])
			{
				val[rc[o]]+=tag[o];
				mn[rc[o]]+=tag[o];
				tag[rc[o]]+=tag[o];
			}
			tag[o]=0;
		}
	}
	inline void maintain(int o)
	{
		sz[o]=sz[lc[o]]+sz[rc[o]]+1;
		mn[o]=min(val[o],min(mn[lc[o]],mn[rc[o]]));
	}
	int merge(int o,int p)
	{
		if(!o||!p) return o|p;
		pushdown(o);pushdown(p);
		if(rnd[o]<rnd[p])
		{
			rc[o]=merge(rc[o],p);
			maintain(o);
			return o;
		}
		else
		{
			lc[p]=merge(o,lc[p]);
			maintain(p);
			return p;
		}
	}
	pii split(int o,int k)
	{
		if(!k) return pii(0,o);
		pushdown(o);
		if(k<=sz[lc[o]])
		{
			pii t=split(lc[o],k);
			lc[o]=t.se;
			maintain(o);
			return pii(t.fr,o);
		}
		else
		{
			pii t=split(rc[o],k-sz[lc[o]]-1);
			rc[o]=t.fr;
			maintain(o);
			return pii(o,t.se);
		}
	}
	void insert(int k,int x)
	{
		rnd[k]=rand();
		mn[k]=val[k]=x;
		sz[k]=1;
		rt=merge(rt,k);
	}
	void reverse(int l,int r)
	{
		pii t1=split(rt,l-1),t2=split(t1.se,r-l+1);
		rev[t2.fr]^=1;
		rt=merge(t1.fr,merge(t2.fr,t2.se));
	}
	int query(int k)
	{
		if(k==0) return 0;
		pii t1=split(rt,k-1),t2=split(t1.se,1);
		int res=val[t2.fr];
		rt=merge(t1.fr,merge(t2.fr,t2.se));
		return res;
	}
	int qmin(int l,int r)
	{
		pii t1=split(rt,l-1),t2=split(t1.se,r-l+1);
		int res=mn[t2.fr];
		rt=merge(t1.fr,merge(t2.fr,t2.se));
		return res;
	}
	void add(int l,int r,int x)
	{
		pii t1=split(rt,l-1),t2=split(t1.se,r-l+1);
		val[t2.fr]+=x;mn[t2.fr]+=x;tag[t2.fr]+=x;
		rt=merge(t1.fr,merge(t2.fr,t2.se));
	}
}

namespace Treap2
{
	int lc[N],rc[N],sz[N],gcd[N],val[N],rev[N],rnd[N],rt=0;
	void pushdown(int o)
	{
		if(!rev[o]) return;
		if(lc[o]) rev[lc[o]]^=1;
		if(rc[o]) rev[rc[o]]^=1;
		swap(lc[o],rc[o]);
		rev[o]=0;
	}
	inline void maintain(int o)
	{
		sz[o]=sz[lc[o]]+sz[rc[o]]+1;
		gcd[o]=__gcd(val[o],__gcd(gcd[lc[o]],gcd[rc[o]]));
	}
	int merge(int o,int p)
	{
		if(!o||!p) return o|p;
		pushdown(o);pushdown(p);
		if(rnd[o]<rnd[p])
		{
			rc[o]=merge(rc[o],p);
			maintain(o);
			return o;
		}
		else
		{
			lc[p]=merge(o,lc[p]);
			maintain(p);
			return p;
		}
	}
	pii split(int o,int k)
	{
		if(!k) return pii(0,o);
		pushdown(o);
		if(k<=sz[lc[o]])
		{
			pii t=split(lc[o],k);
			lc[o]=t.se;
			maintain(o);
			return pii(t.fr,o);
		}
		else
		{
			pii t=split(rc[o],k-sz[lc[o]]-1);
			rc[o]=t.fr;
			maintain(o);
			return pii(o,t.se);
		}
	}

	void dfs(int o)
	{
		if(!o) return;
		dfs(lc[o]);
		dfs(rc[o]);
	}

	void insert(int k,int x)
	{
		rnd[k]=rand();
		gcd[k]=val[k]=x;
		sz[k]=1;
		rt=merge(rt,k);
	}
	void reverse(int l,int r)
	{
		pii t1=split(rt,l-1),t2=split(t1.se,r-l+1);
		rev[t2.fr]^=1;
		rt=merge(t1.fr,merge(t2.fr,t2.se));
	}
	int query(int l,int r)
	{
		pii t1=split(rt,l-1),t2=split(t1.se,r-l+1);
		int res=gcd[t2.fr];
		rt=merge(t1.fr,merge(t2.fr,t2.se));
		return res;
	}
	void update(int k,int x)
	{
		pii t1=split(rt,k-1),t2=split(t1.se,1);
		val[t2.fr]=gcd[t2.fr]=x;
		rt=merge(t1.fr,merge(t2.fr,t2.se));
	}
}

void prework()
{
	Treap1::mn[0]=2100000000;
	for(int i=1,pre=0,x;i<=n;i++)
	{
		scanf("%d",&x);x--;
		Treap1::insert(i,x);
		Treap2::insert(i,abs(x-pre));
		pre=x;
	}
}
int gcd(int l,int r)
{
	if(Treap1::qmin(l,r)==-1) return -1;
	int res=Treap1::query(l);
	if(l<r) res=__gcd(res,Treap2::query(l+1,r));
	return res;
}
inline void update(int k){Treap2::update(k,abs(Treap1::query(k)-Treap1::query(k-1)));}
void reverse(int l,int r)
{
	Treap1::reverse(l,r);
	if(l<r) Treap2::reverse(l+1,r);
	update(l);
	if(r<n) update(r+1);
}
void add(int l,int r,int k)
{
	Treap1::add(l,r,k);
	update(l);
	if(r<n) update(r+1);
}

int main()
{
	scanf("%d%d%d%d",&qwq,&m,&n,&q);
	Matrix::matrix_init();
	prework();
	int opt,l,r,k;
	while(q--)
	{
		scanf("%d%d%d",&opt,&l,&r);
		if(opt==1) printf("%d\n",Matrix::getf(gcd(l,r)));
		if(opt==2) reverse(l,r);
		if(opt==3) scanf("%d",&k),add(l,r,k);
	}
	return 0;
}