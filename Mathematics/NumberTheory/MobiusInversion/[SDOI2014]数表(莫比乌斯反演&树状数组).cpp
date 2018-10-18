#include<bits/stdc++.h>
#define INF 0x7fffffff
#define lowbit(x) (x&-x)
using namespace std;

const int N=100000;
struct QRY{int n,m,a,id;} qry[20010];
pair<int,int> f[N+10];
int prime[9592+10],tot=0;
int mu[N+10];
bool mark[N+10];
int bit[N],ans[N];

void Add(int p,int x){for(;p<=N;p+=lowbit(p))bit[p]+=x;}
int Sum(int p){int res=0;for(;p>0;p-=lowbit(p))res+=bit[p];return res;}
bool operator < (const QRY &a,const QRY &b){return a.a<b.a;}

void Init()
{
	mu[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) mu[i*prime[j]]=-mu[i];
			else mu[i*prime[j]]=0;
		}
	}
	for(int i=1;i<=N;i++)
		for(int j=i;j<=N;j+=i)
			f[j].first+=i;
	for(int i=1;i<=N;i++) f[i].second=i;
}

int main()
{
	Init();
	int Q;
	scanf("%d",&Q);
	for(int i=1;i<=Q;i++)
	{
		scanf("%d%d%d",&qry[i].n,&qry[i].m,&qry[i].a);
		qry[i].id=i;
	}
	sort(qry+1,qry+1+Q);
	sort(f+1,f+1+N);
	int pos=1;
	for(int T=1;T<=Q;T++)
	{
		while(pos<=N&&f[pos].first<=qry[T].a)
		{
			int k=f[pos].second;
			for(int j=k;j<=N;j+=k)
				Add(j,f[pos].first*mu[j/k]);
			pos++;
		}
		int div,n=qry[T].n,m=qry[T].m,res=0;
		if(n>m) swap(n,m);
		for(int i=1;i<=n;i=div+1)
		{
			div=min(n/(n/i),m/(m/i));
			res+=(n/i)*(m/i)*(Sum(div)-Sum(i-1));
		}
		ans[qry[T].id]=res&INF;
	}
	for(int i=1;i<=Q;i++) printf("%d\n",ans[i]);
	return 0;
}
