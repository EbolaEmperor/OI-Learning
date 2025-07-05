#include <bits/stdc++.h>
using namespace std;

const int MAXN = 400010;

struct Point{int x, y;};

long long dist2(const Point &p1, const Point &p2){
    return (long long) (p1.x-p2.x) * (p1.x-p2.x) + (long long) (p1.y-p2.y) * (p1.y-p2.y) ;
}

double dist(const Point &p1, const Point &p2){
    return sqrt(dist2(p1, p2));
}

double perimeter(const Point &p1, const Point &p2, const Point &p3){
    return dist(p1, p2) + dist(p2, p3) + dist(p3, p1);
}

bool cmpx(const Point &p1, const Point &p2){
    return p1.x < p2.x;
}

bool cmpy(const Point &p1, const Point &p2){
    return p1.y < p2.y;
}

double min_perimeter(Point p[], const int &l, const int &r){
    if(r - l <= 5){
        double ans = 1e18;
        for(int i = l; i < r; i++)
            for(int j = l; j < i; j++)
                for(int k = l; k < j; k++){
                    ans = min(ans, perimeter(p[i], p[j], p[k]));
            }
        sort(p + l, p + r, cmpy);
        return ans;
    }

    int mid = (l + r) / 2;
    double midx = (p[mid-1].x + p[mid].x) / 2.;
    double d = min(min_perimeter(p, l, mid), min_perimeter(p, mid, r));

    inplace_merge(p + l, p + mid, p + r, &cmpy);

    static Point B[MAXN];
    int pc = l;
    for(int i = l; i < r ; i++)
        if(p[i].x >= midx - d/2 && p[i].x <= midx + d/2)
            B[pc++] = p[i];
    for(int i = l; i < pc; i++)
        for(int j = i - 1; j >= l && B[j].y >= B[i].y - d/2; j--)
            for(int k = j - 1; k >= l && B[k].y >= B[i].y - d/2; k--)
                d = min(d, perimeter(B[i], B[j], B[k]));

    return d;
}

int main(){
    int n;
    static Point p[MAXN];

    while(1){
        scanf("%d", &n);
        if(n == -1) break;
        for(int i = 0; i < n; i++)
            scanf("%d%d", &p[i].x, &p[i].y);
        sort(p, p + n, cmpx);
        double ans = min_perimeter(p, 0, n);
        printf("%.3lf\n", ans); 
    }
    return 0;
}