#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7,N=1010;
int ch[N][40],prt[N],len[N];
int lst=1,tot=1;
int n,k,ans=0,s[N],wn=0;
int A[N][N],fac[N];

void insert(int c)
{
	int p=lst,np=++tot;len[np]=len[p]+1;
	while(p&&!ch[p][c]) ch[p][c]=np,p=prt[p];
	if(!p) prt[np]=1;
	else
	{
		int q=ch[p][c];
		if(len[p]+1==len[q]) prt[np]=q;
		else
		{
			int nq=++tot;len[nq]=len[p]+1;
			memcpy(ch[nq],ch[q],sizeof(int)*k);
			prt[nq]=prt[q];prt[q]=prt[np]=nq;
			while(ch[p][c]==q) ch[p][c]=nq,p=prt[p];
		}
	}
	lst=np;
}

int gao(const int *s)
{
    int res=0;
    for(int i=1;i<=n;i++)
        insert(s[i]);
    res=tot;
    for(int i=1;i<=tot;i++)
        memset(ch[i],0,sizeof(int)*k);
    memset(prt,0,sizeof(int)*(tot+1));
    memset(len,0,sizeof(int)*(tot+1));
    tot=lst=1;
    return res;
}

void dfs(int d,int mx)
{
    if(d==n+1)
    {
        ans=(ans+1ll*gao(s)*A[k][mx])%ha;
        return;
    }
    for(int c=0;c<mx;c++)
        s[d]=c,dfs(d+1,mx);
    if(mx<k) s[d]=mx,dfs(d+1,mx+1);
}

int main()
{
    freopen("answer.txt","w",stdout);
    for(int i=0;i<=100;i++)
    {
        A[i][0]=1;
        for(int j=1;j<=i;j++)
            A[i][j]=(A[i-1][j-1]+A[i-1][j])%ha;
    }
    fac[0]=1;
    for(int i=1;i<=100;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    for(int i=0;i<=100;i++)
        for(int j=0;j<=100;j++)
            A[i][j]=1ll*A[i][j]*fac[j]%ha;
    for(n=1;n<=15;n++)
    {
        printf("{");
        for(k=1;k<=n;k++)
        {
            ans=0;
            dfs(1,0);
            printf("%d",ans);
            if(k<n) printf(",");
            fflush(stdout);
        }
        printf("},\n");
        fflush(stdout);
    }
    return 0;
}
