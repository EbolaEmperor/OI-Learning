// 设 f(x0) 表示三角形覆盖部分与直线 x=x0 相交的长度
// 注意到 f 是一个分段线性函数，所以找出所有分段点，每一段内用中点积分公式即可
#include<bits/stdc++.h>
using namespace std;

const int M = 2005;

bool lowerSide(int x, int y, int l){
    return x + y < l;
}

class TriangleUnion{
private:
    int x[M], y[M], l[M], n;

public:
    void read(){
        scanf("%d", &n);
        for(int i = 1; i <= n; i++)
            scanf("%d%d%d", x + i, y + i, l + i);
    }

    vector<int> getKnots() const{
        vector<int> knots;
        for(int i = 1; i <= n; i++){
            knots.push_back(x[i]);
            knots.push_back(x[i] + l[i]);
            for(int j = 1; j <= n; j++){
                if(j == i) continue;
                // 求斜线和竖线的交点
                if(y[j] > y[i] && y[j] < y[i] + l[i]
                  && (lowerSide(x[j] - x[i], y[j] - y[i], l[i]) ^ 
                      lowerSide(x[j] + l[j] - x[i], y[j] - y[i], l[i])))
                    knots.push_back(x[i] + y[i] + l[i] - y[j]);
            }
        }
        sort(knots.begin(), knots.end());
        int m = unique(knots.begin(), knots.end()) - knots.begin();
        knots.resize(m);
        return knots;
    }

    double operator () (double x0) const{
        vector<pair<double, double>> seg;
        for(int i = 1; i <= n; i++){
            if(x0 >= x[i] && x0 < x[i] + l[i])
                seg.emplace_back(y[i], y[i] + l[i] - (x0 - x[i]));
        }
        if(seg.empty()) return 0;
        sort(seg.begin(), seg.end());
        double len = 0, prel = -1e7, prer = -1e7;
        for(auto [yl, yr] : seg){
            if(yl > prer){
                len += prer - prel;
                prel = yl;
                prer = yr;
            } else {
                prer = max(prer, yr);
            }
        }
        len += prer - prel;
        return len;
    }
} triangle;

int main(){
    triangle.read();
    auto knots = triangle.getKnots();
    double ans = 0;
    for(int i = 0; i < knots.size() - 1; i++)
        ans += triangle((knots[i] + knots[i + 1]) / 2.) * (knots[i + 1] - knots[i]);
    printf("%.1lf\n", ans);
    return 0;
}