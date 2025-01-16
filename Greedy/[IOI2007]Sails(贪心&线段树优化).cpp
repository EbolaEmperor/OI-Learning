// 思路参考 https://www.luogu.com.cn/article/ig3lwzi4
#include <bits/stdc++.h>
#define ls (o << 1)
#define rs (o << 1 | 1)
using namespace std;

const int N = 100010;
struct Sail{
    int h, k;
    bool operator < (const Sail &rhs) const{
        return h < rhs.h;
    }
} sail[N];
int n, tr[N << 2], tag[N << 2];
// 对于叶子节点，保存如下数据：
// s[i]: h=i 的高度上有几面旗帜
//       由于具体哪个高度几面旗帜不重要，故将 s 从大到小排序
// 对于非叶子节点，保存区间内 s 的最小值
// 对于每根旗杆，在高度为 1～h 里贪心选 k 个 s 值最小的来挂旗子

inline void down(int o, int x){
    tr[o] += x; tag[o] += x;
}

void pushdown(int o){
    if(!tag[o]) return;
    down(ls, tag[o]);
    down(rs, tag[o]);
    tag[o] = 0;
}

int leftmost(int o, int l, int r, int x){
    if(l == r) return l;
    int mid = (l + r) / 2; pushdown(o);
    return (tr[ls] <= x) ? leftmost(ls, l, mid, x)
                         : leftmost(rs, mid + 1, r, x);
}

int getval(int o, int l, int r, int k){
    if(l == r) return tr[o];
    int mid = (l + r) / 2; pushdown(o);
    return (k <= mid) ? getval(ls, l, mid, k)
                      : getval(rs, mid + 1, r, k);
}

void addone(int o, int l, int r, int nl, int nr){
    if(l >= nl && r <= nr) return down(o, 1);
    int mid = (l + r) / 2; pushdown(o);
    if(nl <= mid) addone(ls, l, mid, nl, nr);
    if(nr > mid) addone(rs, mid + 1, r, nl, nr);
    tr[o] = min(tr[ls], tr[rs]);
}

long long getans(int o, int l, int r){
    if(l == r) return (long long) tr[o] * (tr[o] - 1) / 2;
    int mid = (l + r) / 2; pushdown(o);
    return getans(ls, l, mid) + getans(rs, mid + 1, r);
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d%d", &sail[i].h, &sail[i].k);
    sort(sail + 1, sail + 1 + n);
    int maxh = sail[n].h + 1;
    for(int i = 1; i <= n; i++){
        int h = sail[i].h, k = sail[i].k;
        int s = getval(1, 1, maxh, h - k + 1);
        int pos = leftmost(1, 1, maxh, s);
        if(s == 0)
            addone(1, 1, maxh, pos, pos + k - 1);
        else {
            int r = leftmost(1, 1, maxh, s - 1);
            if(r > h)
                addone(1, 1, maxh, pos, pos + k - 1);
            else {
                addone(1, 1, maxh, r, h);
                assert(k - (h - r + 1) - 1 >= 0);
                addone(1, 1, maxh, pos, pos + k - (h - r + 1) - 1);
            }
        }
    }
    cout << getans(1, 1, maxh) << endl;
    return 0;
}