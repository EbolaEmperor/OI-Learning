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

const int N=100010;
int bit[2*N],k;

void Add(int p,int x){for(;p<=k;p+=lowbit(p))bit[p]+=x;}
int Sum(int p){int res=0;for(;p>0;p-=lowbit(p))res+=bit[p];return res;}

struct DATA{int x,y,z,id,w;} a[N],b[N];
int ans[N],f[N];

bool operator != (const DATA &m,const DATA &n){return m.x!=n.x||m.y!=n.y||m.z!=n.z;}

bool cmp1(const DATA &m,const DATA &n)
{
	if(m.x!=n.x) return m.x<n.x;
	if(m.y!=n.y) return m.y<n.y;
	return m.z<n.z;
}
bool cmp2(const DATA &m,const DATA &n){return m.y<n.y||m.y==n.y&&m.z<n.z;}

void CDQ(int L,int R)
{
	if(L==R) return;
	int M=(L+R)/2;
	CDQ(L,M);CDQ(M+1,R);
	sort(a+L,a+M+1,cmp2);
	sort(a+M+1,a+R+1,cmp2);
	int p1=L,p2=M+1,lst=0;
	while(p2<=R)
		if(p1<=M&&a[p1].y<=a[p2].y)
			Add(a[p1].z,a[p1].w),lst=p1++;
		else if(p2<=R)
			f[a[p2].id]+=Sum(a[p2].z),p2++;
	for(int i=L;i<=lst;i++)
		Add(a[i].z,-a[i].w);
}

int main()
{
	int n=read();k=read();
	for(int i=1;i<=n;i++)
	{
		b[i].x=read();
		b[i].y=read();
		b[i].z=read();
	}
	sort(b+1,b+1+n,cmp1);
	int tot=0,cnt=1;
	for(int i=1;i<=n;i++)
		if(b[i]!=b[i+1])
		{
			a[++tot]=b[i];
			a[tot].id=tot;
			a[tot].w=cnt;
			cnt=1;
		}
		else cnt++;
	CDQ(1,tot);
	for(int i=1;i<=tot;i++) ans[f[a[i].id]+a[i].w-1]+=a[i].w;
	for(int i=0;i<n;i++) printf("%d\n",ans[i]);
	return 0;
}
