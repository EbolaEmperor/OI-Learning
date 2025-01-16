#include <bits/stdc++.h>
using namespace std;

const int N = 1100000;
int S;
int n, q, L[N], R[N], belong[N], tot=0;
int v[N], sortedv[N], lazy[N];

int ngeqC(int l, int r, int c){
    int ans = 0;
    if(belong[l] == belong[r]){
        int B = belong[l];
        for(int i = l; i <= r; ++i)
            if(v[i] + lazy[B] >= c) ++ans;
    } else {
        int B = belong[l];
        for(int i = l; i <= R[B]; ++i)
            if(v[i] + lazy[B] >= c) ++ans;
        B = belong[r];
        for(int i = L[B]; i <= r; ++i)
            if(v[i] + lazy[B] >= c) ++ans;
        for(B = belong[l] + 1; B < belong[r]; ++B){
            int p = lower_bound(sortedv + L[B], sortedv + R[B] + 1, c - lazy[B]) - sortedv;
            if(p <= R[B]) ans += R[B] - p + 1;
        }
    }
    return ans;
}

void add(int l, int r, int x){
    if(belong[l] == belong[r]){
        int B = belong[l];
        for(int i = l; i <= r; ++i) v[i] += x;
        for(int i = L[B]; i <= R[B]; ++i) sortedv[i] = v[i];
        sort(sortedv + L[B], sortedv + R[B] + 1);
    } else {
        int B = belong[l];
        for(int i = l; i <= R[B]; ++i) v[i] += x;
        for(int i = L[B]; i <= R[B]; ++i) sortedv[i] = v[i];
        sort(sortedv + L[B], sortedv + R[B] + 1);
        B = belong[r];
        for(int i = L[B]; i <= r; ++i) v[i] += x;
        for(int i = L[B]; i <= R[B]; ++i) sortedv[i] = v[i];
        sort(sortedv + L[B], sortedv + R[B] + 1);
        for(B = belong[l] + 1; B < belong[r]; ++B) lazy[B] += x;
    }
}

int main(){
    scanf("%d%d", &n, &q);
    S = sqrt(n);
    for(int i = 1; i <= n; ++i) scanf("%d", v+i);
    for(int i = 1; i <= n; i += S){
        L[++tot] = i; R[tot] = min(i+S-1,n);
        for(int j = 0; j < S; ++j)
            belong[i+j] = tot, sortedv[i+j] = v[i+j];
        sort(sortedv + L[tot], sortedv + R[tot] + 1);
    }
    int l, r, w; char op[5];
    while(q--){
        scanf("%s%d%d%d", op, &l, &r, &w);
        if(op[0] == 'M') add(l, r, w);
        else printf("%d\n", ngeqC(l, r, w));
    }
    return 0;
}