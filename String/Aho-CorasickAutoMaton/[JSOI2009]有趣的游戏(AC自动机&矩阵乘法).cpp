#include<bits/stdc++.h>
using namespace std;

int ch[110][15],fail[110],sz=0;
bool tag[110];
int n,l,m;
double psb[15];
char s[15];
int word[15];
struct Matrix{double a[110][110];} a;

void insert(char *s,int k)
{
	int p=0,len=strlen(s);
	for(int i=0;i<len;i++)
	{
		int j=s[i]-'A';
		if(!ch[p][j]) ch[p][j]=++sz;
		p=ch[p][j];
	}
	tag[p]=1;word[k]=p;
}

void getfail()
{
	queue<int> q;
	for(int i=0;i<m;i++)
		if(ch[0][i]) q.push(ch[0][i]);
	while(!q.empty())
	{
		int u=q.front();
		tag[u]|=tag[fail[u]];
		for(int i=0;i<m;i++)
			if(ch[u][i])
			{
				int v=ch[u][i];
				fail[v]=ch[fail[u]][i];
				q.push(v);
			}
			else ch[u][i]=ch[fail[u]][i];
		q.pop();
	}
}

Matrix operator * (Matrix &a,Matrix &b)
{
	Matrix c;
	for(int i=0;i<=sz;i++)
		for(int j=0;j<=sz;j++)
		{
			c.a[i][j]=0;
			for(int k=0;k<=sz;k++)
				c.a[i][j]+=a.a[i][k]*b.a[k][j];
		}
	return c;
}

int main()
{
	double p1,p2;
	memset(tag,0,sizeof(tag));
	cin>>n>>l>>m;
	for(int i=0;i<m;i++)
		scanf("%lf%lf",&p1,&p2),psb[i]=p1/p2;
	for(int i=1;i<=n;i++)
		scanf("%s",s),insert(s,i);
	getfail();
	for(int i=0;i<=sz;i++)
		if(tag[i]) a.a[i][i]=1;
		else for(int j=0;j<m;j++) a.a[i][ch[i][j]]+=psb[j];
	for(int i=1;i<=50;i++) a=a*a;
	for(int i=1;i<=n;i++)
		printf("%.2lf\n",a.a[0][word[i]]);
	return 0;
}
