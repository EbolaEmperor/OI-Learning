#include<bits/stdc++.h>
using namespace std;

const int N=6010;
struct Type{int x,y,c;} a[N];
int tot=0;
int b[N];

int main()
{
	int m,opt,x1,x2,y1,y2,k;
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&opt,&x1,&y1);
		if(opt==1)
		{
			scanf("%d",&k);
			a[++tot].x=x1;
			a[tot].y=y1;
			a[tot].c=-k;
		}
		else
		{
			int cnt=0;
			scanf("%d%d%d",&x2,&y2,&k);
			for(int i=1;i<=tot;i++)
				if(a[i].x>=x1&&a[i].x<=x2&&a[i].y>=y1&&a[i].y<=y2)
					b[++cnt]=a[i].c;
			nth_element(b+1,b+k,b+cnt+1);
			printf("%d\n",-b[k]);
		}
	}
	return 0;
}
