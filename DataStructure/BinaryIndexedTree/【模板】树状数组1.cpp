#include<bits/stdc++.h>
using namespace std;

int c[500010],n;
int lowbit(int x){return x&-x;}
void add(int pos,int x)
{
	while(pos<=n)
	{
		c[pos]+=x;
		pos+=lowbit(pos);
	}
}
int query(int pos)
{
	int res=0;
	while(pos>0)
	{
		res+=c[pos];
		pos-=lowbit(pos);
	}
	return res;
}

int main()
{
	int m,a,b,opt;
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",&a),add(i,a);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&opt,&a,&b);
		if(opt==1) add(a,b);
		if(opt==2) printf("%d\n",query(b)-query(a-1));
	}
	return 0;
}
