#include<bits/stdc++.h>
using namespace std;

const int N = 500010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0;
int n,m,s;
int mult[N][25];
int deep[N];

void add_edge(int u,int v){
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int fa){
	mult[u][0]=fa;
	for(int tmp=h[u];tmp;tmp=e[tmp].next){
		if(e[tmp].to==fa) continue;
		deep[e[tmp].to]=deep[u]+1;
		dfs(e[tmp].to,u);
	}
}

void mult_prepare(){
	for(int j=1;j<=19;j++)
		for(int i=1;i<=n;i++)
			mult[i][j]=mult[mult[i][j-1]][j-1];
}

int LCA(int p1,int p2){
	if(deep[p1]<deep[p2]) swap(p1,p2);
	for(int i=19;i>=0;i--)
		if((1<<i)<=deep[p1]-deep[p2])
			p1=mult[p1][i];
	for(int i=19;i>=0;i--)
		if(mult[p1][i]!=mult[p2][i])
			p1=mult[p1][i],p2=mult[p2][i];
	if(p1!=p2) p1=mult[p1][0];
	return p1;
}

int main(){
	int a,b;
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	dfs(s,0);
	mult_prepare();
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		printf("%d\n",LCA(a,b));
	}
	return 0;
}