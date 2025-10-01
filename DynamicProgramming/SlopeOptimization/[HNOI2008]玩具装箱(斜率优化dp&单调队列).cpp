#include <bits/stdc++.h>
using namespace std;

const int N = 50010;
long long dp[N], f[N], g[N], sum[N], C[N], n, L;

double slope(int j1, int j2) {
    return 1.0 * (g[j2] - g[j1]) / (f[j2] - f[j1]);
}

int main() {
    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> C[i];
        sum[i] = sum[i - 1] + C[i];
        f[i] = sum[i] + i;
    }

    deque<int> q;
    q.push_back(0);
    f[0] = dp[0] = 0;
    g[0] = (L + 1) * (L + 1);

    for (int i = 1; i <= n; i++) {
        while (q.size() > 1 && slope(q[0], q[1]) <= 2 * f[i])  q.pop_front();
        int j = q.front();
        dp[i] = dp[j] + (f[i] - f[j] - L - 1) * (f[i] - f[j] - L - 1);
        g[i] = (f[i] + L + 1) * (f[i] + L + 1) + dp[i];
        while (q.size() > 1 && slope(q[q.size() - 2], q[q.size() - 1]) >= slope(q[q.size() - 1], i)) q.pop_back();
        q.push_back(i);
    }

    cout << dp[n] << endl;
    return 0;
}