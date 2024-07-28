#include <bits/stdc++.h>
using namespace std;

const int N = 1010;
int n, T, K, f[N], h[N], v[N];

int main(){
    cin >> n >> T >> K;
    for(int i = 1; i <= n; ++i)
        cin >> v[i] >> h[i];
    // 情况1：全部是小蛋糕
    for(int i = 1; i <= n; ++i)
        for(int j = h[i]; j <= T; ++j)
            f[j] = max(f[j], f[j - h[i]] + v[i]);
    int ans = f[T];
    // 情况2：存在大蛋糕，则必然大蛋糕放最顶上
    memset(f, 0, sizeof(f));
    for(int i = 1; i <= n; ++i)
        for(int j = h[i]/5*4; j <= T; ++j)
            f[j] = max(f[j], f[j - h[i]/5*4] + v[i]);
    // 枚举把哪个大蛋糕放最顶上
    for(int i = 1; i <= n; ++i)
        if(h[i] >= K && h[i] <= T)
            ans = max(ans, f[T - h[i]] + v[i]);
    cout << ans << endl;
    return 0;
}