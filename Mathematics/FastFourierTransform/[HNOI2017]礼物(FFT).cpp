#include "PolynomialFL.h"

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    Polynomial a(n), b(2 * n);
    long long ans0 = 0, k = 0;
    for(int i = 1; i <= n; i++){
        scanf("%lf", &a[i]);
        ans0 += a[i] * a[i];
        k += 2 * a[i];
    }
    for(int i = 1; i <= n; i++){
        scanf("%lf", &b[i]);
        b[i + n] = b[i];
        ans0 += b[i] * b[i];
        k -= 2 * b[i];
    }
    long long mid = floor(-k / 2.0 / n);
    ans0 += min(mid * mid * n + k * mid, 
                (mid + 1) * (mid + 1) * n + k * (mid + 1));
    auto c = a.reverse() * b;
    long long ans = 0;
    for(int i = 1; i <= n; i++)
        ans = max(ans, (long long) round(c[i + n]));
    cout << ans0 - 2 * ans << endl;
    return 0;
}