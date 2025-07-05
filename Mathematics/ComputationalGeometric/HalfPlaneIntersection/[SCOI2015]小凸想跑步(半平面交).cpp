#include <bits/stdc++.h>
using namespace std;

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

double cross(Point a,Point b){return a.x*b.y-a.y*b.x;}

int dcmp(double x){
    static const double eps = 1e-12;
    if(fabs(x) <= eps) return 0;
    else if(x<0) return -1;
    else return 1;
}

struct Line{
    Point a;   // 直线上一点
    Vector v;  // 方向向量
    Line(){}
    Line(const Point &a, const Vector &v):
        a(a), v(v) {}
    double polar() const{
        return atan2(v.y, v.x);
    }
    bool onleft(const Point &p) const{
        return dcmp(cross(v, p-a)) > 0;
    }
    Point crosspoint(const Line& b) const{
        double a1 = cross(b.v, a - b.a);
        double a2 = cross(b.v, a+v - b.a);
        return a + a1 / (a1 - a2) * v;
    }
} l[200005];

bool operator < (const Line &a, const Line &b){
    double x = a.polar(), y = b.polar();
    // 极角更小，或极角相等但是 a 在 b 左侧
    return dcmp(x-y) < 0 || dcmp(x-y) == 0
           && b.onleft(a.a);
}

int tot = 0;

int get_halfplane(Line l[], int tot, Point vertex[]){
    // 按极角排序，极角相等的从左到右排
    sort(l, l + tot);

    // 去重，如果有极角相同的直线，只保留最左侧的那条
    const int tot_pre = tot;
    tot = 0;
    for(int i = 0; i < tot_pre; i++){
        if(i && dcmp(l[i].polar() - l[i-1].polar()) == 0) continue;
        l[tot++] = l[i];
    }

    deque<Line> line_que;
    deque<Point> vertex_que;

    line_que.push_back(l[0]);
    line_que.push_back(l[1]);
    vertex_que.push_back(l[0].crosspoint(l[1]));

    for(int i = 2; i < tot; i++){
        while(!vertex_que.empty() && !l[i].onleft(vertex_que.back()))
            vertex_que.pop_back(), line_que.pop_back();
        while(!vertex_que.empty() && !l[i].onleft(vertex_que.front()))
            vertex_que.pop_front(), line_que.pop_front();
        vertex_que.push_back(l[i].crosspoint(line_que.back()));
        line_que.push_back(l[i]);
    }
    while(!vertex_que.empty() && !line_que.front().onleft(vertex_que.back()))
        vertex_que.pop_back(), line_que.pop_back();
    if(line_que.size() == 1) return 0;
    vertex_que.push_back(line_que.back().crosspoint(line_que.front()));

    int res = 0;
    while(!vertex_que.empty())
        vertex[res++] = vertex_que.front(), vertex_que.pop_front();
    return res;
}

double get_area(Point p[], const int &m){
    if(m < 3) return 0;
    double ans = 0;
    for(int i = 1; i < m-1; i++){
        ans += cross(p[i]-p[0], p[i+1]-p[0]);
    }
    return ans / 2;
}

int main(){
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    for(int i = 0; i < n; i++){
        int j = (i + 1) % n;
        l[i] = Line(p[i], p[j] - p[i]);
    }
    for(int i = 1; i < n; i++){
        int j = (i + 1) % n;
        double A = p[1].y - p[0].y - p[j].y + p[i].y;
        double B = p[0].x - p[1].x + p[j].x - p[i].x;
        double C = cross(p[i], p[j]) - cross(p[0], p[1]);
        l[n-1+i]= Line(-C / (A * A + B * B) * Point(A, B), Point(B, -A));
    }
    int m = get_halfplane(l, 2*n-1, vtx);
    printf("%.4lf\n", get_area(vtx, m) / get_area(p, n));
    return 0;
}