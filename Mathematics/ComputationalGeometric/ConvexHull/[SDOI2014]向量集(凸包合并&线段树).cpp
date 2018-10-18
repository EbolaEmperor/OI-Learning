#include<bits/stdc++.h>
#define INF 0x7fffffff
#define LINF (1ll<<60)
#define decode(x) (x^(lastans&INF))
using namespace std;

typedef long long LL;
const int N=400010;
struct PNT
{
	LL x,y;
	PNT(LL a=0,LL b=0):x(a),y(b){}
};

bool operator < (const PNT &a,const PNT &b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
PNT operator - (const PNT &a,const PNT &b){return PNT(a.x-b.x,a.y-b.y);}
LL Cross(const PNT &a,const PNT &b){return a.x*b.y-a.y*b.x;}
LL Dot(const PNT &a,const PNT &b){return a.x*b.x+a.y*b.y;}

vector<PNT> up[N<<2],down[N<<2];
int lc[N<<2],rc[N<<2],tot=0,root=0;

void merge_up(vector<PNT> &a,vector<PNT> &b,vector<PNT> &c)
{
	int n1=a.size(),n2=b.size(),p1=0,p2=0,top=0;PNT p;
	while(p1<n1||p2<n2)
	{
		if(p1>=n1) p=b[p2++];
		else if(p2>=n2) p=a[p1++];
		else if(a[p1]<b[p2]) p=a[p1++];
		else p=b[p2++];
		while(top>1&&Cross(p-c[top-2],c[top-1]-c[top-2])<=0) c.pop_back(),top--;
		c.push_back(p);top++;
	}
}

void merge_down(vector<PNT> &a,vector<PNT> &b,vector<PNT> &c)
{
	int n1=a.size(),n2=b.size(),p1=0,p2=0,top=0;PNT p;
	while(p1<n1||p2<n2)
	{
		if(p1>=n1) p=b[p2++];
		else if(p2>=n2) p=a[p1++];
		else if(a[p1]<b[p2]) p=a[p1++];
		else p=b[p2++];
		while(top>1&&Cross(p-c[top-2],c[top-1]-c[top-2])>=0) c.pop_back(),top--;
		c.push_back(p);top++;
	}
}

void insert(int &o,int l,int r,int x,PNT p)
{
	if(!o) o=++tot;
	if(l==r)
	{
		up[o].push_back(p);
		down[o].push_back(p);
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid) insert(lc[o],l,mid,x,p);
	else insert(rc[o],mid+1,r,x,p);
	if(r==x)
	{
		merge_up(up[lc[o]],up[rc[o]],up[o]);
		merge_down(down[lc[o]],down[rc[o]],down[o]);
	}
}

LL solve(vector<PNT> &a,PNT p)
{
	int l=0,r=a.size()-1;
	while(r-l>2)
	{
		int mid1=(2*l+r)/3,mid2=(l+2*r)/3;
		if(Dot(a[mid1],p)<Dot(a[mid2],p)) l=mid1;
		else r=mid2;
	}
	LL ans=-LINF;
	for(int i=l;i<=r;i++)
		ans=max(ans,Dot(a[i],p));
	return ans;
}

LL Query(int &o,int l,int r,int nl,int nr,PNT p)
{
	if(l>=nl&&r<=nr) return p.y>=0?solve(up[o],p):solve(down[o],p);
	int mid=(l+r)/2;
	LL ans=-LINF;
	if(nl<=mid) ans=max(ans,Query(lc[o],l,mid,nl,nr,p));
	if(nr>mid) ans=max(ans,Query(rc[o],mid+1,r,nl,nr,p));
	return ans;
}

int main()
{
	int n,l,r,cnt=0;
	LL lastans=0,x,y;
	char s[5];
	scanf("%d%s",&n,s);
	bool online=(s[0]!='E');
	for(int i=1;i<=n;i++)
	{
		scanf("%s%lld%lld",s,&x,&y);
		if(online) x=decode(x),y=decode(y);
		if(s[0]=='A') insert(root,1,n,++cnt,PNT(x,y));
		else
		{
			scanf("%d%d",&l,&r);
			if(online) l=decode(l),r=decode(r);
			lastans=Query(root,1,n,l,r,PNT(x,y));
			printf("%lld\n",lastans);
		}
	}
	return 0;
}
