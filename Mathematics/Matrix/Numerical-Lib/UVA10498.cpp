#include "linprog.h"
using namespace std;

int main() {
    int n, m;
    while (cin >> n >> m) {
        ColVector c(n), b(m);
        Matrix A(m, n);
        for (int i = 0; i < n; ++i) {
            cin >> c(i);
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> A(i, j);
            }
            cin >> b(i);
        }
        ColVector x = linprog(c, A, b);
        long long ans = ceil(dot(x, c) * m);
        printf("Nasa can spend %lld taka.\n", ans);
    }
    return 0;
}