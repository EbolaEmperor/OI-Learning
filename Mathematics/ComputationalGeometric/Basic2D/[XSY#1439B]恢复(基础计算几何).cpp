#include<bits/stdc++.h>
using namespace std;

typedef long double LD;
const int N=110;
LD dist[N][N];
int n;

struct Point
{
    LD x,y;
    Point(LD _x=0,LD _y=0):x(_x),y(_y){}
    Point operator - (const Point &a){return Point(x-a.x,y-a.y);}
    LD angle(){return atan2(y,x);}
    LD dis(Point &a){return sqrt((x-a.x)*(x-a.x)+(y-a.y)*(y-a.y));}
} p[N];
typedef pair<Point,Point> ppp;

struct Circle
{
    LD x,y,r;
    Circle(LD _x=0,LD _y=0,LD _r=0):x(_x),y(_y),r(_r){}
    Point getp(LD alpha){return Point(x+r*cos(alpha),y+r*sin(alpha));}
};

LD cos_theo(LD a,LD b,LD c){return acos((b*b+c*c-a*a)/(2*b*c));}
LD dis(LD x1,LD x2,LD y1,LD y2){return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));}
bool dcmp(LD a,LD b){return fabs(a-b)<1e-5;}

ppp enjo_kosai(Circle &a,Circle &b)
{
    LD beta=cos_theo(b.r,a.r,dis(a.x,b.x,a.y,b.y));
    Point vec(b.x-a.x,b.y-a.y);
    LD alpha=vec.angle()-beta;
    return ppp(a.getp(alpha),a.getp(alpha+beta*2));
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            scanf("%Lf",dist[i]+j);
    p[1]=Point(0.0,0.0);
    p[2]=Point(dist[1][2],0.0);
    Circle a(p[1].x,p[1].y,dist[1][3]);
    Circle b(p[2].x,p[2].y,dist[2][3]);
    p[3]=enjo_kosai(a,b).first;
    for(int i=4;i<=n;i++)
    {
        a=Circle(p[1].x,p[1].y,dist[1][i]);
        b=Circle(p[2].x,p[2].y,dist[2][i]);
        ppp c=enjo_kosai(a,b);
        Point p1=c.first,p2=c.second;
        p[i]=dcmp(p1.dis(p[3]),dist[3][i])?p1:p2; 
    }
    for(int i=1;i<=n;i++)
        printf("%.5Lf %.5Lf\n",p[i].x,p[i].y);
    return 0;
}