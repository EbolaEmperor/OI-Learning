#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
char s[N];
int sa[N],rk[N],c[N],sum[N];
int x[N],y[N],tmp[N];
int height[N],sh[21][N],lg2[N];
struct Opt{int ty,x;} qry[N];
int qwq,n,m,q,tot,cur;
int lst[N],len[N],L[N],R[N];

void get_sa(int n,int m)
{
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<m;i++) c[i+1]+=c[i];
	for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int num=0;
		for(int i=n-k+1;i<=n;i++) y[++num]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) tmp[i]=x[y[i]];
		for(int i=1;i<=n;i++) c[tmp[i]]++;
		for(int i=1;i<m;i++) c[i+1]+=c[i];
		for(int i=n;i>=1;i--) sa[c[tmp[i]]--]=y[i];
		num=1;swap(x,y);x[sa[1]]=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])?++num:num;
		if(num==n) break;
		m=num;
	}
	for(int i=1;i<=n;i++) rk[sa[i]]=i;
}

void get_height(int n)
{
	int k=0;
	for(int i=1;i<=n;i++)
	{
		if(rk[i]==1) continue;   //height[1]=0
		if(k) k--;   //h[i]>=h[i-1]-1
		int j=sa[rk[i]-1];
		while(j+k<=n&&i+k<=n&&s[i+k]==s[j+k]) k++;
		height[rk[i]]=k;   //h[i]=height[rk[i]]
	}
	for(int i=1;i<=n;i++) sh[0][i]=height[i];
	for(int k=1;k<=20;k++)
	   for(int i=1;i<=n;i++)
	       sh[k][i]=min(sh[k-1][i],sh[k-1][i+(1<<k-1)]);
	for(int i=2;i<=n;i++)
	   lg2[i]=lg2[i>>1]+1;
}

int lcp(int x,int y)
{
    if(x==y) return tot-x+1;
    int l=rk[x],r=rk[y];
    if(l>r) swap(l,r);l++;
    int len=r-l+1,k=lg2[len];
    return min(sh[k][l],sh[k][r-(1<<k)+1]);
}

void gao(int x,int st,int ed)
{
    int t=len[x],lenn=ed-st+1,pos=n+st+1;
    int l=L[x],r=R[x],mid,res1=r+1;
    while(l<=r)
    {
        mid=(l+r)/2;
        int p=lcp(sa[mid]+t,pos);
        if(p>=lenn) res1=mid,r=mid-1;
        else if(s[sa[mid]+t+p]>s[pos+p]) res1=mid,r=mid-1;
        else l=mid+1;
    }
    l=L[x],r=R[x];int res2=l-1;
    while(l<=r)
    {
        mid=(l+r)/2;
        int p=lcp(sa[mid]+t,pos);
        if(p>=lenn) res2=mid,l=mid+1;
        else if(s[sa[mid]+t+p]<s[pos+p]) res2=mid,l=mid+1;
        else r=mid-1;
    }
    L[x]=res1;R[x]=res2;
}

void change(int x)
{
    if(lst[x]!=-1)
    {
        gao(x,lst[x],cur);
        len[x]+=cur-lst[x]+1;
        lst[x]=-1;
    }
    else lst[x]=cur+1;
}

int query(int x)
{
    if(L[x]>R[x]) return 0;
    if(lst[x]!=-1)
    {
        if(len[x]+cur-lst[x]+1==0) return 0;
        int pl=L[x],pr=R[x];
        gao(x,lst[x],cur);
        int res=sum[R[x]]-sum[L[x]-1];
        L[x]=pl;R[x]=pr;
        return res;
    }
    else if(len[x]==0) return 0;
    else return sum[R[x]]-sum[L[x]-1];
}

int main()
{
    scanf("%d%d%d%d",&qwq,&n,&m,&q);
    scanf("%s",s+1);
    tot=n=strlen(s+1);
    s[++tot]='O';
    for(int i=1;i<=q;i++)
    {
        int opt,x;char c[5];
        scanf("%d",&opt);
        if(opt==1) scanf("%d",&x),qry[i]={opt,x};
        if(opt==2) scanf("%s",c),s[++tot]=c[0],qry[i]={opt,0};
        if(opt==3) scanf("%d",&x),qry[i]={opt,x};
    }
    memset(lst,-1,sizeof(lst));
    for(int i=1;i<=m;i++) L[i]=1,R[i]=tot;
    get_sa(tot,130);
    get_height(tot);
    for(int i=1;i<=tot;i++)
        sum[i]=sum[i-1]+(sa[i]<=n);
    for(int i=1;i<=q;i++)
    {
        if(qry[i].ty==1) change(qry[i].x);
        if(qry[i].ty==2) cur++;
        if(qry[i].ty==3) printf("%d\n",query(qry[i].x));
    }
    return 0;
}
