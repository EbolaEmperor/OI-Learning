#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <algorithm>
#include <cmath>

using namespace std;

// 考虑到题目未给出明确 N，通常这类单调队列题 N 在 1e5 ~ 5e5 之间
// 开 500005 以防万一
const int MAXN = 500005;
long long a[MAXN];
long long sum[MAXN];
long long st[MAXN][22]; // ST表层数增加以适应更大的 N
int lg2[MAXN];

void build_st(int n) {
    lg2[1] = 0;
    for (int i = 2; i <= n; i++) lg2[i] = lg2[i/2] + 1;
    for (int i = 1; i <= n; i++) st[i][0] = sum[i];
    for (int j = 1; j < 22; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }
}

long long query_st(int l, int r) {
    if (l > r) return -4000000000000000000LL; 
    int k = lg2[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

struct Q1Element {
    int r;
    long long val;
};

struct Segment {
    int r_start, r_end;
    long long w;
    long long max_sum;
    long long val() const { return max_sum - w; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, L, R;
    if (!(cin >> n >> L >> R)) return 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i-1] + a[i];
    }

    build_st(n);

    deque<Q1Element> q1;
    list<Segment> q2;

    // 初始化 Q2 (提前处理 l < R 的部分)
    if (L < R) {
        Segment seg;
        seg.r_start = L;
        seg.r_end = R - 1;
        seg.w = 0;
        seg.max_sum = query_st(L, R - 1);
        q2.push_back(seg);
    }

    for (int i = 1; i <= n; i++) {
        // 1. 从 Q1 移除无效 (r < i)
        while (!q1.empty() && q1.front().r < i) {
            q1.pop_front();
        }

        // 2. 从 Q2 转移到 Q1 (r = i + L - 2)
        int r_move = i + L - 2;
        
        if (!q2.empty()) {
            auto it = q2.begin();
            if (it->r_start == r_move) {
                // 只有当 r >= i 时才有效进入 Q1
                if (r_move >= i) {
                    long long val = sum[r_move] - it->w;
                    while (!q1.empty() && q1.back().val <= val) {
                        q1.pop_back();
                    }
                    q1.push_back({r_move, val});
                }

                // 更新段的起始点
                it->r_start++;
                if (it->r_start > it->r_end) {
                    q2.pop_front(); // 段空了，移除
                } else {
                    // 段还在，更新 max_sum
                    it->max_sum = query_st(it->r_start, it->r_end);
                }

                // 维护 Q2 单调性：如果头部变弱了，且不如第二个强，弹出头部
                if (!q2.empty()) {
                    auto first = q2.begin();
                    if (q2.size() > 1) {
                        auto second = next(first);
                        if (first->val() <= second->val()) {
                            q2.pop_front();
                        }
                    }
                }
            }
        }

        // 3. 更新 Q2 后缀 (用 S[i-1])
        long long w_new = sum[i-1];
        int start_r = -1, end_r = -1;

        if (i + R - 1 <= n) {
            start_r = i + R - 1;
            end_r = i + R - 1;
        }

        // 合并 w 更劣的段
        while (!q2.empty() && q2.back().w >= w_new) {
            auto back_it = prev(q2.end());
            if (start_r == -1) {
                start_r = back_it->r_start;
                end_r = back_it->r_end;
            } else {
                start_r = back_it->r_start;
                end_r = max(end_r, back_it->r_end);
            }
            q2.pop_back();
        }

        if (start_r != -1) {
            Segment new_seg;
            new_seg.r_start = start_r;
            new_seg.r_end = end_r;
            new_seg.w = w_new;
            new_seg.max_sum = query_st(start_r, end_r);

            // 维护 Q2 单调性：如果新来的比尾部强，弹出尾部
            while (!q2.empty()) {
                if (q2.back().val() <= new_seg.val()) {
                    q2.pop_back();
                } else {
                    break;
                }
            }
            q2.push_back(new_seg);
        }

        // 4. 查询最大值
        long long max_val = -4000000000000000000LL;
        if (!q1.empty()) {
            max_val = max(max_val, q1.front().val);
        }
        if (!q2.empty()) {
            max_val = max(max_val, q2.front().val());
        }

        cout << max_val << (i == n ? "" : " ");
    }
    cout << endl;

    return 0;
}

