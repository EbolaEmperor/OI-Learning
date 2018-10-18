#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int base=4111;
int a[110][10];
int bin[10];
ULL state[2][base];
int res[2][base];
int Hash[base],tot[2];
int n,m,k,ans=-1e8;

inline void upmax(int &x,const int &y){if(y>x) x=y;}

void push(ULL s,int num)
{
	int ss=s%base;
	while(Hash[ss])
	{
		if(state[k][Hash[ss]]==s)
		{
			upmax(res[k][Hash[ss]],num);
			return;
		}
		ss++;if(ss==base) ss=0;
	}
	Hash[ss]=++tot[k];
	state[k][tot[k]]=s;
	res[k][tot[k]]=num;
}

void gao(int i,int j)
{
	for(int u=1;u<=tot[k^1];u++)
	{
		ULL s=state[k^1][u];int num=res[k^1][u];
		int p=(s>>bin[j-1])&3,q=(s>>bin[j])&3;
		if(p==0&&q==0)
		{
			push(s,num);
			if(i<n&&j<m)
				push(s+(1<<bin[j-1])+(2<<bin[j]),num+a[i][j]);
		}
		else if(q==0&&p>0)
		{
			if(i<n) push(s,num+a[i][j]);
			if(j<m)
			{
				int tmp=s-p*(1<<bin[j-1]);
				tmp+=p*(1<<bin[j]);
				push(tmp,num+a[i][j]);
			}
		}
		else if(q>0&&p==0)
		{
			if(j<m) push(s,num+a[i][j]);
			if(i<n)
			{
				int tmp=s-q*(1<<bin[j]);
				tmp+=q*(1<<bin[j-1]);
				push(tmp,num+a[i][j]);
			}
		}
		else if(p==1&&q==1)
		{
			int cnt=1,tmp;
			for(int v=j+1;v<=m;v++)
			{
				int ss=(s>>bin[v])&3;
				if(ss==1) cnt++;
				if(ss==2) cnt--;
				if(!cnt)
				{
					tmp=s-(1<<bin[v]);
					break;
				}
			}
			tmp-=(1<<bin[j-1])+(1<<bin[j]);
			push(tmp,num+a[i][j]);
		}
		else if(p==2&&q==2)
		{
			int cnt=1,tmp;
			for(int v=j-2;v>=1;v--)
			{
				int ss=(s>>bin[v])&3;
				if(ss==2) cnt++;
				if(ss==1) cnt--;
				if(!cnt)
				{
					tmp=s+(1<<bin[v]);
					break;
				}
			}
			tmp-=(2<<bin[j-1])+(2<<bin[j]);
			push(tmp,num+a[i][j]);
		}
		else if(p==2&&q==1)
			push(s-(2<<bin[j-1])-(1<<bin[j]),num+a[i][j]);
		else if(s-(1<<bin[j-1])-(2<<bin[j])==0) upmax(ans,num+a[i][j]);
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	for(int i=0;i<=8;i++) bin[i]=(i<<1);
	tot[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			k^=1;tot[k]=0;
			memset(Hash,0,sizeof(Hash));
			gao(i,j);
		}
		for(int j=1;j<=tot[k];j++)
			state[k][j]<<=2;
	}
	printf("%d\n",ans);
	return 0;
}
