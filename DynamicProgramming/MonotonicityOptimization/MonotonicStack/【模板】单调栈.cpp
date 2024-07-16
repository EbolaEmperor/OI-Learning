#include <bits/stdc++.h>
using namespace std;

void fstMin(int *a, int n, int *f){
    stack<int> stk;
    for(int i = n-1; i >= 0; --i){
        while(!stk.empty() && a[stk.top()] <= a[i]) stk.pop();
        f[i] = stk.empty() ? 0 : stk.top() + 1;
        stk.push(i);
    }
}

int main(){
    const int N = 3000000;
    static int a[N], f[N], n;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", a+i);
    fstMin(a, n, f);
    for(int i = 0; i < n; ++i) printf("%d ", f[i]);
    return 0;
}