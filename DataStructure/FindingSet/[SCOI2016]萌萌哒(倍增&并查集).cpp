#include<bits/stdc++.h>
#define ha 1000000007
#define inv10 700000005
using namespace std;

const int N=100010;
int fa[18][N];

int find(int x,int p){return fa[p][x]==x?x:fa[p][x]=find(fa[p][x],p);}
void merge(int x,int y,int p){if(find(x,p)!=find(y,p)) fa[p][fa[p][x]]=y;}

int main()
{
	int l1,l2,r1,r2,n,m;
	scanf("%d%d",&n,&m);
	for(int p=0;p<=16;p++)
		for(int i=1;i<=n;i++)
			fa[p][i]=i;
	while(m--)
	{
		scanf("%d%d%d%d",&l1,&r1,&l2,&r2);
		for(int p=16;p>=0;p--)
			if(l1+(1<<p)-1<=r1)
				merge(l1,l2,p),l1+=1<<p,l2+=1<<p;
	}
	for(int p=16;p>0;p--)
		for(int i=1;i+(1<<p)-1<=n;i++)
			merge(i,find(i,p),p-1),
			merge(i+(1<<p-1),fa[p][i]+(1<<p-1),p-1);
	int ans=9;
	for(int i=1;i<=n;i++)
		if(find(i,0)==i) ans=1ll*ans*10%ha;
	printf("%d\n",1ll*ans*inv10%ha);
	return 0;
}
