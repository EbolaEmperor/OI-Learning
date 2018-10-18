#include<bits/stdc++.h>
using namespace std;

const double eps=1e-8;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x<0) return -1;
	else return 1;
}

struct bowl
{
	double h,r1,r2;
	void read(){scanf("%lf%lf%lf",&h,&r1,&r2);}
} b[15],fk[15];
int id[15],n;
bool vis[15];
double h[15],ans=1e4;

double gao()
{
	double dafa=0;
	for(int i=1;i<=n;i++) fk[i]=b[id[i]];
	for(int i=1;i<=n;i++)
	{
		double t=0,t1=fk[i].h/(fk[i].r2-fk[i].r1);
		for(int j=1;j<i;j++)
		{
			t=max(t,h[j]);
			double t2=fk[j].h/(fk[j].r2-fk[j].r1);
			if(dcmp(fk[i].r1-fk[j].r1)<=0)
			{
				if(dcmp(t1-t2)>=0) t=max(t,h[j]);
				else
				{
					if(dcmp(fk[i].r2-fk[j].r2)<=0)
					{
						double tmp=t2*(fk[i].r2-fk[j].r1);
						if(dcmp(tmp-fk[i].h)>0)
							t=max(t,tmp-fk[i].h+h[j]);
						else t=max(t,h[j]);
					}
					else t=max(t,fk[j].h-(fk[j].r2-fk[i].r1)*t1+h[j]);
				}
			}
			else if(dcmp(fk[i].r1-fk[j].r2)<0)
			{
				if(dcmp(t1-t2)>=0) t=max(t,t2*(fk[i].r1-fk[j].r1)+h[j]);
				else
				{
					if(dcmp(fk[i].r2-fk[j].r2)<=0)
						t=max(t,t2*(fk[i].r2-fk[j].r1)-fk[i].h+h[j]);
					else t=max(t,fk[j].h-t1*(fk[j].r2-fk[i].r1)+h[j]);
				}
			}
			else t=max(t,h[j]+fk[j].h);
		}
		h[i]=t;dafa=max(dafa,t+fk[i].h);
	}
	return dafa;
}

void dfs(int p)
{
	if(p>n){ans=min(ans,gao());return;}
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;
		id[p]=i;vis[i]=1;
		dfs(p+1);vis[i]=0;
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		b[i].read();
	dfs(1);
	printf("%d\n",(int)round(ans));
	return 0;
}
