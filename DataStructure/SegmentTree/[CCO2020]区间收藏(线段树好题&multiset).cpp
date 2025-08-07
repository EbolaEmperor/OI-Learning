#include <bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;

const int N = 1e6 + 5;
multiset<int> allL, allR;
multiset<int> fixL[N], fixR[N];
int ans[N<<2], maxl[N<<2], minr[N<<2];

void pushup(int o) {
    maxl[o] = max(maxl[o<<1], maxl[o<<1|1]);
    minr[o] = min(minr[o<<1], minr[o<<1|1]);
    ans[o] = min(ans[o<<1], ans[o<<1|1]);
    ans[o] = min(ans[o], minr[o<<1|1] - maxl[o<<1]);
}

void update(int o, int l, int r, int k) {
    if (l == r) {
        maxl[o] = fixR[l].empty() ? -inf : *fixR[l].rbegin();
        minr[o] = fixL[l].empty() ? inf : *fixL[l].begin();
        ans[o] = minr[o] - maxl[o];
        return;
    }
    int mid = (l + r) / 2;
    if (k <= mid) update(o<<1, l, mid, k);
    else update(o<<1|1, mid+1, r, k);
    pushup(o);
}

int main() {
    memset(maxl, -0x3f, sizeof(maxl));
    memset(minr, 0x3f, sizeof(minr));
    memset(ans, 0x3f, sizeof(ans));
    int q, l, r;
    char op[5];
    scanf("%d", &q);
    while(q--) {
        scanf("%s%d%d", op, &l, &r);
        if (op[0] == 'A') {
            allL.insert(l);
            allR.insert(r);
            fixL[l].insert(r);
            fixR[r].insert(l);
        } else {
            allL.erase(allL.find(l));
            allR.erase(allR.find(r));
            fixL[l].erase(fixL[l].find(r));
            fixR[r].erase(fixR[r].find(l));
        }
        update(1, 1, 1e6, l);
        update(1, 1, 1e6, r);

        int L = *allL.rbegin();
        int R = *allR.begin();
        if (L < R) {
            printf("%d\n", *fixL[L].begin() - *fixR[R].rbegin());
        } else {
            printf("%d\n", ans[1]);
        }
    }
    return 0;
}