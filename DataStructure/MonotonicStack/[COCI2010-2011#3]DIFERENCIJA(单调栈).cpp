#include <bits/stdc++.h>
using namespace std;

typedef bool (*CMP)(int, int);
const int N = 300010;
int n, a[N], f[N], g[N];

long long solve(CMP cmp){
    stack<int> stk;
    for(int k = 1; k <= n; ++k){
        while(!stk.empty() && cmp(a[k], a[stk.top()])) stk.pop();
        f[k] = stk.empty() ? 0 : stk.top();
        stk.push(k);
    }
    while(!stk.empty()) stk.pop();
    for(int k = n; k >= 1; --k){
        while(!stk.empty() && (cmp(a[k], a[stk.top()]) || a[k]==a[stk.top()]) ) stk.pop();
        g[k] = stk.empty() ? n+1 : stk.top();
        stk.push(k);
    }
    long long ans = 0;
    for(int k = 1; k <= n; ++k)
        ans += (long long) a[k] * (g[k] - k) * (k - f[k]);
    return ans;
}

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", a+i);
    long long ans = solve([](int x, int y){return x > y;});
    ans -= solve([](int x, int y){return x < y;});
    cout << ans << endl;
    return 0;
}