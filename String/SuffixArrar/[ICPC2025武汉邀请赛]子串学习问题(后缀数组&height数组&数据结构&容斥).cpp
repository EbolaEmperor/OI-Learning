#include <bits/stdc++.h>
#include "debug.h"
using namespace std;

struct SuffixArray {
    int n;
    string s;
    vector<int> sa, rk, height;
    vector<int> lg2;
    vector<vector<int>> st;          // 稀疏表

    SuffixArray(const string& str) : n((int)str.size()), s(str) {
        build_sa();
        build_height();
        build_st();
    }

    /* --------- 构建后缀数组（倍增 + sort） --------- */
    void build_sa() {
        sa.resize(n + 1);
        rk.resize(n + 1);
        vector<int> tmp(n + 1);
        for (int i = 1; i <= n; ++i) {
            sa[i] = i;
            rk[i] = s[i - 1];        // 先按单字符排名
        }
        for (int k = 1;; k <<= 1) {
            auto cmp = [&](int a, int b) {
                if (rk[a] != rk[b]) return rk[a] < rk[b];
                int ra = (a + k <= n) ? rk[a + k] : -1;
                int rb = (b + k <= n) ? rk[b + k] : -1;
                return ra < rb;
            };
            sort(sa.begin() + 1, sa.end(), cmp);
            tmp[sa[1]] = 1;
            for (int i = 2; i <= n; ++i) {
                tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
            }
            rk.swap(tmp);
            if (rk[sa[n]] == n) break;   // 已全部唯一
        }
        /* sa[i] 表示排名为 i 的后缀位置（1-based） */
        /* rk[pos] 表示后缀 pos 的排名（1..n）      */
    }

    /* --------- 构建 height 数组 (Kasai) --------- */
    void build_height() {
        height.assign(n + 1, 0);
        int k = 0;
        for (int i = 1; i <= n; ++i) {
            int r = rk[i];
            if (r == 1) continue;        // 最小的后缀
            int j = sa[r - 1];
            while (i + k <= n && j + k <= n && s[i - 1 + k] == s[j - 1 + k]) ++k;
            height[r] = k;
            if (k) --k;
        }
        /* h[1] = 0，其余同定义 */
    }

    /* --------- 构建 height 的 RMQ 稀疏表 --------- */
    void build_st() {
        lg2.resize(n + 1);
        lg2[1] = 0;
        for (int i = 2; i <= n; ++i) lg2[i] = lg2[i >> 1] + 1;
        int K = lg2[n] + 1;
        st.assign(K, vector<int>(n + 1));
        for (int i = 1; i <= n; ++i) st[0][i] = height[i];
        for (int k = 1; k < K; ++k) {
            for (int i = 1; i + (1 << k) - 1 <= n; ++i) {
                st[k][i] = min(st[k - 1][i], st[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    /* 在 height 中求区间最小值，闭区间 [l,r]，要求 l<=r */
    int rmq(int l, int r) const {
        if (l > r) return INT_MAX;
        int k = lg2[r - l + 1];
        return min(st[k][l], st[k][r - (1 << k) + 1]);
    }

    /* 查询两个后缀的 LCP 长度 */
    int lcp(int i, int j) const {
        if (i == j) return n - i + 1;
        int a = rk[i], b = rk[j];
        if (a > b) swap(a, b);
        return rmq(a + 1, b);
    }

    /* 给定后缀排名 pos 和前缀长度 len，二分得到最左 L、最右 R */
    pair<int,int> range_with_prefix(int pos, int len) const {
        int L = pos, R = pos;
        /* 向左二分 */
        int lo = 1, hi = pos;
        while (lo < hi) {
            int mid = (lo + hi) >> 1;
            if (rmq(mid + 1, pos) >= len) hi = mid;
            else lo = mid + 1;
        }
        L = lo;
        /* 向右二分 */
        lo = pos, hi = n;
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if (rmq(pos + 1, mid) >= len) lo = mid;
            else hi = mid - 1;
        }
        R = lo;
        return {L, R};
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    if (!(cin >> s)) return 0;
    int n = (int)s.size();

    SuffixArray SA(s);                      // 后缀数组相关结构

    /* val[i] = 该后缀排名 i 目前还能贡献的新串数量 */
    vector<long long> val(n + 1);
    for (int i = 1; i <= n; ++i) {
        int h = (i == 1) ? 0 : SA.height[i];
        val[i] = 1LL * n - SA.sa[i] + 1 - h;
        // cout << val[i] << ' ';
    }
    // cout << '\n';

    set<int> alive;                         // 仍有贡献的排名下标
    for (int i = 1; i <= n; ++i) alive.insert(i);

    long long cur = 0;                      // 词典当前大小

    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        int len = r - l + 1;
        int pos = SA.rk[l];                 // 该子串对应的后缀排名
        auto [L, R] = SA.range_with_prefix(pos, len);

        long long add = 0;

        /* 处理区间 (L, R] 中的后缀：一次性清零 */
        auto it = alive.lower_bound(L + 1);
        while (it != alive.end() && *it <= R) {
            int idx = *it;
            add += val[idx];
            // cout << "erase " << idx << " " << val[idx] << " " << add << '\n';
            val[idx] = 0;
            it = alive.erase(it);           // erase 返回下一个迭代器
        }

        /* 处理 L 本身 */
        if (alive.count(L) && val[L] > len - SA.height[L] - 1) {
            // cout << "ans=" << add << endl;
            // cout << L << " " << SA.height[L] << " " << len << " " << val[L] << '\n';
            long long delta = val[L] - (len - SA.height[L] - 1);
            add += delta;
            val[L] -= delta;
            if (val[L] == 0) alive.erase(L);
        }

        cur += add;
        cout << cur << '\n';
        // debug(alive);
    }
    return 0;
}