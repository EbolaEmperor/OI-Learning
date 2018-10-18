#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int base=219797;
int a[15][15],bin[15];
ULL state[2][base],res[2][base];
int Hash[base],tot[2];
int n,m,k=0,nn,mm;
ULL ans=0;

void push(ULL s,ULL num)
{
	int ss=s%base;
	while(Hash[ss])
	{
		if(state[k][Hash[ss]]==s)
		{
			res[k][Hash[ss]]+=num;
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
	//printf("gao\n");
	for(int u=1;u<=tot[k^1];u++)
	{
		ULL s=state[k^1][u],num=res[k^1][u];
		//printf("%llu\n",s);
		int p=(s>>bin[j-1])&3,q=(s>>bin[j])&3;
		if(a[i][j]==0){if(p==0&&q==0) push(s,num);continue;}
		if(p==0&&q==0)
		{
			if(a[i][j]==1&&(a[i][j+1]==1||a[i][j+1]==2)&&(a[i+1][j]==1||a[i+1][j]==3))
				push(s+(1<<bin[j-1])+(2<<bin[j]),num);
		}
		else if(p>0&&q==0)
		{
			if(a[i][j]==1&&(a[i+1][j]==1||a[i+1][j]==3)) push(s,num);
			if((a[i][j]==1||a[i][j]==2)&&(a[i][j+1]==1||a[i][j+1]==2)) push(s-(p<<bin[j-1])+(p<<bin[j]),num);
		}
		else if(p==0&&q>0)
		{
			if(a[i][j]==1&&(a[i][j+1]==1||a[i][j+1]==2)) push(s,num);
			if((a[i][j]==1||a[i][j]==3)&&(a[i+1][j]==1||a[i+1][j]==3)) push(s-(q<<bin[j])+(q<<bin[j-1]),num);
		}
		else if(p==1&&q==1)
		{
			int cnt=1,tmp;
			for(int v=j+1;v<=m;v++)
			{
				int ss=(s>>bin[v])&3;
				if(ss==1) cnt++;
				if(ss==2) cnt--;
				if(!cnt){tmp=s-(1<<bin[v]);break;}
			}
			tmp-=(1<<bin[j-1])+(1<<bin[j]);
			push(tmp,num);
		}
		else if(p==2&&q==2)
		{
			int cnt=1,tmp;
			for(int v=j-2;v>=1;v--)
			{
				int ss=(s>>bin[v])&3;
				if(ss==2) cnt++;
				if(ss==1) cnt--;
				if(!cnt){tmp=s+(1<<bin[v]);break;}
			}
			tmp-=(2<<bin[j-1])+(2<<bin[j]);
			push(tmp,num);
		}
		else if(p==2&&q==1) push(s-(2<<bin[j-1])-(1<<bin[j]),num);
		else if(i==nn&&j==mm) ans+=num;
	}
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			char c=getchar();
			while(c!='.'&&c!='#'&&c!='|'&&c!='-') c=getchar();
			if(c=='.') a[i][j]=1;
			if(c=='-') a[i][j]=2;
			if(c=='|') a[i][j]=3;
			if(c!='#') nn=i,mm=j;
		}
	for(int i=0;i<15;i++) bin[i]=(i<<1);
	tot[0]=res[0][1]=1;
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
	printf("%llu\n",ans);
	return 0;
}
