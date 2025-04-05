#include <bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N = 2010;
int n, k, f[N][N];

int Pow(int a, int b) {
    int ans = 1;
    for (; b; b >>= 1, a = 1ll * a * a % ha)
        if (b & 1) ans = 1ll * ans * a % ha;
    return ans;
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) f[1][i] = 1;
    for (int i = 1; i < k; i++) {
        f[i + 1][n - i + 1] = f[i][n - i + 1];
        int sum = 0;
        for (int j = n - i; j >= 1; j--){
            sum = (sum + f[i][j]) % ha;
            f[i + 1][j] = sum;
        }
    }
    int ans = f[k][1];
    if (n > k) ans = 1ll * ans * Pow(2, n - 1 - k) % ha;
    cout << ans << endl;
    return 0;
}