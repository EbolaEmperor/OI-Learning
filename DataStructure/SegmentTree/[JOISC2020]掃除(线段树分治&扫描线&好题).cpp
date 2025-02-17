// 参考题解：https://www.luogu.com.cn/article/8ae0a4gc
#include <bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<20)+5;
    //Input Correlation
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline int read()
    {
        int x=0,fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x*fg;
    }
    //Output Correlation
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    struct END{~END(){flush();} } EENNDD;
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
}

const int P = 1e7;

// 动态开点线段树，支持区间更新 max、单点查询
class DynamicSegmentTree{
public:
    int maxtag[P], ls[P], rs[P], tot, root;
    DynamicSegmentTree() {tot = root = 1;}
    
    void clear(){
        memset(maxtag, 0, sizeof(int) * (tot + 1));
        memset(ls, 0, sizeof(int) * (tot + 1));
        memset(rs, 0, sizeof(int) * (tot + 1));
        tot = root = 1;
    }

    void upmax(int &o, int l, int r, int nl, int nr, int x){
        if(!o) o = ++tot;
        if(l >= nl && r <= nr){
            maxtag[o] = max(maxtag[o], x);
            return;
        }
        int mid = (l + r) / 2;
        if(nl <= mid) upmax(ls[o], l, mid, nl, nr, x);
        if(nr > mid) upmax(rs[o], mid + 1, r, nl, nr, x);
    }

    int getval(int o, int l, int r, int k){
        if(!o) return 0;
        if(l == r) return maxtag[o];
        int mid = (l + r) / 2, ans = maxtag[o];
        if(k <= mid) ans = max(ans, getval(ls[o], l, mid, k));
        else ans = max(ans, getval(rs[o], mid + 1, r, k));
        return ans;
    }
} dsgt, dsgt2;

struct Point{
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator < (const Point &rhs) const{
        return x < rhs.x || x == rhs.x && y < rhs.y;
    }
};

const int N = 1e6 + 5;
int n;
// 我们以清扫操作来计时，即，初始时刻为 0，每发生一次清扫操作，时刻就加一
// qst[i]: 能影响第 i 个询问的第一个操作时刻
// qend[i]: 能影响第 i 个询问的最后一个操作时刻
int qst[N], qend[N], qcnt = 0;
// qdirt[i]: 第 i 个询问的灰尘坐标（这里把灰尘复制一下，为了分治时方便处理）
// qtmp[i]: 分治时用的辅助数组
Point qdirt[N], qtmp[N];
// optype[i]: 第 i 个操作的类型。0: H 型清扫；1: V 型清扫
// opl[i]: 第 i 个操作的扫帚宽度
int optype[N], opl[N], opcnt = 0;
// dirt[i]: 第 i 堆灰尘的位置
Point dirt[N];
// dtime[i]: 第 i 堆灰尘的插入时刻
int dtime[N], dcnt = 0;

// qry[o]: 对于 o = [l,r]，这里存完整受到 [l,r] 时刻所有操作影响的询问编号
vector<int> qry[N << 2];

void insertQuery(int o, int l, int r, int nl, int nr, int id){
    if(l >= nl && r <= nr){
        qry[o].push_back(id);
        return;
    }
    int mid = (l + r) / 2;
    if(nl <= mid) insertQuery(o << 1, l, mid, nl, nr, id);
    if(nr > mid) insertQuery(o << 1 | 1, mid + 1, r, nl, nr, id);
}

bool cmpx(int i, int j){return qdirt[i].x < qdirt[j].x;}
bool cmpy(int i, int j){return qdirt[i].y < qdirt[j].y;}

void solve(int o, int l, int r){
    // 处理 [l,r] 时刻的所有操作，并对完整受到 [l,r] 里所有操作影响的询问施加影响
    // 这就转化为了无插入的问题：初始时刻有一堆灰尘，受到 [l,r] 操作的影响后改变位置。
    if(!qry[o].empty()){
        if(1ll * (r - l) * qry[o].size() <= 3 * (4 * (r - l) + 2 * qry[o].size()) * log2(n)){
            // 卡常小技巧：如果规模很小，就直接暴力做
            for(int i = l; i <= r; i++)
                for(int j : qry[o])
                    if(optype[i] == 0 && qdirt[j].y <= opl[i])
                        qdirt[j].x = max(qdirt[j].x, n - opl[i]);
                    else if(optype[i] == 1 && qdirt[j].x <= opl[i])
                        qdirt[j].y = max(qdirt[j].y, n - opl[i]);
        } else {
            vector<pair<int,int>> opH, opV;
            // 对 opH 与 opV 划分管辖领域
            dsgt.clear();
            dsgt2.clear();
            for(int i = l; i <= r; i++){
                if(optype[i] == 0){
                    int p = dsgt2.getval(dsgt2.root, 0, n, opl[i]);
                    opH.emplace_back(p, opl[i]);
                    dsgt.upmax(dsgt.root, 0, n, p, n - opl[i] - 1, opl[i] + 1);
                } else {
                    int p = dsgt.getval(dsgt.root, 0, n, opl[i]);
                    opV.emplace_back(p, opl[i]);
                    dsgt2.upmax(dsgt2.root, 0, n, p, n - opl[i] - 1, opl[i] + 1);
                }
            }

            // 划分好管辖领域后，两类操作相互独立。先处理 opH
            dsgt.clear();
            sort(opH.begin(), opH.end());
            sort(qry[o].begin(), qry[o].end(), cmpx);
            auto jt = opH.begin();
            for(int i : qry[o]){
                for(; jt != opH.end() && jt->first <= qdirt[i].x; ++jt)
                    dsgt.upmax(dsgt.root, 0, n, 0, jt->second, n - jt->second);
                qtmp[i].x = max(qdirt[i].x, dsgt.getval(dsgt.root, 0, n, qdirt[i].y));
            }

            // 再处理 opV
            dsgt.clear();
            sort(opV.begin(), opV.end());
            sort(qry[o].begin(), qry[o].end(), cmpy);
            jt = opV.begin();
            for(int i : qry[o]){
                for(; jt != opV.end() && jt->first <= qdirt[i].y; ++jt)
                    dsgt.upmax(dsgt.root, 0, n, 0, jt->second, n - jt->second);
                qtmp[i].y = max(qdirt[i].y, dsgt.getval(dsgt.root, 0, n, qdirt[i].x));
            }

            // 把算出来的 x、y 坐标拷贝回 qdirt 里
            for(int i : qry[o]) qdirt[i] = qtmp[i];
        }
    }

    if(l == r) return;
    int mid = (l + r) / 2;
    solve(o << 1, l, mid);
    solve(o << 1 | 1, mid + 1, r);
}

int main(){
    int m, q;
    n = IO::read();
    m = IO::read();
    q = IO::read();
    dcnt = m;
    for(int i = 1; i <= m; i++){
        dirt[i].x = IO::read();
        dirt[i].y = IO::read();
    }
    for(int i = 1; i <= q; i++){
        int t, x, y;
        t = IO::read();
        x = IO::read();
        if(t == 1){
            qdirt[++qcnt] = dirt[x];
            qst[qcnt] = dtime[x] + 1;
            qend[qcnt] = opcnt;
        } else if(t == 2 || t == 3){
            optype[++opcnt] = t - 2;
            opl[opcnt] = x;
        } else {
            y = IO::read();
            dirt[++dcnt] = Point(x, y);
            dtime[dcnt] = opcnt;
        }
    }

    if(opcnt){
        // 将询问插入线段树区间，然后开始分治
        for(int i = 1; i <= qcnt; i++)
            if(qst[i] <= qend[i])
                insertQuery(1, 1, opcnt, qst[i], qend[i], i);
        solve(1, 1, opcnt);
    }

    for(int i = 1; i <= qcnt; i++){
        IO::print(qdirt[i].x);
        IO::putc(' ');
        IO::print(qdirt[i].y);
        IO::putc('\n');
    }
    return 0;
}