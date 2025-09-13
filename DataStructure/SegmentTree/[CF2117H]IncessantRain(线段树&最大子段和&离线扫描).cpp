#include <bits/stdc++.h>
using namespace std;

/* =========================
 * 1) 最大子段和（MSS）线段树
 * 需求：不 build；初始全为 -1；单点修改；clear：把 best>0 的部分暴力递归清空为 -1
 * 仅使用数组和函数；不使用 lazy/pushdown
 * ========================= */
const int MAXN = 300000 + 5;

static int segSum[4*MAXN];
static int segPref[4*MAXN];
static int segSuff[4*MAXN];
static int segBest[4*MAXN];
static unsigned char builtChild[4*MAXN]; // 是否已经初始化过子节点（只标记“是否建过子树”）
static int N1;

/* 把节点 p 表示的长度为 len 的区间，设置为“全是 -1”的状态 */
inline void set_all_neg(int p, int len){
    segSum[p]  = -(int)len;
    segPref[p] = -1;
    segSuff[p] = -1;
    segBest[p] = -1;
}

/* 叶子：把节点 p 设为单点值 val */
inline void set_leaf_val(int p){
    auto val = -segSum[p];
    segSum[p] = segPref[p] = segSuff[p] = segBest[p] = val;
}

/* 合并 p = merge(L, R) */
inline void merge_node(int p, int Lc, int Rc){
    segSum[p]  = segSum[Lc] + segSum[Rc];
    segPref[p] = max(segPref[Lc], segSum[Lc] + segPref[Rc]);
    segSuff[p] = max(segSuff[Rc], segSum[Rc] + segSuff[Lc]);
    segBest[p] = max({segBest[Lc], segBest[Rc], segSuff[Lc] + segPref[Rc]});
}

/* 若 p 还没“建过子树”，就把左右子区间初始化成“全 -1” */
inline void ensure_children(int p, int l, int r){
    if(builtChild[p] || l==r) return;
    int m = (l + r) >> 1;
    int lc = p<<1, rc = p<<1|1;
    set_all_neg(lc, m - l + 1);
    set_all_neg(rc, r - m);
    builtChild[p] = 1;
}

/* 初始化：不 build；仅把根设为整段全 -1，标记“未建过子树” */
void init_mss(int n){
    N1 = n;
    set_all_neg(1, N1);
    // 安全起见清零 builtChild（其余数组值会在需要时被覆盖）
    memset(builtChild, 0, sizeof(unsigned char)*4*n);
}

/* 单点修改：a[idx] = val */
void point_update_mss(int p, int l, int r, int idx){
    if(l == r){
        set_leaf_val(p);
        // 叶子无子树
        return;
    }
    ensure_children(p, l, r);
    int m = (l + r) >> 1;
    if(idx <= m) point_update_mss(p<<1, l, m, idx);
    else         point_update_mss(p<<1|1, m+1, r, idx);
    merge_node(p, p<<1, p<<1|1);
}
inline void point_update_mss(int idx){
    point_update_mss(1, 0, N1-1, idx);
}

/* clear：把“最大子段和 > 0”的区间暴力下探清空为 -1 */
void clear_pos_mss(int p, int l, int r){
    if(segBest[p] <= 0) return;       // 该段没有正贡献，无需处理
    if(l == r){
        set_leaf_val(p);
        return;
    }
    ensure_children(p, l, r);         // 需要下探时才建默认子树（全 -1）
    int m = (l + r) >> 1;
    clear_pos_mss(p<<1, l, m);
    clear_pos_mss(p<<1|1, m+1, r);
    merge_node(p, p<<1, p<<1|1);
}

/* 查询整个数组的最大子段和（如需） */
inline int best_all_mss(){
    return segBest[1];
}

/* =========================
 * 2) 区间 max 覆盖（永久化标记）
 * 需求：只更新 tag，不 pushdown；最后一次 DFS 收集每点值
 * ========================= */
static int tagMax[4*MAXN];
static int N2;
static const int NEG_INF = (int)-4e18;

void init_chmax(int n){
    N2 = n;
    // 所有 tag 置为 -∞，表示“无下界约束”
    fill(tagMax, tagMax + 4*n, NEG_INF);
}

/* a[i] = max(a[i], x) for i in [L, R] —— 永久化标记 */
void range_chmax(int p, int l, int r, int L, int R, int x){
    if(r < L || R < l) return;
    if(L <= l && r <= R){
        tagMax[p] = max(tagMax[p], x);
        return;
    }
    int m = (l + r) >> 1;
    range_chmax(p<<1,   l,   m, L, R, x);
    range_chmax(p<<1|1, m+1, r, L, R, x);
}
inline void range_chmax(int L, int R, int x){
    range_chmax(1, 0, N2-1, L, R, x);
}

/* 最后一次 DFS：把祖先最大 tag 向下携带，到叶子与 base[i] 取 max */
void dfs_collect(int p, int l, int r, int carry, vector<int>& out){
    int cur = max(carry, tagMax[p]);
    if(l == r){
        out[l] = cur;
        return;
    }
    int m = (l + r) >> 1;
    dfs_collect(p<<1,   l,   m, cur, out);
    dfs_collect(p<<1|1, m+1, r, cur, out);
}
vector<int> collect_chmax(){
    vector<int> out(N2);
    dfs_collect(1, 0, N2-1, NEG_INF, out);
    return out;
}

int main() {
    int T, n, q;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &q);
        vector<int> a(n + 1);
        vector<vector<pair<int,int>>> ops(n + 1);
        for(int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            // (x,y): 在 x 时刻，位置 i 发生了一次修改（改为 x 或从 x 改为别的）
            ops[a[i]].emplace_back(0, i);
        }
        for(int i = 1; i <= q; i++) {
            int x, pos;
            scanf("%d%d", &pos, &x);
            if (x == a[pos]) continue;
            ops[a[pos]].emplace_back(i, pos);
            ops[x].emplace_back(i, pos);
            a[pos] = x;
        }
        init_mss(n + 1);
        init_chmax(q + 1);
        for(int x = 1; x <= n; x++) {
            int i = 0;
            while (i < ops[x].size()) {
                int j = i;
                while(j < ops[x].size() && ops[x][j].first == ops[x][i].first) {
                    point_update_mss(ops[x][j].second);
                    j++;
                }
                int endpos = (j == ops[x].size()) ? q : ops[x][j].first - 1;
                range_chmax(ops[x][i].first, endpos, best_all_mss() / 2);
                i = j;
            }
            clear_pos_mss(1, 0, N1-1);
        }
        auto ans = collect_chmax();
        for (int i = 1; i <= q; i++)
            printf("%d ", ans[i]);
        printf("\n");
    }
    return 0;
}