// 和 [JOI Open 2021] Crossing 里的运算是一样的
#include <bits/stdc++.h>
using namespace std;

int lucas(int n, int m){
    static const int C[3][3] = {
        1, 0, 0,
        1, 1, 0,
        1, 2, 1
    };
    if(n < m) return 0;
    if(m == 0) return 1;
    return lucas(n / 3, m / 3) * C[n % 3][m % 3] % 3;
}

int main(){
    int n, ans = 0; string s;
    cin >> n >> s; --n;
    for(int i = 0; i <= n; i++){
        int coef = lucas(n, i);
        int a = int(s[i] == 'W') + 2 * int(s[i] == 'B');
        if(n & 1) coef = (3 - coef) % 3;
        ans = (ans + coef * a) % 3;
    }
    putchar("RWB"[ans]);
    return 0;
}