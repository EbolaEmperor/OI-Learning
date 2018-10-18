#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;

int read()
{
	int x=0,fg=1;char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-') fg=-1,c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return fg*x;
}

const int N=500010;
vector<int> num[N<<2];
struct base
{
	int a[35],n;
	base(){memset(a,0,sizeof(a));}
	int& operator [] (const int &x){return a[x];}
} c;
set<pii> S;
set<pii>::iterator it;
int ans[N];

void insert(base &a,int x)
{
	if(a.n==30) return;
	for(int i=30;i>=0;i--)
		if(x&(1<<i))
		{
			if(a[i]) x^=a[i];
			else{a[i]=x;a.n++;break;}
		}
}

int query(base &a)
{
	int ans=0;
	for(int i=30;i>=0;i--)
		if((ans^a[i])>ans) ans^=a[i];
	return ans;
}

void insert(int o,int l,int r,int nl,int nr,int x)
{
	if(l>=nl&&r<=nr){num[o].push_back(x);return;}
	int mid=(l+r)/2;
	if(nl<=mid) insert(o*2,l,mid,nl,nr,x);
	if(nr>mid) insert(o*2+1,mid+1,r,nl,nr,x);
}

void dfs(int o,int l,int r,base bs)
{
	for(int i=0;i<num[o].size();i++)
		if(num[o][i]) insert(bs,num[o][i]);
	if(l==r){ans[l]=query(bs);return;}
	int mid=(l+r)/2;
	dfs(o*2,l,mid,bs);
	dfs(o*2+1,mid+1,r,bs);
}

int main()
{
	int n=read(),x;
	for(int i=1;i<=n;i++)
	{
		x=read();
		if(x>0) S.insert(pii(x,i));
		else
		{
			it=S.lower_bound(pii(-x,0));
			insert(1,1,n,it->second,i-1,it->first);
			S.erase(it);
		}
	}
	for(it=S.begin();it!=S.end();it++)
		insert(1,1,n,it->second,n,it->first);
	dfs(1,1,n,c);
	for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
	return 0;
}
