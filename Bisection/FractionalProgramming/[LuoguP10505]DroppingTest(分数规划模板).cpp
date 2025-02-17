#include <bits/stdc++.h>
using namespace std;

double fracProg(int *a, int *b, int n, int k){
    double *c = new double[n];
    auto check = [&](double mid){
        for(int i = 0; i < n; ++i)
            c[i] = a[i] - mid * b[i];
        sort(c, c + n);
        double sum = 0;
        for(int i = n - k; i < n; ++i)
            sum += c[i];
        return sum >= 0;
    };

    double l = 0, r = 1, mid;
    while(r - l > 1e-4){
        mid = (l + r) / 2;
        if(check(mid)) l = mid;
        else r = mid;
    }
    delete[] c;
    return mid;
}

int main(){
    int n, k;
    const int N = 1010;
    static int a[N], b[N];
    while(1){
        scanf("%d%d", &n, &k);
        if(!n) break;
        for(int i = 0; i < n; ++i) scanf("%d", a+i);
        for(int i = 0; i < n; ++i) scanf("%d", b+i);
        printf("%.0lf\n", round(100 * fracProg(a, b, n, n-k)));
    }
    return 0;
}