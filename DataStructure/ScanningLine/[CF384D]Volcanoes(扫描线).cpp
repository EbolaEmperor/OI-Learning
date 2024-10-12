#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

struct Point{
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator < (const Point &rhs) const{
        return x < rhs.x || x == rhs.x && y < rhs.y;
    }
};

struct Segment{
    int l, r;
    Segment(int l = 0, int r = 0) : l(l), r(r) {}
};

const int N = 100010;
Point pnt[N];
int n, m;

int main(){
    cin >> n >> m;
    for(int i = 1; i <= m; i++)
        cin >> pnt[i].x >> pnt[i].y;
    pnt[++m] = Point(n, n + 1);
    pnt[++m] = Point(1, n + 1);
    sort(pnt + 1, pnt + 1 + m);
    vector<Segment> seg;
    seg.emplace_back(1, 1);
    for(int i = 1, j; i <= m; i = j){
        if(i > 1 && pnt[i].x != pnt[i - 1].x + 1){
            // 如果隔了一整列空的，那 seg[0].l 到 n 都是可达的纵坐标
            int tmp = seg[0].l;
            seg.clear();
            seg.emplace_back(tmp, n);
        }
        vector<Segment> newseg;
        vector<int> py;
        int p = 0, y = 0; j = i;
        while(j <= m && pnt[j].x == pnt[i].x)
            py.push_back(pnt[j++].y);
        if(j <= m) py.push_back(n + 1);
        for(int nexty : py){
            if(nexty > y + 1){
                // 找到前一列里第一个能到达纵坐标区间 (y, nexty) 的线段
                while(p < seg.size() && seg[p].r <= y) p++;
                if(p < seg.size() && seg[p].l < nexty)
                    // 从前面一列的 (y, nexty) 中第一个可到位置，一直到 nexty - 1，在本列中都是可到的
                    newseg.emplace_back(max(y + 1, seg[p].l) , nexty - 1);
            }
            y = nexty;
        }
        swap(seg, newseg);
        if(seg.empty()) break;
    }
    cout << ( (!seg.empty() && seg.back().r == n) ? (2 * n - 2) : -1 ) << endl;
    return 0;
}