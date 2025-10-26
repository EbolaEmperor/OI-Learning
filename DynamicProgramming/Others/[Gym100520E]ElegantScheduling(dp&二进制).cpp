#include <bits/stdc++.h>
#define lowbit(x) ((x) & (-(x)))
using namespace std;

const int N = 4096;
int n, f[N][N], pre[N][N];
long long A, B, C, M;

int getmat(int i, int j) {
    return (A * i + B * j + C * (i ^ j)) % M;
}

void output(int n, int i) {
    if(n) output(n-1, pre[n][i]);
    cout << i << ' ';
}

int main() {
    freopen("elegant.in", "r", stdin);
    freopen("elegant.out", "w", stdout);
    while(true) {
        cin >> n;
        if (n == 0) break;
        cin >> A >> B >> C >> M;
        for (int i = 1; i < n; i++) 
            memset(f[i], 0x3f, sizeof(int) * n);
        for (int i = 1; i < n; i++) {
            int x = lowbit(i);
            for (int j = 0; j < n; j++)
                for (int k = 0; k < x; k++) {
                    int val = f[i-1][j] + getmat(j, j^x^k);
                    if (val < f[i][j^x^k]) {
                        f[i][j^x^k] = val;
                        pre[i][j^x^k] = j;
                    }
                }
        }
        int best = 0;
        for (int i = 1; i < n; i++)
            if (f[n-1][i] < f[n-1][best])
                best = i;
        cout << f[n-1][best] << '\n';
        output(n-1, best);
        cout << "\n";
    }
    return 0;
}
