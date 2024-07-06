#include <bits/stdc++.h>
using namespace std;

const int S = 1 << 16;
int n, initS;
double f[S];

int main(){
    cin >> n;
    for(int i = 0, x; i < n; ++i)
        cin >> x, initS |= 1 << x;
    for(int s = 1; s < S; ++s){
        f[s] = 1e18;
        for(int x = 0; x <= 15; ++x){
            double coef = 1., rhs = 1.;
            if(x && (s>>x-1&1)) rhs += f[s^(1<<x-1)] / 3.;
            else coef -= 1. / 3;
            if(s>>x&1) rhs += f[s^(1<<x)] / 3.;
            else coef -= 1. / 3;
            if(x<15 && (s>>x+1&1)) rhs += f[s^(1<<x+1)] / 3.;
            else coef -= 1. / 3.;
            if(coef > 1e-12) f[s] = min(f[s], rhs / coef);
        }
    }
    cout << setprecision(10) << f[initS] << endl;
    return 0;
}