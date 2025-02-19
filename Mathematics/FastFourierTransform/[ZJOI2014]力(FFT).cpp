#include "PolynomialFL.h"

int main(){
    int n;
    scanf("%d", &n);
    Polynomial q(n), g(n);
    for(int i = 1; i <= n; i++){
        scanf("%lf", &q[i]);
        g[i] = 1.0 / i / i;
    }
    auto ans1 = q * g;
    auto ans2 = q.reverse() * g;
    for(int i = 1; i <= n; i++)
        printf("%.4lf\n", ans1[i] - ans2[n - i]);
    return 0;
}