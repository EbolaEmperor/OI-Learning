#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int jump[N][18], diam[N], volsum[N], n, q;

void getfa(){
    diam[n + 1] = 2e9;
    volsum[n + 1] = 1e9;
    stack<int> stk;
    stk.push(n + 1);
    for(int i = n; i >= 1; --i){
        while(!stk.empty() && diam[i] >= diam[stk.top()]) stk.pop();
        jump[i][0] = stk.top();
        volsum[i] += volsum[stk.top()];
        stk.push(i);
    }
    jump[n + 1][0] = n + 1;
}

void multiple(){
    for(int k = 0; k <= 15; ++k)
        for(int i = n + 1; i >= 1; --i)
            jump[i][k + 1] = jump[jump[i][k]][k];
}

int query(int x, int v){
    for(int k = 16; k >= 0; --k){
        if(v > volsum[x] - volsum[jump[x][k]]){
            v -= volsum[x] - volsum[jump[x][k]];
            x = jump[x][k];
        }
    }
    return x <= n ? x : 0;
}

int main(){
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i)
        scanf("%d%d", diam + i, volsum + i);
    getfa();
    multiple();
    while(q--){
        int pos, vol;
        scanf("%d%d", &pos, &vol);
        printf("%d\n", query(pos, vol));
    }
    return 0;
}