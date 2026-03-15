#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> x(n);
    long long s_min = (long long)4e18;

    for (int i = 0; i < n; ++i) {
        long long xi, yi;
        cin >> xi >> yi;
        x[i] = xi;
        long long s = xi + yi;
        if (s < s_min) s_min = s;
    }

    sort(x.begin(), x.end());
    long long singleCost = 0, ans = m / s_min * 2;
    for (long long k = 0; k < n; ++k) {
        singleCost += x[k];
        if (singleCost > m) break;
        long long rem = m - singleCost;
        ans = max(ans, (k + 1) + rem / s_min * 2);
    }
    cout << ans << endl;

    return 0;
}