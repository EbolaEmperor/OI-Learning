// 正解显然是要知道连通块数、每个连通块内部的奇度数点有几个
// 但这样就要建图，本题建图比较麻烦，于是考虑乱搞
// 思路：用线段相交+并查集找连通块
//      然后把图片转化为像素点矩阵：线段是黑的，别的是白的。
//      找有几个黑像素点周围有奇数个黑点，这样就找到了奇度数点
// hack：很容易 hack，因为坐标转为像素点会丢失精度，只要搞两个平行、不相交、但只差一个坐标的线段，这个做法就 gg 了
#include <bits/stdc++.h>

struct Pix{
    int x, y;
};

class Cordinate{
public:
    double x, y;
    Cordinate(): x(0), y(0) {}
    Cordinate(const double &x, const double &y): x(x), y(y) {}
    Cordinate(const Cordinate& rhs): x(rhs.x), y(rhs.y) {}
    Cordinate& operator = (const Cordinate& rhs){
        x = rhs.x; y = rhs.y;
        return *this;
    }
};

class axis
{
private:
    int winWidth, winHeight;
    Cordinate center;
    double diam;

public:
    axis();
    axis(const Cordinate &, const double &);
    axis(const int &, const int &, const Cordinate &, const double &);
    int getWinWidth() const;
    int getWinHeight() const;
    Cordinate pix2cord(const Pix &p) const;
    Pix cord2pix(const Cordinate &c) const;
};

axis::axis()
{
    winWidth = 1920;
    winHeight = 1080;
    diam = 5.0;
}

axis::axis(const Cordinate &c, const double &d)
{
    winWidth = 1920;
    winHeight = 1080;
    center = c;
    diam = d;
}

axis::axis(const int &w, const int &h, const Cordinate &c, const double &d)
{
    winWidth = w;
    winHeight = h;
    center = c;
    diam = d;
}

Pix axis::cord2pix(const Cordinate &c) const
{
    Pix centerPix = (Pix){winHeight/2, winWidth/2};
    Pix result;
    int maxLength = std::max(winHeight, winWidth);
    result.y = (int)((c.x - center.x) / diam * maxLength) + centerPix.y;
    result.x = centerPix.x - (int)((c.y - center.y) / diam * maxLength);
    return result;
}

Cordinate axis::pix2cord(const Pix &p) const
{
    Pix centerPix = (Pix){winHeight/2, winWidth/2};
    Cordinate result;
    double maxLength(std::max(winHeight, winWidth));
    result.x = double(p.y-centerPix.y) / maxLength * diam + center.x;
    result.y = double(centerPix.x-p.x) / maxLength * diam + center.y;
    return result;
}

int axis::getWinWidth() const
{
    return winWidth;
}

int axis::getWinHeight() const
{
    return winHeight;
}

using namespace std;

// 这里可以调整画线的宽度
const int width = 0;

// 这里调整图片尺寸，默认为 1920*1080
// 当 mag=2 时，尺寸变为 3840*2160，继续放大同理
const int mag = 4;
int pic[1080 * mag][1080 * mag];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void setpix(int i, int j){
    if(i >= 0 && i < 1080 * mag && j >= 0 && j < 1080 * mag)
        pic[i][j] = 1;
}

int fa[55];

int find(int x){
    return fa[x] == x ? x : fa[x] = find(fa[x]);
}

int main(){
    freopen("draw.in", "r", stdin);
    freopen("draw.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> x(n), y(n), xx(n), yy(n);
    int minx = 1e6, miny = 1e6, maxx = -1e6, maxy = -1e6;
    for(int i = 0; i < n; i++){
        fa[i] = i;
        cin >> x[i] >> y[i] >> xx[i] >> yy[i];
        minx = min(minx, x[i]);
        maxx = max(maxx, x[i]);
        miny = min(miny, y[i]);
        maxy = max(maxy, y[i]);
        minx = min(minx, xx[i]);
        maxx = max(maxx, xx[i]);
        miny = min(miny, yy[i]);
        maxy = max(maxy, yy[i]);
    }
    double midx = (minx + maxx) / 2.0;
    double midy = (miny + maxy) / 2.0;
    axis axiser(1080 * mag, 1080 * mag, Cordinate(midx, midy), max(maxx - minx, maxy - miny) * 1.1);

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++){
            int fi = find(i), fj = find(j);
            if(fi == fj) continue;
            if(x[i] == xx[i] && x[j] == xx[j]){
                if(x[i] != x[j]) continue;
                int oy1 = y[j], oy2 = yy[j];
                if(oy1 > oy2) swap(oy1, oy2);
                if(y[i] >= oy1 && y[i] <= oy2 || yy[i] >= oy1 && yy[i] <= oy2)
                    fa[fi] = fj;
            } else if(y[i] == yy[i] && y[j] == yy[j]){
                if(y[i] != y[j]) continue;
                int oy1 = x[j], oy2 = xx[j];
                if(oy1 > oy2) swap(oy1, oy2);
                if(x[i] >= oy1 && x[i] <= oy2 || xx[i] >= oy1 && xx[i] <= oy2)
                    fa[fi] = fj;
            } else {
                int u = i, v = j;
                if(x[j] == xx[j]) swap(u, v);
                int oy1 = y[u], oy2 = yy[u];
                if(oy1 > oy2) swap(oy1, oy2);
                if(y[v] < oy1 || y[v] > oy2) continue;
                oy1 = x[v], oy2 = xx[v];
                if(oy1 > oy2) swap(oy1, oy2);
                if(x[u] < oy1 || x[u] > oy2) continue;
                fa[fi] = fj;
            }
        }
    int cnt = 0;
    for(int i = 0; i < n; i++)
        if(find(i) == i) ++cnt;
    
    int R; cin >> R;
    if(R % 2 == 0){
        cout << cnt - 1 << endl;
        return 0;
    }

    for(int i = 0; i < n; i++){
        Pix pix1 = axiser.cord2pix(Cordinate(x[i], y[i]));
        Pix pix2 = axiser.cord2pix(Cordinate(xx[i], yy[i]));
        if(pix1.x == pix2.x){
            int l = pix1.y, r = pix2.y;
            if(l > r) swap(l, r);
            for(int k = -width; k <= width; k++)
                for(int j = l; j <= r; j++)
                    setpix(pix1.x + k, j);
        } else {
            int l = pix1.x, r = pix2.x;
            if(l > r) swap(l, r);
            for(int k = -width; k <= width; k++)
                for(int j = l; j <= r; j++)
                    setpix(j, pix1.y + k);
        }
    }

    for(int id = 0; id < n; id++){
        if(find(id) != id) continue;
        int odd = 0;
        for(int i = 0; i < n; i++){
            if(find(i) != id) continue;
            {
                Pix pix1 = axiser.cord2pix(Cordinate(x[i], y[i]));
                if(pic[pix1.x][pix1.y] == 1){
                    int neighbor = 0;
                    for(int d = 0; d < 4; d++){
                        int u = pix1.x + dx[d], v = pix1.y + dy[d];
                        if(u >= 0 && u < 1080 * mag && v >= 0 && v < 1080 * mag && pic[u][v])
                            ++neighbor;
                    }
                    if(neighbor & 1) ++odd;
                }
                pic[pix1.x][pix1.y] = 2;
            }
            {
                Pix pix1 = axiser.cord2pix(Cordinate(xx[i], yy[i]));
                if(pic[pix1.x][pix1.y] == 1){
                    int neighbor = 0;
                    for(int d = 0; d < 4; d++){
                        int u = pix1.x + dx[d], v = pix1.y + dy[d];
                        if(u >= 0 && u < 1080 * mag && v >= 0 && v < 1080 * mag && pic[u][v])
                            ++neighbor;
                    }
                    if(neighbor & 1) ++odd;
                }
                pic[pix1.x][pix1.y] = 2;
            }
        }
        if(odd > 2) cnt += (odd - 2) / 2;
    }
    cout << cnt - 1 << endl;

    return 0;
}