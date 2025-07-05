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

int getconvex(Point p[], int n, Point ch[]){
    sort(p+1, p+1+n);
    int m = 0;
    for(int i = 1; i <= n; i++){
        while(m >= 2 && dcmp(cross(ch[m]-ch[m-1], p[i]-ch[m-1])) <= 0) m--;
        ch[++m] = p[i];
    }
    int k = m;
    for(int i = n-1; i >= 1; i--){
        while(m > k && dcmp(cross(ch[m]-ch[m-1], p[i]-ch[m-1])) <= 0) m--;
        ch[++m] = p[i];
    }
    if(m == 1) return 1;
    return m-1;
}

Vector rotate90(const Vector &v){
    return Vector(-v.y, v.x);
}

double area(const Point &A, const Point &B, const Point &C, const Point &D){
    return (cross(B-A, C-A) + cross(C-A, D-A)) / 2;
}

int main(){
    const int N = 50010;
    static Point p[N], ch[N];
    int n;
    double ans = 0;

    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    
    int m = getconvex(p, n, ch);
    auto next = [&](int i){return i % m + 1;};

    int j = 2, R = 2, L = -1;
    for(int i = 1; i <= m; i++){
        Vector v = ch[next(i)]-ch[i];
        Vector vert = rotate90(v);
        while(dcmp(cross(v, ch[next(j)]-ch[j])) > 0) j = next(j);
        while(dcmp(cross(vert, ch[next(R)]-ch[R])) < 0) R = next(R);
        if(L == -1) L = j;
        while(dcmp(cross(vert, ch[next(L)]-ch[L])) > 0) L = next(L);

        ans = max(ans, area(ch[i], ch[R], ch[j], ch[L]));
        ans = max(ans, area(ch[next(i)], ch[R], ch[j], ch[L]));
    }
    printf("%.3lf\n", ans);
    return 0;
}