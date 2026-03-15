#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>

using namespace std;

const int MAXN = 50005;
long long a[MAXN];
long long sum[MAXN];
long long st[MAXN][20];
int lg2[MAXN];

void build_st(int n) {
    lg2[1] = 0;
    for (int i = 2; i <= n; i++) lg2[i] = lg2[i/2] + 1;
    for (int i = 1; i <= n; i++) st[i][0] = sum[i];
    for (int j = 1; j < 20; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
        }
    }
}

long long query_st(int l, int r) {
    if (l > r) return -4000000000000000000LL; // -4e18
    int k = lg2[r - l + 1];
    return max(st[l][k], st[r - (1 << k) + 1][k]);
}

struct Q1Element {
    int r;
    long long val;
};

struct Segment {
    int r_start, r_end;
    long long w;  // 最优左端点 l 对应的 S[l-1]
    long long max_sum;  // max_{r1 <= r <= r2}(S[r])
    long long val() const { return max_sum - w; }  // 这一段的最优价值： max_{r1 <= r <= r2}(S[r]) - S[l-1]
};

void solve() {
    int n;
    if (!(cin >> n)) return;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sum[i] = sum[i-1] + a[i];
    }
    build_st(n);
    int q;
    if (!(cin >> q)) return;

    while (q--) {
        int L, R;
        cin >> L >> R;

        deque<Q1Element> q1;
        deque<Segment> q2;

        // Pre-fill Q2 with [L, R-1] if applicable
        if (L < R) {
            Segment seg;
            seg.r_start = L;
            seg.r_end = R - 1;
            seg.w = 0;
            seg.max_sum = query_st(L, R - 1);
            q2.push_back(seg);
        }

        unsigned long long final_ans = 0;

        for (int i = 1; i <= n; i++) {
            // 1. Remove invalid from Q1 (r < i)
            while (!q1.empty() && q1.front().r < i) q1.pop_front();

            // 2. Move from Q2 to Q1
            // Valid r for Q1: r < i + L - 1.
            // The element becoming valid for Q1 at this step is r = i + L - 2.
            int r_move = i + L - 2;
            
            if (!q2.empty()) {
                if (q2.front().r_start == r_move) {
                    // Move to Q1 ONLY if valid (r >= i)
                    if (r_move >= i) {
                        long long val = sum[r_move] - q2.front().w;
                        while (!q1.empty() && q1.back().val <= val) { // 意味着 q1.back() 没用了，删掉
                            q1.pop_back();
                        }
                        q1.push_back({r_move, val}); // 传统的单调队列
                    }

                    // Update Segment
                    q2.front().r_start++;
                    if (q2.front().r_start > q2.front().r_end) q2.pop_front();
                    // 如果还有，因为 [r1,r2] 变成了 [r1+1,r2]，所以要更新 max_sum
                    else q2.front().max_sum = query_st(q2.front().r_start, q2.front().r_end);

                    // Maintain Q2 Monotonicity after front update
                    // If the front element becomes smaller than the second, it's useless forever.
                    // 注意要保持单调性：q2 里面区间的最优价值是递减的
                    // 如果有一段区间在另一段区间前面，且前面一段的最优价值更小，那前面一段就永远没用了
                    // 疑问：随着 i 往右枚举，Q2 里每一段的最优价值会更新，有没有可能更新之后，前面一段的价值又变得比后一段大了呢？
                    // 答案是没有可能。可以放心弹出去
                    if (q2.size() > 1) {
                        if (q2[0].val() <= q2[1].val())
                            q2.pop_front();
                    }
                }
            }

            // 3. Update Suffix Q2 (Merge with new i+R-1)
            long long w_new = sum[i-1];
            int start_r = -1, end_r = -1;

            if (i + R - 1 <= n) {
                start_r = i + R - 1;
                end_r = i + R - 1;
            }

            // 如果 q2 里最后一段的最优左端点 S[l-1] >= S[i-1]，那他的最优左端点就应该更新为 i
            // 这时候最后一段的最优左端点变成与 i+R-1 的最优左端点一样，所以合并成一段
            while (!q2.empty() && q2.back().w >= w_new) {
                if (start_r == -1) {
                    start_r = q2.back().r_start;
                    end_r = q2.back().r_end;
                } else {
                    start_r = q2.back().r_start;
                    end_r = max(end_r, q2.back().r_end);
                }
                q2.pop_back();
            }

            // 现在把待合并的都弹出去了，要把合并好的最后一段加进去
            if (start_r != -1) {
                Segment new_seg;
                new_seg.r_start = start_r;
                new_seg.r_end = end_r;
                new_seg.w = w_new;
                new_seg.max_sum = query_st(start_r, end_r); // 求 max_{r1 <= r <= r2} S[r]，用 ST 表

                // Maintain Q2 Monotonicity (Pop back if smaller than new)
                // 维护 Q2 单调性，一样的道理：如果有一段既在前面、价值又小，那就永远没用了
                while (!q2.empty()) {
                    if (q2.back().val() <= new_seg.val()) q2.pop_back();
                    else break;
                }
                q2.push_back(new_seg);
            }

            // 4. Query
            long long max_val = -4000000000000000000LL;
            if (!q1.empty()) {
                max_val = max(max_val, q1.front().val);
            }
            if (!q2.empty()) {
                max_val = max(max_val, q2.front().val());
            }
            unsigned long long ki = (unsigned long long)max_val;
            final_ans ^= ( (unsigned long long)i * ki );
        }
        cout << final_ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}
