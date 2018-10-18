#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

struct Line
{
	int k,b;
	int id;
} l[10010];
bool visible[10010];
int s[10010],top=0;

bool cmp(Line a,Line b){return a.k>b.k||(a.k==b.k&&a.b>b.b);}
double solve_x(Line a,Line b){return ((double)b.b-(double)a.b)/((double)a.k-(double)b.k);}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&l[i].b);
	for(int i=1;i<=n;i++) scanf("%d",&l[i].k),l[i].id=i;
	sort(l+1,l+1+n,cmp);
	memset(visible,0,sizeof(visible));
	for(int i=1;i<=n;i++)
	{
		if(i>1&&l[i].k==l[i-1].k&&l[i].b<l[i-1].b) continue;
		if(top>0&&solve_x(l[i],l[s[top]])<0) continue;
		while(top>1&&solve_x(l[s[top]],l[i])>solve_x(l[s[top]],l[s[top-1]])) visible[l[s[top]].id]=0,top--;
		s[++top]=i;
		visible[l[i].id]=1;
	}
	cout<<top<<endl;
	for(int i=1;i<=n;i++)
		if(visible[i]) printf("%d ",i);
	return 0;
}
