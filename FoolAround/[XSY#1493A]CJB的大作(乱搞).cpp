#include<bits/stdc++.h>
#define mx 2000000000000000000ll
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
	template<class I> inline I read()
	{
		I x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x;
	}
	inline void reads(char *s)
	{
		char c=Get();int tot=-1;
		while(c<'a'||c>'z') c=Get();
		while(c>='a'&&c<='z') s[++tot]=c,c=Get();
		s[++tot]='\0';
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
typedef long long LL;
LL cnt[110][27],sum[64][110][27];
char s[110];
int k[100010],n;
LL len;

char getch(int dep,LL p)
{
	if(dep==0) return s[p];
	if(p<(len<<dep-1)) return getch(dep-1,p);
	if(p<(len<<dep-1)+k[dep]) return getch(dep-1,p-k[dep]);
	return getch(dep-1,p-(len<<dep-1)-k[dep]);
}

LL getans(int dep,LL p,char c)
{
	if(dep==0) return cnt[p][c-'a'];
	if(p<(len<<dep-1)) return getans(dep-1,p,c);
	if(p<(len<<dep-1)+k[dep]) return cnt[len-1][c-'a']*(1ll<<dep-1)+sum[dep][p-(len<<dep-1)][c-'a'];
	return getans(dep-1,p-(len<<dep-1)-k[dep],c)+cnt[len-1][c-'a']*(1ll<<dep-1)+sum[dep][k[dep]-1][c-'a'];
}

LL getans(LL p,char c)
{
	if(p==-1) return 0;
	int t;for(t=1;(len<<t)<=p;t++);
	return getans(t,p,c);
}

int main()
{
	reads(s);len=strlen(s);
	for(int i=0;i<len;i++)
	{
		cnt[i][s[i]-'a']++;
		if(i) for(int j=0;j<26;j++) cnt[i][j]+=cnt[i-1][j];
	}
	n=read<int>();
	int m=read<int>();LL l,r;char c;
	for(int i=1;i<=n;i++) k[i]=read<int>();
	for(int t=1;(len<<t)<=mx;t++)
	{
		k[t]%=len<<t-1;
		for(int i=0;i<k[t];i++)
		{
			c=getch(t,(len<<t-1)+i);
			sum[t][i][c-'a']++;
			if(i) for(int j=0;j<26;j++) sum[t][i][j]+=sum[t][i-1][j];
		}
	}
	while(m--)
	{
		l=read<LL>()-1;r=read<LL>()-1;
		c=Get();while(c<'a'||c>'z') c=Get();
		print(getans(r,c)-getans(l-1,c));
	}
	flush();
	return 0;
}
