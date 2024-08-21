#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
int maxn[N << 2], minn[N << 2], col[N], n;

void build(int o, int l, int r){
    if(l == r){
        maxn[o] = minn[o] = col[l];
        return;
    }
    int mid = (l + r) / 2;
    build(o<<1, l, mid);
    build(o<<1|1, mid+1, r);
    maxn[o] = max(maxn[o<<1], maxn[o<<1|1]);
    minn[o] = min(minn[o<<1], minn[o<<1|1]);
}

int qmax(int o, int l, int r, int nl, int nr){
    if(l >= nl && r <= nr) return maxn[o];
    int mid = (l + r) / 2, ans = 0;
    if(nl <= mid) ans = max(ans, qmax(o<<1, l, mid, nl, nr));
    if(nr > mid) ans = max(ans, qmax(o<<1|1, mid+1, r, nl, nr));
    return ans;
}

int qmin(int o, int l, int r, int nl, int nr){
    if(l >= nl && r <= nr) return minn[o];
    int mid = (l + r) / 2, ans = n+1;
    if(nl <= mid) ans = min(ans, qmin(o<<1, l, mid, nl, nr));
    if(nr > mid) ans = min(ans, qmin(o<<1|1, mid+1, r, nl, nr));
    return ans;
}

void update(int o, int l, int r, int k){
    if(l == r){
        maxn[o] = 0;
        minn[o] = n+1;
        return;
    }
    int mid = (l + r) / 2;
    if(k <= mid) update(o<<1, l, mid, k);
    else update(o<<1|1, mid+1, r, k);
    maxn[o] = max(maxn[o<<1], maxn[o<<1|1]);
    minn[o] = min(minn[o<<1], minn[o<<1|1]);
}

int cnt;
int last[N];
vector<int> ccc[N];
set<pair<int,int>> s;
// first: 消失位置   second: 颜色

void work(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++){
        scanf("%d", &col[i]);
        if(!last[col[i]]) ++cnt;
        last[col[i]] = i;
        ccc[col[i]].push_back(i);
    }
    build(1, 1, n);
    for(int c = 1; c <= n; c++)
        if(last[c]) s.insert(make_pair(last[c], c));
    int pos = 1;
    vector<int> ans;
    ans.push_back(0);
    while(pos <= cnt){
        auto it = s.begin();
        int c = (pos & 1) ? 
                qmax(1, 1, n, ans.back()+1, it->first) :
                qmin(1, 1, n, ans.back()+1, it->first) ;
        int i = lower_bound(ccc[c].begin(), ccc[c].end(), ans.back()+1) - ccc[c].begin();
        ans.push_back(ccc[c][i]);
        for(int x : ccc[c])
            update(1, 1, n, x);
        auto jt = s.find(make_pair(last[c], c));
        s.erase(jt);
        pos++;
    }
    printf("%d\n", cnt);
    for(int x : ans)
        if(x) printf("%d ", col[x]);
    puts("");
    for(int i = 1; i <= n; i++) ccc[i].clear();
    s.clear();
    memset(last, 0, sizeof(int) * (n+3));
    cnt = 0;
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--) work();
    return 0;
}
