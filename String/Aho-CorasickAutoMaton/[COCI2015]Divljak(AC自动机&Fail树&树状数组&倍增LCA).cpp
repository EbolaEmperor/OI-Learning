#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

const int N=2000010;
int ch[N][26],fail[N],sz=0;
int word[100010];
int bit[N];
int in[N],out[N],dfn=0;
char s[N];
struct Edge{int to,next;} e[2*N];
int h[N],sum=0;
int a[N];
int mul[N][23],dep[N];

void add(int p,int k)
{
	for(int i=p;i<=sz+1;i+=lowbit(i))
		bit[i]+=k;
}

int query(int p)
{
	int res=0;
	for(int i=p;i>0;i-=lowbit(i))
		res+=bit[i];
	return res;
}

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void insert(char *s,int k)
{
	int p=0,len=strlen(s);
	for(int i=0;i<len;i++)
	{
		int j=s[i]-'a';
		if(!ch[p][j]) ch[p][j]=++sz;
		p=ch[p][j];
	}
	word[k]=p;
}

void getfail()
{
	queue<int> q;
	q.push(0);
	while(!q.empty())
	{
		int u=q.front();
		for(int i=0;i<26;i++)
			if(ch[u][i])
			{
				int v=ch[u][i];
				if(u) fail[v]=ch[fail[u]][i];
				q.push(v);
			}
			else ch[u][i]=ch[fail[u]][i];
		q.pop();
	}
}

void dfs(int u,int la)
{
	in[u]=++dfn;
	for(int j=1;j<=20;j++) mul[u][j]=mul[mul[u][j-1]][j-1];
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		mul[v][0]=u;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
	out[u]=dfn;
}

int LCA(int p1,int p2)
{
	if(dep[p1]<dep[p2]) swap(p1,p2);
	for(int j=20;j>=0;j--)
		if(dep[mul[p1][j]]>=dep[p2]) p1=mul[p1][j];
	for(int j=20;j>=0;j--)
		if(mul[p1][j]!=mul[p2][j]) p1=mul[p1][j],p2=mul[p2][j];
	if(p1!=p2) p1=mul[p1][0];
	return p1;
}

bool cmp(const int &x,const int &y){return in[x]<in[y];}

void solve(char *s)
{
	int len=strlen(s),p=0;
	for(int i=0;i<len;i++) a[i]=p=ch[p][s[i]-'a'];
	sort(a,a+len,cmp);
	add(in[a[0]],1);
	for(int i=1;i<len;i++)
		if(a[i]!=a[i-1])
		{
			add(in[a[i]],1);
			int lca=LCA(a[i],a[i-1]);
			add(in[lca],-1);
		}
}

int main()
{
	int n,Q,opt,x;
	cin>>n;
	for(int i=1;i<=n;i++)
		scanf("%s",s),insert(s,i);
	getfail();
	for(int i=1;i<=sz;i++)
		add_edge(i,fail[i]),add_edge(fail[i],i);
	dfs(0,0);
	cin>>Q;
	for(int i=1;i<=Q;i++)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%s",s);
			solve(s);
		}
		else
		{
			scanf("%d",&x);x=word[x];
			printf("%d\n",query(out[x])-query(in[x]-1));
		}
	}
	return 0;
}
