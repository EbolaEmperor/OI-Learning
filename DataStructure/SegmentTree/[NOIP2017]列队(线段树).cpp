#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=1<<16;
	//Input Correlation
	char buf[S],*H,*T;
	inline char Get()
	{
		if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
		if(H==T) return -1;return *H++;
	}
	inline int read()
	{
		int x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x;
	}
	//Output Correlation
	char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
	inline void flush()
	{
		fwrite(obuf,1,oS-obuf,stdout);
		oS=obuf;
	}
	inline void putc(char x)
	{
		*oS++ =x;
		if(oS==oT) flush();
	}
	template <class I>
	inline void print(I x)
	{
		if(!x) putc('0');
		if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
	}
}

using namespace IO;
typedef long long LL;
const int N=300010,M=12000010;
int rt[N],ls[M],rs[M],num[M],tot=0;
vector<LL> back[N];
int n,m,q,mx;

int Query(int o,int l,int r,int k)
{
	if(l==r) return l;
	int mid=(l+r)/2,size=mid-l+1-num[ls[o]];
	if(k<=size) return Query(ls[o],l,mid,k);
	else return Query(rs[o],mid+1,r,k-size);
}

void Remove(int &o,int l,int r,int k)
{
	if(!o) o=++tot;num[o]++;
	if(l==r) return;
	int mid=(l+r)/2;
	if(k<=mid) Remove(ls[o],l,mid,k);
	else Remove(rs[o],mid+1,r,k);
}

LL gao1(int x,LL y)
{
	int p=Query(rt[n+1],1,mx,x);
	Remove(rt[n+1],1,mx,p);
	LL ans=(p<=n)?1ll*p*m:back[n+1][p-n-1];
	back[n+1].push_back(y?y:ans);
	return ans;
}

LL gao2(int x,int y)
{
	int p=Query(rt[x],1,mx,y);
	Remove(rt[x],1,mx,p);
	LL ans=(p<m)?1ll*(x-1)*m+p:back[x][p-m];
	back[x].push_back(gao1(x,ans));
	return ans;
}

int main()
{
	int x,y;LL ans;
	n=read();m=read();q=read();
	mx=max(n,m)+q;
	while(q--)
	{
		x=read();y=read();
		ans=y==m?gao1(x,0):gao2(x,y);
		print(ans);putc('\n');
	}
	flush();
	return 0;
}
