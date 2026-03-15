#include <bits/stdc++.h>
using namespace std;

const int N = 400010;
struct Point{
    double x, y;
    Point(const double &x=0, const double &y=0): x(x), y(y) {}
} p[N];
int n;

double dist(const Point &a, const Point &b){
    return sqrt((a.x-b.x) * (a.x-b.x) + (a.y-b.y) * (a.y-b.y));
}

bool cmpx(const Point &a, const Point &b){
    return a.x < b.x;
}

bool cmpy(const Point &a, const Point &b){
    return a.y < b.y;
}

tuple<double, Point, Point> findmin(int l, int r){
    if(r - l <= 5){
        double ans = 1e20;
        Point ans1, ans2;
        for(int i = l; i <= r; i++)
            for(int j = i+1; j <= r; j++) {
                double d = dist(p[i], p[j]);
                if(d < ans) {
                    ans = d;
                    ans1 = p[i];
                    ans2 = p[j];
                }
            }
        sort(p+l, p+r+1, cmpy);
        return make_tuple(ans, ans1, ans2);
    }

    int mid = (l + r) / 2;
    // 一定要先求出 xm，否则 子区间 findmin 里会重新排序，再出来的 p[mid] 就不再是中间的点了
    double xm = 0.5 * (p[mid].x + p[mid+1].x);
    auto [h, ans1, ans2] = findmin(l, mid);
    auto [h2, ans3, ans4] = findmin(mid+1, r);
    if(h2 < h) {
        h = h2;
        ans1 = ans3;
        ans2 = ans4;
    }
    
    inplace_merge(p+l, p+mid+1, p+r+1, cmpy);
    static Point B[N];
    int bcnt = 0;
    for(int i = l; i <= r; i++)
        if(fabs(p[i].x - xm) < h)
            B[++bcnt] = p[i];
    
    double ans = h;
    for(int i = 1; i <= bcnt; i++)
        for(int j = i-1; j >= 1 && B[i].y - B[j].y < h; j--) {
            double d = dist(B[i], B[j]);
            if(d < ans) {
                ans = d;
                ans1 = B[i];
                ans2 = B[j];
            }
        }
    return make_tuple(ans, ans1, ans2);
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    sort(p+1, p+1+n, cmpx);
    auto [ans, ans1, ans2] = findmin(1, n);
    printf("%g\n", ans);
    printf("(%.16f, %.16f)\n", ans1.x, ans1.y);
    printf("(%.16f, %.16f)\n", ans2.x, ans2.y);
    return 0;
}