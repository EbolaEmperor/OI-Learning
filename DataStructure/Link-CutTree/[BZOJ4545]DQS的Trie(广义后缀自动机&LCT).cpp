#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=200010;
int son[N][2],f[N],size[N];
int tag[N],sta[N],top=0;

bool nroot(int o){return son[f[o]][0]==o||son[f[o]][1]==o;}
void down(int o,int x){size[o]+=x;tag[o]+=x;}

void pushdown(int x)
{
	if(x&&tag[x])
	{
		if(son[x][0]) down(son[x][0],tag[x]);
		if(son[x][1]) down(son[x][1],tag[x]);
		tag[x]=0;
	}
}

void rotate(int x)
{
	int y=f[x],z=f[y],k=(son[y][1]==x),w=son[x][k^1];
	if(nroot(y)) son[z][son[z][1]==y]=x;
	son[x][k^1]=y;
	son[y][k]=w;
	if(w) f[w]=y;
	f[y]=x;
	f[x]=z;
}

void splay(int x)
{
	int y=x,z;
	top=0;
	sta[top++]=y;
	while(nroot(y)) sta[top++]=f[y],y=f[y];
	while(top>0) pushdown(sta[--top]);
	while(nroot(x))
	{
		y=f[x];z=f[y];
		if(nroot(y)) rotate((son[y][0]==x)^(son[z][0]==y)?x:y);
		rotate(x);
	}
}

void access(int x)
{
	int y=0;
	while(x)
	{
		splay(x);
		son[x][1]=y;
		y=x;x=f[x];
	}
}

void link(int x,int y)
{
	access(y);
	splay(y);
	size[y]+=size[x];
	tag[y]+=size[x];
	f[x]=y;
}

void cut(int x)
{
	access(x);
	splay(x);
	size[son[x][0]]-=size[x];
	tag[son[x][0]]-=size[x];
	f[son[x][0]]=0;
	son[x][0]=0;
}

int ch[N][26],prt[N],len[N];
int sz=1;
LL ans=0;

int insert(int p,int c)
{
	int np=++sz;len[np]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1,link(np,1);
	else
	{
		int q=ch[p][c];
		if(len[q]==len[p]+1) prt[np]=q,link(np,q);
		else
		{
			int nq=++sz;len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(ch[nq]));
			prt[nq]=prt[q];link(nq,prt[q]);
			cut(q);link(q,nq);link(np,nq);
			prt[q]=prt[np]=nq;
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	ans+=(LL)len[np]-len[prt[np]];
	access(np);splay(np);
	size[np]++;tag[np]++;
	return np;
}

struct Edge{int to,capa,mark,next;} e[2*N];
int h[N],tot=0;
int fa[N],pt[N];

void add_edge(int u,int v,int w,int m)
{
	e[++tot].to=v;
	e[tot].capa=w;
	e[tot].mark=m;
	e[tot].next=h[u];
	h[u]=tot;
}

void dfs(int u,int la,int mak)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].mark!=mak) continue;
		int v=e[tmp].to;
		if(v==la) continue;
		pt[v]=insert(pt[u],e[tmp].capa);
		fa[v]=u;dfs(v,u,mak);
	}
}

char qs[N];

int match()
{
	int p=1,l=strlen(qs);
	for(int i=0;i<l;i++)
	{
		int c=qs[i]-'a';
		if(!ch[p][c]) return 0;
		p=ch[p][c];
	}
	access(p);splay(p);
	return size[p];
}

int main()
{
	int id,n,u,v,mak=1;
	char s[10];
	scanf("%d%d",&id,&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%s",&u,&v,s);
		add_edge(u,v,s[0]-'a',mak);
		add_edge(v,u,s[0]-'a',mak);
	}
	pt[1]=1;
	dfs(1,0,mak);
	int Q,opt,rt,siz;
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%d",&opt);
		if(opt==1) printf("%lld\n",ans);
		if(opt==2)
		{
			mak++;
			scanf("%d%d",&rt,&siz);
			for(int i=1;i<siz;i++)
			{
				scanf("%d%d%s",&u,&v,s);
				add_edge(u,v,s[0]-'a',mak);
				add_edge(v,u,s[0]-'a',mak);
			}
			dfs(rt,fa[rt],mak);
		}
		if(opt==3)
		{
			scanf("%s",qs);
			printf("%d\n",match());
		}
	}
	return 0;
}