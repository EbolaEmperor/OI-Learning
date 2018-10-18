#include<iostream>
#include<cstdio>
#include<stack>
#include<queue>
using namespace std;

int opt[2][1005];

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		bool f1=true,f2=true,f3=true;
		for(int i=0;i<n;i++) scanf("%d%d",&opt[0][i],&opt[1][i]);
		stack<int> s;
		for(int i=0;i<n;i++)
		{
			if(opt[0][i]==1) s.push(opt[1][i]);
			if(s.empty()){f1=false;break;}
			if(opt[0][i]==2&&!s.empty())
			{
				int num=s.top();
				if(num!=opt[1][i]){f1=false;break;}
				s.pop();
			}
		}
		queue<int> q;
		for(int i=0;i<n;i++)
		{
			if(opt[0][i]==1) q.push(opt[1][i]);
			if(q.empty()){f2=false;break;}
			if(opt[0][i]==2&&!q.empty())
			{
				int num=q.front();
				if(num!=opt[1][i]){f2=false;break;}
				q.pop();
			}
		}
		priority_queue<int> pq;
		for(int i=0;i<n;i++)
		{
			if(opt[0][i]==1) pq.push(opt[1][i]);
			if(pq.empty()){f3=false;break;}
			if(opt[0][i]==2&&!pq.empty())
			{
				int num=pq.top();
				if(num!=opt[1][i]){f3=false;break;}
				pq.pop();
			}
		}
		int cnt=f1+f2+f3;
		if(cnt==0) puts("impossible");
		if(cnt>1) puts("not sure");
		if(cnt==1)
		{
			if(f1) puts("stack");
			if(f2) puts("queue");
			if(f3) puts("priority queue");
		}
	}
	return 0;
}
