#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

struct Type_XY{int x,y,id,ans;} qry[100010];
int ch[100010][30],sz=0;
int father[100010],val[100010],fail[100010];
int word[100010],cnt[100010],ans[100010];
char s[100010];
int bit[100010];
struct Edge{int to,next;} e[200010];
int h[100010],sum=0;
int in[100010],out[100010],dfn=0;

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void add(int p,int k)
{
	for(int i=p;i<=dfn;i+=lowbit(i))
		bit[i]+=k;
}

int query(int p)
{
	int res=0;
	for(int i=p;i>0;i-=lowbit(i))
		res+=bit[i];
	return res;
}

bool operator < (const Type_XY &t1,const Type_XY &t2) {return t1.y<t2.y;}

void insert()
{
	scanf("%s",s);
	int n=strlen(s),u=0,cnt=0;
	for(int i=0;i<n;i++)
	{
		if(s[i]>='a'&&s[i]<='z')
		{
			int idx=s[i]-'a';
			if(ch[u][idx]==0)
			{
				ch[u][idx]=++sz;
				father[sz]=u;
			}
			u=ch[u][idx];
		}
		if(s[i]=='B') u=father[u];
		if(s[i]=='P') word[++cnt]=u,val[u]=cnt;
	}
}

void GetFail()
{
	queue<int> q;
	fail[0]=0;
	for(int i=0;i<26;i++)
		if(ch[0][i]!=0) q.push(ch[0][i]),fail[ch[0][i]]=0;
	while(!q.empty())
	{
		int o=q.front();
		//cout<<o<<endl;
		for(int i=0;i<26;i++)
			if(ch[o][i])
			{
				int v=ch[o][i];
				if(o) fail[v]=ch[fail[o]][i];
				q.push(v);
			}
			else ch[o][i]=ch[fail[o]][i];
		q.pop();
	}
}

void dfs(int u,int la)
{
	in[u]=++dfn;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==la) continue;
		dfs(e[tmp].to,u);
	}
	out[u]=dfn;
}

void solve()
{
	int p=0,len=strlen(s),k=1,cnt=0;
	for(int i=0;i<len;i++)
	{
		//cout<<i<<endl;
		if(s[i]>='a'&&s[i]<='z')
		{
			p=ch[p][s[i]-'a'];
			add(in[p],1);
		}
		if(s[i]=='B')
		{
			add(in[p],-1);
			p=father[p];
		}
		if(s[i]=='P')
		{
			cnt++;
			for(int j=k;qry[j].y==cnt;j++,k++)
			{
				int ans1=query(out[word[qry[j].x]]);
				int ans2=query(in[word[qry[j].x]]-1);
				qry[j].ans=ans1-ans2;
			}
		}
	}
}

int main()
{
	insert();
	GetFail();
	for(int i=1;i<=sz;i++)
		add_edge(i,fail[i]),add_edge(fail[i],i);
	dfs(0,0);
	int T;
	cin>>T;
	for(int tt=1;tt<=T;tt++)
	{
		scanf("%d%d",&qry[tt].x,&qry[tt].y);
		qry[tt].id=tt;
	}
	sort(qry+1,qry+1+T);
	solve();
	for(int i=1;i<=T;i++) ans[qry[i].id]=qry[i].ans;
	for(int i=1;i<=T;i++) printf("%d\n",ans[i]);
	return 0;
}
