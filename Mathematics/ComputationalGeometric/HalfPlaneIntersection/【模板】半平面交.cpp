#include <bits/stdc++.h>
using namespace std;

struct Point{
    double x, y;
    Point(double x=0, double y=0): x(x),y(y) {}
    double len() const{
        return sqrt(x * x + y * y);
    }
};
#define Vector Point

Vector operator * (const double &a, const Point &b){
    return Vector(a*b.x, a*b.y);
}
Vector operator + (const Point &a, const Point &b){
    return Vector(a.x+b.x, a.y+b.y);
}
Vector operator - (const Point &a, const Point &b){
    return Vector(a.x-b.x, a.y-b.y);
}

double cross(const Point &a, const Point &b){
    return a.x * b.y - a.y * b.x;
}
double dot(const Point &a, const Point &b){
    return a.x * b.x + a.y * b.y;
}

int dcmp(double x){
    if(fabs(x) < 1e-12) return 0;
    else if(x<0) return -1;
    else return 1;
}
bool operator < (const Point &a, const Point &b){
    return dcmp(a.x-b.x)<0 || dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)<0;
}

struct Line{
    Point A;
    Vector v;
    double polar;
    Line(){}
    Line(const Point &A, const Point &B): 
        A(A), v(B-A), polar(atan2(v.y, v.x)) {}
    bool notleft(const Point &B) const{
        return dcmp(cross(v, B-A)) <= 0;
    }
};

bool operator < (const Line &l, const Line &r){
    return dcmp(l.polar - r.polar) < 0
        || dcmp(l.polar - r.polar) == 0
        && dcmp(cross(l.v, r.A - l.A)) < 0;
}

Point LineIns(const Line &l, const Line &r){
    double a1 = cross(r.v, l.A-r.A);
    double a2 = cross(r.v, l.A+l.v-r.A);
    double lam = a1 / (a1 - a2);
    return l.A + lam * l.v;
}

int halfplane(Line l[], int n, Line hp[], Point ins[]){
    sort(l+1, l+1+n);
    int tot = 0;
    for(int i = 1; i <= n; i++){
        if(tot && dcmp(l[i].polar-l[tot].polar) == 0) continue;
        l[++tot] = l[i];
    }

    int pl = 1, pr = 0;
    for(int i = 1; i <= tot; i++){
        while(pr-pl >= 1 && l[i].notleft(ins[pr])) pr--;
        while(pr-pl >= 1 && l[i].notleft(ins[pl+1])) pl++;
        hp[++pr] = l[i];
        if(pr - pl >= 1)
            ins[pr] = LineIns(hp[pr], hp[pr-1]);
    }
    while(pr-pl >= 1 && hp[pl].notleft(ins[pr])) pr--;
    if(pr - pl >= 2)
        ins[pl] = LineIns(hp[pl], hp[pr]);
    
    for(int i = pl; i <= pr; i++)
        hp[i-pl+1] = hp[i], ins[i-pl+1] = ins[i];
    return pr - pl + 1;
}

double getarea(Point p[], int n){
    double area = 0;
    for(int i = 2; i <= n-1; i++){
        area += cross(p[i]-p[1], p[i+1]-p[1]);
    }
    return area / 2;
}

int main(){
    int n, m, tot = 0;
    const int N = 510;
    static Point p[N], ins[N];
    static Line line[N], hp[N];

    scanf("%d", &n);
    while(n--){
        scanf("%d", &m);
        for(int i = 1; i <= m; i++)
            scanf("%lf%lf", &p[i].x, &p[i].y);
        for(int i = 1; i <= m; i++)
            line[++tot] = Line(p[i], p[i%m+1]);
    }
    tot = halfplane(line, tot, hp, ins);
    printf("%.3lf\n", getarea(ins, tot));
    return 0;
}