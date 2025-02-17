#include<bits/stdc++.h>
using namespace std;

const int N=10010;
struct Point{double x,y;} p[N],ansp;
double ans=1e18,wgt[N];
int n,begint=0;

double sqr(const double &x){return x*x;}
double dist(Point &a,Point &b){return sqrt(sqr(a.x-b.x)+sqr(a.y-b.y));}
double calc(Point pnt)
{
    double res=0;
    for(int i=1;i<=n;i++)
        res+=dist(pnt,p[i])*wgt[i];
    if(res<ans) ans=res,ansp=pnt;
    return res;
}

double RAND(){return (double)rand()/RAND_MAX;}
double accept(double dta,double tem){return dta<0||RAND()<exp(-dta/tem);}
void anneal(Point pnt,double tem,double delta,double end)
{
    calc(pnt);
    while(tem>end)
    {
        Point nxt={pnt.x+tem*(RAND()*2-1),pnt.y+tem*(RAND()*2-1)};
        double nxtans=calc(nxt);
        if(accept(nxtans-ans,tem)) pnt=nxt;
        tem*=delta;
    }
    for(int i=1;i<=1000;i++)
        calc({ansp.x+tem*(RAND()*2-1),ansp.y+tem*(RAND()*2-1)});
}

bool TLE()
{
    double now=clock()-begint;
    now=now/CLOCKS_PER_SEC*1000;
    return now>950;
}

int main()
{
    begint=clock();
    srand(time(0));
    scanf("%d",&n);
    Point s={0,0};
    for(int i=1;i<=n;i++)
    {
        scanf("%lf%lf%lf",&p[i].x,&p[i].y,wgt+i);
        s.x+=p[i].x;s.y+=p[i].y;
    }
    s.x/=n;s.y/=n;
    anneal(s,1e5,1-7e-3,1e-14);
    while(!TLE()) anneal(ansp,rand()%5+5,1-3e-3,1e-3);
    printf("%.3lf %.3lf\n",ansp.x,ansp.y);
    return 0;
}