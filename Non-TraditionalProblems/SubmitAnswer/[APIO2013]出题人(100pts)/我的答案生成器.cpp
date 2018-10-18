#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct Edge{int to,capa,next;} e[2000000];
int h[2000],sum=-1;

void add_edge(int u,int v,int w)
{
	sum++;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
	//cout<<u<<" "<<v<<endl;
}

int main()
{
	srand(19260817);
	freopen("6.txt","w",stdout);
	int l=32;
	cout<<l<<endl;
	for(int i=0;i<l;i++) h[i]=-1;
	int p=18;
	for(int i=0;i<l;i+=2)
	{
		add_edge(i,i+1,(1<<p));
		if(i+2<l) add_edge(i,i+2,0);
		if(i+2<l) add_edge(i+1,i+2,-(1<<(p+1)));
		p--;
	}
		/*add_edge(0,1,4);
		add_edge(0,2,0);
		add_edge(1,2,-8);
		add_edge(2,3,2);
		add_edge(2,4,0);
		add_edge(3,4,-4);*/
	for(int i=0;i<l;i++)
	{
		int cnt=0;
		for(int tmp=h[i];tmp!=-1;tmp=e[tmp].next) cnt++;
		cout<<cnt;
		for(int tmp=h[i];tmp!=-1;tmp=e[tmp].next) printf(" %d %d",e[tmp].to,e[tmp].capa);
		putchar('\n');
		//puts("0");
	}
	cout<<8<<endl;
	for(int i=1;i<=8;i++) printf("%d %d\n",0,l-1);
	fclose(stdout);
	freopen("6.txt","r",stdin);
	freopen("T.txt","w",stdout);
	int cnt=0,xx;
	while(cin>>xx) cnt++;
	cout<<"T="<<cnt<<endl;
	return 0;
}
