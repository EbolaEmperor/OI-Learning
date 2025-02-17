#include<bits/stdc++.h>
using namespace std;

const int N=500010;
int cnt[30],p[N],n,m;

void update(int x,int k){for(int i=0;i<=20;i++) if((x^p[x])&(1<<i)) cnt[i]+=k;}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<n;i++)
		scanf("%d",p+i),update(i,1);
	int x,y;
	while(m--)
	{
		scanf("%d%d",&x,&y);x--;y--;
		update(x,-1);update(y,-1);
		swap(p[x],p[y]);
		update(x,1);update(y,1);
		int ans=20;while(ans>=0&&!cnt[ans]) ans--;
		printf("%d\n",(ans>=0?1<<ans:0));
	}
	return 0;
}