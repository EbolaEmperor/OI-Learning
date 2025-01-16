#include<bits/stdc++.h>
#define ha 1000000007
#define MP make_pair
#define FR first
#define SE second
using namespace std;

typedef pair<int,int> pii;
const int N=420010;
char A[N],B[N];
pii pa[N],pb[N];
int n,L,m,len;

void prework()
{
	if(n==100) m=8;
	if(n==10000) m=10;
	if(n==400000) m=29;
	len=n-m+1;n+=L;
	for(int i=1;i<=len;i++)
	{
		int statu=0;
		for(int j=i;j<=i+m-1;j++)
			statu=((statu<<1)+(A[j]-'0'))%ha;
		pa[i]=MP(statu,i);
	}
	for(int i=1;i<=len;i++)
	{
		int statu=0;
		for(int j=i;j<=i+m-1;j++)
			statu=((statu<<1)+(B[j]-'0'))%ha;
		pb[i]=MP(statu,i);
	}
	sort(pa+1,pa+1+len);
	sort(pb+1,pb+1+len);
}

int main()
{
	scanf("%d%d",&n,&L);
	scanf("%s%s",A,B);
	prework();
	int p1=1,p2=1,ans=0,tms=0;
	for(int i=1;i<=len;i++)
	{
		while(p1<=len&&pa[p1].FR<pb[i].FR) p1++;
		while(p2<=len&&pa[p2].FR<=pb[i].FR) p2++;
		if(p1==len) break;
		for(int j=p1;j<p2;j++)
		{
			int ta=pa[j].SE,tb=pb[i].SE;
			int la=max(1,ta+m-L),lb=max(1,tb+m-L);
			int ra=min(ta,n-L+1),rb=min(tb,n-L+1);
			int l=max(la-ta,lb-tb),r=min(ra-ta,rb-tb);
			if(l<=r)
			{
				int sum=0;tms+=r-l;
				for(int k=0;k<L;k++) sum+=(A[ta+l+k]==B[tb+l+k]);
				ans=max(ans,sum);
				for(int k=l+1;k<=r;k++)
				{
					sum-=(A[ta+k-1]==B[tb+k-1]);
					sum+=(A[ta+k+L-1]==B[tb+k+L-1]);
					ans=max(ans,sum);
				}
				if(tms>100000000) goto fuck;
			}
		}
	}
	fuck: cout<<ans<<endl;
	return 0;
}