#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N = 20000000;
LL g[N+10], n;

int main(){
    cin >> n;
    g[1] = 1; g[2] = 3;
    int idx = 2;
    for(int i = 3; i <= N; i++){
        g[i] = g[i-1] + idx;
        if(i == g[idx]) idx++;
        if(g[i]>=n){
            cout << i << endl;
            return 0;
        }
    }
    LL cur = N, now = g[N];
    while(cur != g[idx]) cur++, now += idx;
    idx++;
    while(now < n){
        cur += g[idx] - g[idx-1];
        now += (g[idx] - g[idx-1]) * idx;
        idx++;
    }
    if(now > n){
        idx--;
        now -= (g[idx] - g[idx-1]) * idx;
        cur -= g[idx] - g[idx-1];
        while(now < n){
            cur++, now += idx;
            if(cur == g[idx]) idx++;
        }
    }
    cout << cur << endl;
    return 0;
}