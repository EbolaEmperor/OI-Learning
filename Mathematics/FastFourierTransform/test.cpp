#include "Polynomial.h"

int main(){
    int n;
    scanf("%d", &n); n--;
    Polynomial a(n);
    for(int i = 0; i <= n; i++) scanf("%d", &a[i]);
    auto c = log(a);
    for(int i = 0; i <= n; i++)
        printf("%d ", c[i]); puts("");

    return 0;
}