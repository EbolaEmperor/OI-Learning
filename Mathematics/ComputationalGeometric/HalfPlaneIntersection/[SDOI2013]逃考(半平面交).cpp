#include <bits/stdc++.h>
using namespace std;

struct Point{
    double x, y;
    Point(double x=0, double y=0): x(x), y(y) {}
} p[400005], vtx[400005];
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
    int id;
    Line(){}
    Line(const Point &a, const Vector &v, const int &id):
        a(a), v(v), id(id) {}
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
} l[400005];

bool operator < (const Line &a, const Line &b){
    double x = a.polar(), y = b.polar();
    // 极角更小，或极角相等但是 a 在 b 左侧
    return dcmp(x-y) < 0 || dcmp(x-y) == 0
           && b.onleft(a.a);
}

int tot = 0;

int get_halfplane(Line l[], int tot, Point vertex[], int line_id[]){
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
    while(!line_que.empty()){
        line_id[res] = line_que.front().id;
        line_que.pop_front();
        vertex[res++] = vertex_que.front();
        vertex_que.pop_front();
    }
    return res;
}

double in_convex(Point p[], const int &m, const Point &q){
    if(m == 0) return false;
    for(int i = 0; i < m; i++){
        int j = (i + 1) % m;
        if( dcmp(cross(p[j] - p[i], q - p[i])) < 0 )
            return false;
    }
    return true;
}

int adj[400005], s;
std::vector<int> g[400005];

int bfs(int n){
    static bool vis[400005];
    static int dis[400005];
    memset(vis, 0, sizeof(bool) * (n+1));
    queue<int> q;
    q.push(s);
    vis[s] = 1;
    dis[s] = 0;

    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v : g[u]){
            if(vis[v]) continue;
            dis[v] = dis[u] + 1;
            vis[v] = 1;
            q.push(v);
        }
    }

    return dis[n];
}

int main(){
    Point yang;
    int T, n, W, H;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        scanf("%d%d%lf%lf", &W, &H, &yang.x, &yang.y);
        for(int i = 0; i < n; i++){
            scanf("%lf%lf", &p[i].x, &p[i].y);
            g[i].clear();
        }
        g[n].clear();
        for(int i = 0; i < n; i++){
            int tot = 0;
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                l[tot++] = Line((p[i]+p[j])/2, rotate90(p[j]-p[i]), j);
            }
            // 矩形边界
            l[tot++] = Line(Point(0, 0), Vector(1, 0), n);
            l[tot++] = Line(Point(W, 0), Vector(0, 1), n);
            l[tot++] = Line(Point(W, H), Vector(-1, 0), n);
            l[tot++] = Line(Point(0, H), Vector(0, -1), n);

            int m = get_halfplane(l, tot, vtx, adj);
            for(int j = 0; j < m; j++){
                g[i].push_back(adj[j]);
                g[adj[j]].push_back(i);
            }
            if(in_convex(vtx, m, yang)) s = i;
        }
        printf("%d\n", bfs(n));
    }
    return 0;
}