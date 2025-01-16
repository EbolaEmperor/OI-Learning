#include <bits/stdc++.h>
using namespace std;

const int N = 10010;
vector<int> tag[N << 2];
bitset<N> val[N << 2], ans;

void dfs(int o, int l, int r){
    val[o][0] = 1;
    for(int x : tag[o])
        val[o] |= val[o] << x;
    if(l == r){
        ans |= val[o];
        return;
    }
    int mid = (l + r) / 2;
    val[o << 1] = val[o << 1 | 1] = val[o];
    dfs(o << 1, l, mid);
    dfs(o << 1 | 1, mid + 1, r);
}

void insert(int o, int l, int r, int nl, int nr, int x){
    if(l >= nl && r <= nr){
        tag[o].push_back(x);
        return;
    }
    int mid = (l + r) / 2;
    if(nl <= mid) insert(o << 1, l, mid, nl, nr, x);
    if(nr > mid) insert(o << 1 | 1, mid + 1, r, nl, nr, x);
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    while(q--){
        int l, r, x;
        scanf("%d%d%d", &l, &r, &x);
        insert(1, 1, n, l, r, x);
    }
    dfs(1, 1, n);
    vector<int> ks;
    for(int i = 1; i <= n; i++)
        if(ans[i]) ks.push_back(i);
    printf("%zu\n", ks.size());
    for(int x : ks)
        printf("%d ", x);
    printf("\n");
    return 0;
}