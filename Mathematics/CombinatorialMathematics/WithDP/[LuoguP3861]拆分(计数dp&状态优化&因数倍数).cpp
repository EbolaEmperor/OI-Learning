#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

typedef long long LL;
const int mod = 998244353;

void fuck() {
    LL n;
    cin >> n;

    vector<LL> d;
    for(LL i = 1; i * i <= n; i++) {
        if(n % i == 0) {
            d.push_back(i);
            if(n / i != i) d.push_back(n / i);
        }
    }
    sort(d.begin(), d.end());

    int m = d.size();
    vector<vector<int>> dp(m, vector<int>(m, 0));
    // dp[i][j]: 当前乘积为 d[i]，使用的因子不超过 d[j] 的方案数
    dp[0][0] = 1;
    for(int i = 0; i < m; i++) {
        int k = i + 1;
        for(int j = 1; j < m; j++) {
            (dp[i][j] += dp[i][j - 1]) %= mod;
            if(d[i] * d[j] <= n) {
                // 这里要找到 k 使得 d[i] * d[j] = d[k]，可以用 unordered_map，但我们选择直接双指针
                while(k < m && d[k] < d[i] * d[j]) k++;
                if(k < m && d[i] * d[j] == d[k])
                    (dp[k][j] += dp[i][j - 1]) %= mod;
            }
        }
    }
    cout << (dp[m - 1][m - 1] + mod - 1) % mod << "\n";
}

int main() {
    int T;
    cin >> T;
    while (T--) fuck();
    return 0;
}