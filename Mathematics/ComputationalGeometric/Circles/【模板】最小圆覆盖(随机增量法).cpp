#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
struct Point{
    double x, y;
    Point(double x=0, double y=0): x(x),y(y) {}
    double len() const{
        return sqrt(x * x + y * y);
    }
};
#define Vector Point
Point p[N];
int n;

Vector operator * (const double &a, const Point &b){
    return Vector(a*b.x, a*b.y);
}
Vector operator + (const Point &a, const Point &b){
    return Vector(a.x+b.x, a.y+b.y);
}
Vector operator - (const Point &a, const Point &b){
    return Vector(a.x-b.x, a.y-b.y);
}

int dcmp(double x){
    if(fabs(x) < 1e-12) return 0;
    else if(x<0) return -1;
    else return 1;
}

bool incircle(const Point &o, const double &r, const Point &p){
    return dcmp((o-p).len() - r) <= 0;
}

double sqr(const double &x){return x * x;}

void geto(const Point &a, const Point &b, const Point &c, Point &ans, double &r) {
    double a11, a12, a21, a22, b1, b2;
    a11 = 2 * (b.x - a.x); a12 = 2 * (b.y - a.y);
    a21 = 2 * (c.x - a.x); a22 = 2 * (c.y - a.y);
    b1 = sqr(b.x) - sqr(a.x) + sqr(b.y) - sqr(a.y);
    b2 = sqr(c.x) - sqr(a.x) + sqr(c.y) - sqr(a.y);
    ans.x = (b1 * a22 - b2 * a12) / (a11 * a22 - a12 * a21);
    ans.y = (a11 * b2 - a21 * b1) / (a11 * a22 - a12 * a21);
    r = (a-ans).len();
}

// 求 MC(P[i],P[j]; P[1],...,P[j-1])
void mc_fix2(int i, int j, Point &ans, double &r){
    ans = 0.5 * (p[i] + p[j]);
    r = (p[i]-p[j]).len() / 2;
    for(int k = 1; k < j; k++){
        if(incircle(ans, r, p[k])) continue;
        // 根据引理3，MC(P[i],P[j]; P[1],...,P[k]) = MC(P[i],P[j],P[k]; P[1],...,P[k-1])
        geto(p[i], p[j], p[k], ans, r);
    }
}

// 求 MC(P[i]; P[1],...,P[i-1])
void mc_fix1(int i, Point &ans, double &r){
    ans = 0.5 * (p[i] + p[1]);
    r = (p[i]-p[1]).len() / 2;
    for(int j = 2; j < i; j++){
        if(incircle(ans, r, p[j])) continue;
        // 根据引理2，MC(P[i]; P[1],...,P[j]) = MC(P[i],P[j]; P[1],...,P[j-1])
        mc_fix2(i, j, ans, r);
    }
}

// 求 MC(空; P[1],...,P[n])
void mc_fix0(Point &ans, double &r){
    ans = p[1]; r = 0;
    for(int i = 2; i <= n; i++){
        if(incircle(ans, r, p[i])) continue;
        // 根据引理1，MC(空; P[1],...,P[i]) = MC(P[i]; P[1],...,P[i-1])
        mc_fix1(i, ans, r);
    }
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    random_shuffle(p+1, p+1+n);
    Point ans;
    double r;
    mc_fix0(ans, r);
    printf("%.10lf\n%.10lf %.10lf\n", r, ans.x, ans.y);
    return 0;
}