#include "Polynomial.h"

int main(){
    int n;
    scanf("%d", &n); n--;
    Polynomial a(n);
    for(int i = 0; i <= n; i++) scanf("%d", &a[i]);
    // 乘法：c = a * b;
    // 求逆：c = inv(a);
    // 对数：c = log(a);
    // 指数：c = exp(a);
    // 开根：c = sqrt(a);
    // 快速幂：c = pow(a, k);
    // 三角函数：c = sin(a); c = cos(a); c = tan(a);
    // 反三角函数：c = asin(a); c = acos(a); c = atan(a);
    auto c = sqrt(a);
    for(int i = 0; i <= n; i++)
        printf("%d ", c[i]); puts("");
    return 0;
}