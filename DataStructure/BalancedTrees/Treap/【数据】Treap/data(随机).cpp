#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;

struct{int val,cnt;} a[2000];
int tot=0,sum=0,opt,x;

int main()
{
	srand(time(0));
	freopen("testdata.in","w",stdout);
	cout<<1000<<endl;
	for(int i=1;i<=1000;i++)
	{
		opt=(tot<=3)?1:(rand()%6+1);
		if(opt==1)
		{
			x=rand();
			printf("%d %d\n",opt,x);
			bool flag=false;
			for(int j=1;j<=tot;j++)
				if(a[j].val==x) {a[j].cnt++;flag=true;break;}
			if(!flag) a[++tot].val=x,a[tot].cnt=1;
			sum++;
		}
		if(opt==2)
		{
			x=rand()%tot+1;
			printf("%d %d\n",opt,a[x].val);
			if(a[x].cnt>1) a[x].cnt--;
			else
			{
				for(int j=x;j<tot;j++) a[j]=a[j+1];
				a[tot].val=a[tot].cnt=0;
				tot--;
			}
		}
		if(opt==3)
		{
			x=rand()%tot+1;
			printf("%d %d\n",opt,a[x].val);
		}
		if(opt==4)
		{
			x=rand()%sum+1;
			printf("%d %d\n",opt,sum);
		}
		if(opt>=5)
		{
			int mn=0x3fffffff,mx=-0x3fffffff;
			for(int j=1;j<=tot;j++)
			{
				mn=min(mn,a[j].val);
				mx=max(mx,a[j].val);
			}
			x=rand()%(mx-mn+1)+mn;
			printf("%d %d\n",opt,x);
		}
	}
	return 0;
}
