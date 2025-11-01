#include <bits/stdc++.h>
using namespace std;

const int S = 20;
const int N = 1 << S;
int f[N], n, k;

int main() {
    scanf("%d%d", &n, &k);
    int xsum = 0, dp = 0;
    memset(f, -0x3f, sizeof(f));
    f[0] = 0;
    for (int i = 0, x; i < n; i++) {
        scanf("%d", &x);
        xsum ^= x;
        dp = max(dp, f[xsum ^ k] + 1);
        f[xsum] = max(f[xsum], dp);
    }
    printf("%d\n", dp);
    return 0;
}
