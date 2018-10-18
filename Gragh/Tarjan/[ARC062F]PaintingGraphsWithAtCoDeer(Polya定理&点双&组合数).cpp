#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=210;
struct Edge{int to,next;} e[N];
int h[N],sum=0,n,m,K;
int low[N],pre[N],dfn=0;
stack<int> s;
set<int> scc;
int C[N][N];
int ans=1;

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void Init()
{
	for(int i=0;i<=200;i++) C[i][0]=1;
	for(int i=1;i<=200;i++)
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%ha;
}

int Polya(int n)
{
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=(ans+Pow(K,__gcd(i,n)))%ha;
	return 1ll*ans*Pow(n,ha-2)%ha;
}

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void Tarjan(int u,int fa)
{
	low[u]=pre[u]=++dfn;s.push(u);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(!pre[v])
		{
			Tarjan(v,u);
			low[u]=min(low[u],low[v]);
			if(low[v]>=pre[u])
			{
				scc.clear();
				int o,cnt=0;
				do{
					o=s.top();
					scc.insert(o);
					s.pop();
				}while(o!=v);
				scc.insert(u);
				for(int x : scc)
					for(int t=h[x];t;t=e[t].next)
						if(scc.count(e[t].to)) cnt++;
				cnt>>=1;
				if(cnt<scc.size()) ans=1ll*ans*K%ha;
				if(cnt==scc.size()) ans=1ll*ans*Polya(cnt)%ha;
				if(cnt>scc.size()) ans=1ll*ans*C[cnt+K-1][K-1]%ha;
			}
		}
		else low[u]=min(low[u],pre[v]);
	}
	if(!fa) s.pop();
}

int main()
{
	int u,v;Init();
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++)
		if(!pre[i]) Tarjan(i,0);
	printf("%d\n",ans);
	return 0;
}
