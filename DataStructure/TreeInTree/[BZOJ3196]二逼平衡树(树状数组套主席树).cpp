#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

const int N=50010;
struct Node{int ls,rs,sum;} t[N*150];
struct Type{int opt,l,r,k;} q[N];
int a[N],f[3*N];
int root[N],s[N];
int ra[N],rb[N];
int n,m,cnt=0,sz=0;

int lowbit(int x){return x&-x;}

void insert(int &o,int l,int r,int x,int addv,int ty)
{
	if(o==0||ty==1) t[++cnt]=t[o],o=cnt;
	t[o].sum+=addv;
	if(l==r) return;
	int mid=(l+r)/2;
	if(x<=mid) insert(t[o].ls,l,mid,x,addv,ty);
	else insert(t[o].rs,mid+1,r,x,addv,ty);
}

void copy(int l,int r)
{
	ra[0]=rb[0]=0;
	for(int i=l-1;i>0;i-=lowbit(i)) ra[++ra[0]]=s[i];
	for(int i=r;i>0;i-=lowbit(i)) rb[++rb[0]]=s[i];
}

int Rank(int L,int R,int l,int r,int x)
{
	if(x>r)
	{
		int tmp=t[R].sum-t[L].sum;
		for(int i=1;i<=ra[0];i++) tmp-=t[ra[i]].sum;
		for(int i=1;i<=rb[0];i++) tmp+=t[rb[i]].sum;
		return tmp;
	}
	int la[30],lb[30];
	for(int i=1;i<=ra[0];i++) la[i]=ra[i],ra[i]=t[ra[i]].ls;
	for(int i=1;i<=rb[0];i++) lb[i]=rb[i],rb[i]=t[rb[i]].ls;
	int mid=(l+r)/2;
	if(l==r) return 0;
	int sum=Rank(t[L].ls,t[R].ls,l,mid,x);
	if(x>mid+1)
	{
		for(int i=1;i<=ra[0];i++) ra[i]=t[la[i]].rs;
		for(int i=1;i<=rb[0];i++) rb[i]=t[lb[i]].rs;
		sum+=Rank(t[L].rs,t[R].rs,mid+1,r,x);
	}
	return sum;
}

int kth(int L,int R,int l,int r,int x)
{
	int mid=(l+r)/2;
	if(l==r) return mid;
	int tmp=t[t[R].ls].sum-t[t[L].ls].sum;
	for(int i=1;i<=ra[0];i++) tmp-=t[t[ra[i]].ls].sum;
	for(int i=1;i<=rb[0];i++) tmp+=t[t[rb[i]].ls].sum;
	if(tmp>=x)
	{
		for(int i=1;i<=ra[0];i++) ra[i]=t[ra[i]].ls;
		for(int i=1;i<=rb[0];i++) rb[i]=t[rb[i]].ls;
		return kth(t[L].ls,t[R].ls,l,mid,x);
	}
	else
	{
		for(int i=1;i<=ra[0];i++) ra[i]=t[ra[i]].rs;
		for(int i=1;i<=rb[0];i++) rb[i]=t[rb[i]].rs;
		return kth(t[L].rs,t[R].rs,mid+1,r,x-tmp);
	}
}

void updata(int x,int k,int addv)
{
	for(int i=x;i<=n;i+=lowbit(i))
		insert(s[i],1,sz,k,addv,0);
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",a+i),f[++sz]=a[i];
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&q[i].opt,&q[i].l,&q[i].r);
		if(q[i].opt==3) f[++sz]=q[i].r;
		else
		{
			scanf("%d",&q[i].k);
			if(q[i].opt!=2) f[++sz]=q[i].k;
		}
	}
	sort(f+1,f+1+sz);
	sz=unique(f+1,f+1+sz)-(f+1);
	for(int i=1;i<=n;i++)
	{
		int x=lower_bound(f+1,f+1+sz,a[i])-f;
		root[i]=root[i-1];
		insert(root[i],1,sz,x,1,1);
	}
	for(int i=1;i<=m;i++)
	{
		int opt=q[i].opt;
		if(opt==1)
		{
			copy(q[i].l,q[i].r);
			int x=lower_bound(f+1,f+1+sz,q[i].k)-f;
			printf("%d\n",Rank(root[q[i].l-1],root[q[i].r],1,sz,x)+1);
		}
		if(opt==2)
		{
			copy(q[i].l,q[i].r);
			printf("%d\n",f[kth(root[q[i].l-1],root[q[i].r],1,sz,q[i].k)]);
		}
		if(opt==3)
		{
			int x=lower_bound(f+1,f+1+sz,a[q[i].l])-f;
			int y=lower_bound(f+1,f+1+sz,q[i].r)-f;
			if(x==y) continue;
			updata(q[i].l,x,-1);
			updata(q[i].l,y,1);
			a[q[i].l]=q[i].r;
		}
		if(opt==4)
		{
			int x=lower_bound(f+1,f+1+sz,q[i].k)-f;
			copy(q[i].l,q[i].r);
			int p=Rank(root[q[i].l-1],root[q[i].r],1,sz,x);
			copy(q[i].l,q[i].r);
			if(p==0) printf("-2147483647\n");else printf("%d\n",f[kth(root[q[i].l-1],root[q[i].r],1,sz,p)]);
		}
		if(opt==5)
		{
			int x=lower_bound(f+1,f+1+sz,q[i].k)-f;
			copy(q[i].l,q[i].r);
			int p=Rank(root[q[i].l-1],root[q[i].r],1,sz,x+1);
			copy(q[i].l,q[i].r);
			if(p>q[i].r-q[i].l) printf("2147483647\n");
			else printf("%d\n",f[kth(root[q[i].l-1],root[q[i].r],1,sz,p+1)]);
		}
	}
	return 0;
}
