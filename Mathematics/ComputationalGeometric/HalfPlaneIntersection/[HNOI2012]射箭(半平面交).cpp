#include <bits/stdc++.h>
#define double long double
using namespace std;

const double eps = 1e-18;
const double inf = 1e18;
struct Point{
    double x, y;
    Point(double x=0, double y=0): x(x), y(y) {}
} p[200005], vtx[200005];
typedef Point Vector;

Point operator + (const Point &a, const Point &b){
    return Point(a.x + b.x, a.y + b.y);
}
Point operator - (const Point &a, const Point &b){
    return Point(a.x - b.x, a.y - b.y);
}
Point operator * (const double &k, const Point &a){
    return Point(a.x * k, a.y * k);
}
Point operator / (const Point &a, const double &k){
    return Point(a.x / k, a.y / k);
}
Vector rotate90(const Vector &v){
    return Vector(-v.y, v.x);
}

double cross(const Point &a, const Point &b){return a.x*b.y-a.y*b.x;}

int dcmp(double x){
    if(fabs(x) <= eps) return 0;
    else if(x<0) return -1;
    else return 1;
}

struct Line{
    Point a, e;   // 直线上一点
    Vector v;     // 方向向量
    double theta;
    int id;
    Line(){}
    Line(const Point &a, const Vector &v, const int &id):
        a(a), v(v), id(id), e(a+v), theta(atan2(v.y,v.x)) {}
    double polar() const{
        return theta;
    }
    bool onleft(const Point &p) const{
        return dcmp(cross(v, p-a)) > 0;
    }
    bool onright(const Point &p) const{
        return dcmp(cross(v, p-a)) < 0;
    }
    Point crosspoint(const Line& b) const{
        double a1 = cross(b.v, a - b.a);
        double a2 = cross(b.v, e - b.a);
        return a + a1 / (a1 - a2) * v;
    }
} l[200005];

bool operator < (const Line &a, const Line &b){
    double x = a.polar(), y = b.polar();
    // 极角更小，或极角相等但是 a 在 b 左侧
    return dcmp(x-y) < 0 || dcmp(x-y) == 0
           && a.onright(b.a);
}

int tot = 0;

int get_halfplane(Line input_l[], int all, int maxid){
    static Line l[200005];
    int tot = 0;
    for(int i = 0; i < all; i++){
        if(input_l[i].id > maxid) continue;
        if(tot && dcmp(input_l[i].polar() - l[tot-1].polar()) == 0) continue;
        l[tot++] = input_l[i];
    }

    static Line line_que[200005];
    static Point vertex_que[200005];
    int ql = 0, qr = -1;

    for(int i = 0; i < tot; i++){
        while(ql < qr && l[i].onright(vertex_que[qr])) qr--;
        while(ql < qr && l[i].onright(vertex_que[ql+1])) ql++;
        if(ql <= qr) vertex_que[qr+1] = (l[i].crosspoint(line_que[qr]));
        line_que[++qr] = l[i];
    }
    while(ql < qr && line_que[ql].onright(vertex_que[qr])) qr--;
    if(ql == qr) return 0;
    vertex_que[ql] = (line_que[ql].crosspoint(line_que[qr]));

    return qr - ql + 1;
}

int main(){
    int n, x, yl, yr;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d%d%d", &x, &yl, &yr);
        l[2*i] = Line(Point(0, (double)yl/x), Vector(1, -x), i+1);
        l[2*i+1] = Line(Point(0, (double)yr/x), Vector(-1, x), i+1);
    }
    l[2*n] = Line(Point(-eps, eps), Vector(inf, 0), 0);    // b>0
    l[2*n+1] = Line(Point(-eps, eps), Vector(0, inf), 0);  // a<0
    // 加上边界保证半平面交有界
    l[2*n+2] = Line(Point(-inf, eps), Vector(0, -1), 0);
    l[2*n+3] = Line(Point(eps, inf), Vector(-1, 0), 0);

    // 因为卡常，遂把排序放到预处理
    sort(l, l + 2*n + 4);

    int L = 1, R = n, mid;
    while(L <= R){
        mid = (L + R) / 2;
        int m = get_halfplane(l, 2*n+4, mid);
        if(m >= 3) L = mid + 1;
        else R = mid - 1;
    }
    cout << R << endl;
    return 0;
}