#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=1<<20;
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
		putc('\n');
	}
}

inline void upmax(int &x,const int &y){if(y>x) x=y;}

using namespace IO;
const int N=100010;
struct Qry{int x,y,z,id;} q[N],tmp1[N],tmp2[N];
struct Edge{int u,v;} e[N];
int fa[N],dep[N],size[N];
int n,m,top=0;
struct data{int x,fa,y,dep,size;} stk[N];
int ans[N],pr=0;
int cnt[N];

int find(int x){return fa[x]==x?x:find(fa[x]);}

int merge(int x,int y)
{
	x=find(x);y=find(y);
	if(x==y) return 0;
	if(dep[x]<=dep[y])
	{
		stk[++top]=(data){x,fa[x],y,dep[y],size[y]};
		fa[x]=y;upmax(dep[y],dep[x]+1);
		size[y]+=size[x];
	}
	else
	{
		stk[++top]=(data){y,fa[y],x,dep[x],size[x]};
		fa[y]=x;upmax(dep[x],dep[y]+1);
		size[x]+=size[y];
	}
	return 1;
}

void pop()
{
	fa[stk[top].x]=stk[top].fa;
	dep[stk[top].y]=stk[top].dep;
	size[stk[top].y]=stk[top].size;
	top--;
}

void devide(int l,int r,int ql,int qr)
{
	int mid=(l+r)/2;
	while(pr<mid) pr++,cnt[pr]+=merge(e[pr].u,e[pr].v);
	while(pr>mid){if(cnt[pr]) pop(),cnt[pr]--;pr--;}
	if(l==r)
	{
		for(int i=ql;i<=qr;i++)
			ans[q[i].id]=l;
		return;
	}
	int L=0,R=0;
	for(int i=ql;i<=qr;i++)
	{
		int x=find(q[i].x),y=find(q[i].y);
		int sz=(x==y)?size[x]:(size[x]+size[y]);
		if(q[i].z<=sz) tmp1[++L]=q[i];
		else tmp2[++R]=q[i];
	}
	for(int i=1;i<=L;i++) q[ql+i-1]=tmp1[i];
	for(int i=1;i<=R;i++) q[ql+L+i-1]=tmp2[i];
	if(L) devide(l,mid,ql,ql+L-1);
	if(R) devide(mid+1,r,ql+L,qr);
}

int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) fa[i]=i,dep[i]=size[i]=1;
	for(int i=1;i<=m;i++)
		e[i].u=read(),e[i].v=read();
	int Q=read(),x,y,z;
	for(int i=1;i<=Q;i++)
	{
		x=read();y=read();z=read();
		q[i]=(Qry){x,y,z,i};
	}
	devide(1,m,1,Q);
	for(int i=1;i<=Q;i++) print(ans[i]);
	flush();
	return 0;
}
