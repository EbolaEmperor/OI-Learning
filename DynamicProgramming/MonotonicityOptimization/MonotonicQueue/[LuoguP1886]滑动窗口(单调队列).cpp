#include <bits/stdc++.h>
using namespace std;

const int N = 1000010;
int a[N], n, k, qmax[N], qmin[N];
deque<int> dq;

int main(){
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i) scanf("%d", a+i);
    // 求 max
    for(int i = 1; i <= k; ++i){
        while(!dq.empty() && a[dq.back()] < a[i]) dq.pop_back();
        dq.push_back(i);
    }
    qmax[k] = dq.front();
    for(int i = k+1; i <= n; ++i){
        while(!dq.empty() && a[dq.back()] < a[i]) dq.pop_back();
        dq.push_back(i);
        if(!dq.empty() && dq.front() <= i-k) dq.pop_front();
        qmax[i] = dq.front();
    }
    // 求 min
    while(!dq.empty()) dq.pop_back();
    for(int i = 1; i <= k; ++i){
        while(!dq.empty() && a[dq.back()] > a[i]) dq.pop_back();
        dq.push_back(i);
    }
    qmin[k] = dq.front();
    for(int i = k+1; i <= n; ++i){
        while(!dq.empty() && a[dq.back()] > a[i]) dq.pop_back();
        dq.push_back(i);
        if(!dq.empty() && dq.front() <= i-k) dq.pop_front();
        qmin[i] = dq.front();
    }
    for(int i = k; i <= n; ++i) printf("%d ", a[qmin[i]]);puts("");
    for(int i = k; i <= n; ++i) printf("%d ", a[qmax[i]]);
    return 0;
}