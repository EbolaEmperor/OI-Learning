#include <bits/stdc++.h>
using namespace std;

const int N = 400010;
struct Point{
    int x, y;
    Point(const int &x=0, const int &y=0): x(x), y(y) {}
} p[N];
int n;

long long dist2(const Point &a, const Point &b){
    return (long long) (a.x-b.x) * (a.x-b.x) + (long long) (a.y-b.y) * (a.y-b.y);
}

bool cmpx(const Point &a, const Point &b){
    return a.x < b.x;
}

bool cmpy(const Point &a, const Point &b){
    return a.y < b.y;
}

long long findmin(int l, int r){
    if(r - l <= 5){
        long long ans = 1ll<<62;
        for(int i = l; i <= r; i++)
            for(int j = i+1; j <= r; j++)
                ans = min(ans, dist2(p[i], p[j]));
        sort(p+l, p+r+1, cmpy);
        return ans;
    }

    int mid = (l + r) / 2;
    // 一定要先求出 xm，否则 子区间 findmin 里会重新排序，再出来的 p[mid] 就不再是中间的点了
    double xm = 0.5 * (p[mid].x + p[mid+1].x);
    long long h2 = findmin(l, mid);
    h2 = min(h2, findmin(mid+1, r));
    double h = sqrt(h2);

    inplace_merge(p+l, p+mid+1, p+r+1, cmpy);
    static Point B[N];
    int bcnt = 0;
    for(int i = l; i <= r; i++)
        if(p[i].x >= xm-h && p[i].x <= xm+h)
            B[++bcnt] = p[i];
    
    long long ans = h2;
    for(int i = 1; i <= bcnt; i++)
        for(int j = i-1; j >= 1 && B[j].y >= B[i].y-h; j--)
            ans = min(ans, dist2(B[i], B[j]));
    return ans;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", &p[i].x, &p[i].y);
    sort(p+1, p+1+n, cmpx);
    cout << findmin(1, n) << endl;
    return 0;
}