#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int n, a[N], b[N];
long long s[N], w[N];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[n + i] = a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        b[n + i] = b[i];
    }
    for (int i = 1; i <= 2 * n; i++) {
        s[i] = s[i - 1] + b[i];
        w[i] = a[i] - s[i - 1];
    }

    // 用单调队列对每个 i，计算 s[i-n] + max_{i-n < j <= i} w[j]
    deque<int> dq;
    long long ans = LLONG_MAX;
    for (int i = 1; i <= 2 * n; i++) {
        while (!dq.empty() && w[dq.back()] <= w[i]) {
            dq.pop_back();
        }
        dq.push_back(i);
        if (i - dq.front() >= n) {
            dq.pop_front();
        }
        if (i >= n) {
            ans = min(ans, w[dq.front()] + s[i - n]);
        }
    }
    cout << ans << "\n";
    return 0;
}