#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=100010,M=510;
int n,m,tot,g[M][M];

struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
    void read(){scanf("%d%d",&x,&y);}
    bool operator == (const Point &b) const{return x==b.x&&y==b.y;}
	bool operator < (const Point &b) const{return x<b.x||x==b.x&&y<b.y;}
	Point operator - (const Point &b){return Point(x-b.x,y-b.y);}
	LL operator * (const Point &b){return (LL)x*b.y-(LL)y*b.x;}
} a[N],b[M],c[N];

int convex_hull(Point *p,Point *ch,int n)
{
	sort(p+1,p+1+n);
	int top=0;
	for(int i=1;i<=n;i++)
	{
		while(top>1&&(ch[top]-ch[top-1])*(p[i]-ch[top-1])<=0) top--;
		ch[++top]=p[i];
	}
	int k=top;
	for(int i=n-1;i>=1;i--)
	{
		while(top>k&&(ch[top]-ch[top-1])*(p[i]-ch[top-1])<=0) top--;
		ch[++top]=p[i];
	}
	return top;
}

bool in_convex(const Point &a)
{
    for(int i=1;i<tot;i++)
        if((c[i]-a)*(c[i+1]-a)<=0) return 0;
    return 1;
}

void gaogaogaogaogao()
{
    memset(g,0x3f,sizeof(g));
    for(int i=1;i<=m;i++)
    {
        if(in_convex(b[i])) continue;
        bool flag=0;
        Point l,r;
        for(int j=1;j<=tot;j++)
        {
            if(b[i]==c[j]) continue;
            Point v=c[j]-b[i];
            if(!flag) l=v,r=v,flag=1;
            if(r*v<0) r=v;
            if(l*v>0) l=v;
        }
        l=Point(0,0)-l;
        for(int j=1;j<=m;j++)
            if(j!=i&&(b[j]-b[i])*l<=0&&(b[j]-b[i])*r>=0)
                g[i][j]=1;
    }
    for(int k=1;k<=m;k++)
        for(int i=1;i<=m;i++)
            for(int j=1;j<=m;j++)
                g[i][j]=min(g[i][j],g[i][k]+g[k][j]);
    int ans=m*2;
    for(int i=1;i<=m;i++)
        ans=min(ans,g[i][i]);
    if(ans==m*2) puts("-1");
    else printf("%d\n",ans);
}

int main()
{
	scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) a[i].read();
    for(int i=1;i<=m;i++) b[i].read();
    if(n==1)
    {
        bool flag=0;
        for(int i=1;i<=m;i++)
            if(a[1]==b[i]) flag=1;
        if(flag) return puts("1"),0;
    }
    tot=convex_hull(a,c,n);
    gaogaogaogaogao();
    return 0;
}
