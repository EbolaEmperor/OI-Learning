#include <iostream>
#include <vector>
#include <deque>
#include <list>
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
    long long w;
    long long max_sum;
    long long val() const { return max_sum - w; }
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
        list<Segment> q2;

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
                auto it = q2.begin();
                if (it->r_start == r_move) {
                    // Move to Q1 ONLY if valid (r >= i)
                    if (r_move >= i) {
                        long long val = sum[r_move] - it->w;
                        while (!q1.empty() && q1.back().val <= val) {
                            q1.pop_back();
                        }
                        q1.push_back({r_move, val});
                    }

                    // Update Segment
                    it->r_start++;
                    if (it->r_start > it->r_end) q2.pop_front();
                    else it->max_sum = query_st(it->r_start, it->r_end);

                    // Maintain Q2 Monotonicity after front update
                    // If the front element becomes smaller than the second, it's useless forever.
                    if (!q2.empty()) {
                        auto first = q2.begin();
                        if (q2.size() > 1) {
                            auto second = next(first);
                            if (first->val() <= second->val())
                                q2.pop_front();
                        }
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

                // Maintain Q2 Monotonicity (Pop back if smaller than new)
                while (!q2.empty()) {
                    if (q2.back().val() <= new_seg.val()) q2.pop_back();
                    else break;
                }
                q2.push_back(new_seg);
            }

            // 4. Query
            long long max_val = -4000000000000000000LL;
            bool found = false;
            if (!q1.empty()) {
                max_val = max(max_val, q1.front().val);
                found = true;
            }
            if (!q2.empty()) {
                max_val = max(max_val, q2.front().val());
                found = true;
            }

            if (found) {
                 unsigned long long ki = (unsigned long long)max_val;
                 final_ans ^= ( (unsigned long long)i * ki );
            }
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
