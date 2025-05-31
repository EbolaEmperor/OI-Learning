#include <bits/stdc++.h>
using namespace std;

const int N = 40010;
int n, k, rk[N], sa[N], s[N], oldrk[N], height[N];

// 本题因为字符集达到了 1e6，所以写计数排序不如写两个 log 的朴素 sort
void getSA() {
    for (int i = 1; i <= n; ++i) sa[i] = i, rk[i] = s[i];
    for (int w = 1; w < n; w <<= 1) {
        sort(sa + 1, sa + n + 1, [&](int x, int y) {
            return rk[x] == rk[y] ? rk[x + w] < rk[y + w] : rk[x] < rk[y];
        });
        memcpy(oldrk, rk, sizeof(rk));
        for (int p = 0, i = 1; i <= n; ++i) {
            if (oldrk[sa[i]] == oldrk[sa[i - 1]] &&
                oldrk[sa[i] + w] == oldrk[sa[i - 1] + w]) {
                rk[sa[i]] = p;
            } else {
                rk[sa[i]] = ++p;
            }
        }
    }
    for (int i = 1, k = 0; i <= n; ++i) {
        if (rk[i] == 0) continue;
        if (k) --k;
        while (s[i + k] == s[sa[rk[i] - 1] + k]) ++k;
        height[rk[i]] = k;
    }
}

int main() {
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> s[i];
    getSA();

    deque<int> dq;
    int ans = 0; --k;
    for (int i = 1; i <= n; ++i) {
        while (!dq.empty() && dq.front() < i - k + 1) dq.pop_front();
        while (!dq.empty() && height[dq.back()] >= height[i]) dq.pop_back();
        dq.push_back(i);
        if (i >= k) {
            ans = max(ans, height[dq.front()]);
        }
    }
    cout << ans << endl;
    return 0;
}