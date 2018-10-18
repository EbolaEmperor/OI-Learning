#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
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
		int x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x;
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
	}
}

using namespace IO;
typedef pair<int,int> pii;
const int N=300010,M=100010;
vector<pii> obj[M];
int sum[M];
int n,m;
int bit[M];

void Add(int p,int x){for(;p<=m;p+=lowbit(p)) bit[p]+=x;}
int Sum(int p){int res=0;for(;p;p-=lowbit(p)) res+=bit[p];return res;}

int main()
{
	int l,r;
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		l=read();r=read();
		obj[r-l+1].push_back(pii(l,r));
	}
	for(int i=m;i>=1;i--)
		sum[i]=sum[i+1]+obj[i].size();
	int pl=0;
	for(int i=1;i<=m;i++)
	{
		int ans=sum[i+1];
		while(pl<i)
		{
			pl++;
			for(int j=0;j<obj[pl].size();j++)
			{
				Add(obj[pl][j].first,1);
				Add(obj[pl][j].second+1,-1);
			}
		}
		for(int j=i;j<=m;j+=i) ans+=Sum(j);
		print(ans);putc('\n');
	}
	flush();
	return 0;
}
