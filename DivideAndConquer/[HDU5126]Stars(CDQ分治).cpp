#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int Q=50010;
int bit[Q<<1],hs,Hash[Q<<2];

void Add(int p,int k){for(;p<=hs;p+=lowbit(p))bit[p]+=k;}
int Sum(int p){int res=0;for(;p>0;p-=lowbit(p))res+=bit[p];return res;}

struct OPT
{
	int x,y,z,ty,id;//ty : 1(新增) 2(减询问) 3(加询问)
	OPT(int m1=0,int m2=0,int m3=0,int m4=0,int m5=0):
		ty(m1),x(m2),y(m3),z(m4),id(m5){}
}opt[Q<<3],ot[Q<<3];
int ans[Q];

bool cmpx(const OPT &m,const OPT &n){return m.x<n.x||m.x==n.x&&m.ty<n.ty;}
bool cmpy(const OPT &m,const OPT &n){return m.y<n.y||m.y==n.y&&m.ty<n.ty;}

void CDQ2(int L,int R)
{
	if(L==R) return;
	int M=(L+R)/2;
	CDQ2(L,M);CDQ2(M+1,R);
	sort(ot+L,ot+M+1,cmpy);
	sort(ot+M+1,ot+R+1,cmpy);
	int p1=L,p2=M+1,lst=0;
	while(p2<=R)
	{
		while(p1<=M&&ot[p1].ty!=1) p1++;
		while(p2<=R&&ot[p2].ty==1) p2++;
		if(p1<=M&&ot[p1].y<=ot[p2].y)
			Add(ot[p1].z,1),lst=p1++;
		else if(p2<=R)
		{
			int fg=(ot[p2].ty==2)?-1:1;
			ans[ot[p2].id]+=fg*Sum(ot[p2].z);
			p2++;
		}
	}
	for(int i=L;i<=lst;i++)
		if(ot[i].ty==1) Add(ot[i].z,-1);
}

void CDQ1(int L,int R)
{
	if(L==R) return;
	int M=(L+R)/2;
	CDQ1(L,M);CDQ1(M+1,R);
	int cnt=0;
	for(int p=L;p<=M;p++)
		if(opt[p].ty==1) ot[++cnt]=opt[p];
	for(int p=M+1;p<=R;p++)
		if(opt[p].ty!=1) ot[++cnt]=opt[p];
	if(cnt==0) return;
	sort(ot+1,ot+1+cnt,cmpx);
	CDQ2(1,cnt);
}

int main()
{
	int n=read(),tot=0,qt=0,m=0;
	for(int i=1;i<=n;i++)
	{
		int op=read(),x1=read(),y1=read(),z1=read();
		Hash[++m]=z1;
		if(op==1) opt[++tot]=OPT(1,x1,y1,z1,0);
		if(op==2)
		{
			qt++;int x2=read(),y2=read(),z2=read();
			Hash[++m]=z2;Hash[++m]=z1-1;
			opt[++tot]=OPT(3,x2,y2,z2,qt);
			opt[++tot]=OPT(2,x2,y2,z1-1,qt);
			opt[++tot]=OPT(2,x2,y1-1,z2,qt);
			opt[++tot]=OPT(2,x1-1,y2,z2,qt);
			opt[++tot]=OPT(3,x2,y1-1,z1-1,qt);
			opt[++tot]=OPT(3,x1-1,y2,z1-1,qt);
			opt[++tot]=OPT(3,x1-1,y1-1,z2,qt);
			opt[++tot]=OPT(2,x1-1,y1-1,z1-1,qt);
		}
	}
	sort(Hash+1,Hash+1+m);
	hs=unique(Hash+1,Hash+1+m)-(Hash+1);
	for(int i=1;i<=tot;i++)
		opt[i].z=lower_bound(Hash+1,Hash+1+hs,opt[i].z)-Hash;
	CDQ1(1,tot);
	for(int i=1;i<=qt;i++) printf("%d\n",ans[i]);
	return 0;
}
