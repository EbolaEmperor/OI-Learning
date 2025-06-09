#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long LLL;

LLL ExGcd(LLL a, LLL b, LLL &x, LLL &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    LLL g = ExGcd(b, a % b, x, y);
    LLL t = x; x = y;
    y = t - (a / b) * y;
    return g;
}

LLL minSol(LLL a, LLL b, LLL c) {
    LLL x, y;
    LLL g = ExGcd(a, b, x, y);
    if (c % g != 0) return -1;
    a /= g; b /= g; c /= g;
    if(b < 0) b = -b;
    return (x * c % b + b) % b;
}

int main(){
    int n;
    cin >> n;
    vector<int> C(n), P(n), L(n);

    int m = 0;
    for(int i = 0; i < n; i++) {
        cin >> C[i] >> P[i] >> L[i];
        m = max(m, C[i]);
    }

    auto check = [&](int m) {
        for(int i = 0; i < n; i++)
            for(int j = i + 1; j < n; j++) {
                LLL a = P[i] - P[j];
                LLL c = C[j] - C[i];
                LLL x = minSol(a, m, c);
                if (x != -1 && x <= min(L[i], L[j]))
                    return false;
            }
        return true;
    };

    while(!check(m)) ++m;
    cout << m << endl;
    return 0;
}
