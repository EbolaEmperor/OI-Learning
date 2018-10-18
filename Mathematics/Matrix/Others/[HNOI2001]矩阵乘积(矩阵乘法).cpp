#include<bits/stdc++.h>
using namespace std;

int A[6005],B[6005];
char input[10005];

int main()
{
	freopen("testdata.in","r",stdin);
	int x,y,u,v,val;
	int m,n,o,p;
	scanf("%d%d%d%d%d%d",&x,&y,&m,&n,&o,&p);
	fgets(input,10000,stdin);
	while(true)
	{
		fgets(input,10000,stdin);
		if(!isdigit(input[0])) break;
		sscanf(input,"%d%d%d",&u,&v,&val);
		if(u==x) A[v]=val;
	}
	while(true)
	{
		fgets(input,10000,stdin);
		if(!isdigit(input[0])) break;
		sscanf(input,"%d%d%d",&u,&v,&val);
		B[v]+=A[u]*val;
	}
	memcpy(A,B,sizeof(A));
	memset(B,0,sizeof(B));
	while(~scanf("%d%d%d",&u,&v,&val))
		B[v]+=A[u]*val;
	cout<<B[y]<<endl;
	return 0;
}
