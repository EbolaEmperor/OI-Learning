#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct Line
{
	int k,b;
	int id;
} l[50010];
bool visible[50010];
int s[50010];
int top=0;

void read(Line &a){scanf("%d%d",&a.k,&a.b);}
bool cmp(Line a,Line b){return a.k>b.k||(a.k==b.k&&a.b>b.b);}
double solve_x(Line a,Line b){return ((double)b.b-(double)a.b)/((double)a.k-(double)b.k);}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) read(l[i]),l[i].id=i;
	sort(l+1,l+1+n,cmp);
	memset(visible,0,sizeof(visible));
	for(int i=1;i<=n;i++)
	{
		if(i>1&&l[i].k==l[i-1].k) continue;
		while(top>1&&solve_x(l[s[top]],l[i])>=solve_x(l[s[top]],l[s[top-1]])) visible[l[s[top]].id]=0,top--;
		s[++top]=i;
		visible[l[i].id]=1;
	}
	for(int i=1;i<=n;i++)
		if(visible[i]) printf("%d ",i);
	return 0;
}
