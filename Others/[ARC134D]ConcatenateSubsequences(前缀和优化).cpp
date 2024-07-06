#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int n, a[N<<1], sufmin[N], sufminpos[N];
vector<int> ans1, ans2;

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= 2*n; ++i) scanf("%d", a+i);
    sufmin[n] = a[n]; sufminpos[n] = n;
    for(int i = n - 1; i >= 1; --i){
        sufmin[i] = min(sufmin[i+1], a[i]);
        sufminpos[i] = (a[i] == sufmin[i]) ? i : sufminpos[i+1];
    }
    int allmin = sufmin[1], bmin = 2e9, pos;
    for(int i = 1; i <= n; ++i)
        if(a[i] == allmin){
            pos = i + 1;
            ans1.push_back(a[i]);
            ans2.push_back(a[i+n]);
            bmin = min(bmin, a[i+n]);
        }
    if(bmin < allmin)
        return printf("%d %d\n", allmin, bmin), 0;
    int nextv = -1;
    for(int i = 1; i < ans2.size(); ++i)
        if(ans2[i] != ans2[0]) {nextv = ans2[i]; break;}
    while(pos <= n){
        int i = sufminpos[pos], v = sufmin[pos];
        if(v > ans2[0] || v == ans2[0] && nextv < ans2[0]) break;
        ans1.push_back(v);
        ans2.push_back(a[i+n]);
        pos = i + 1;
    }
    for(int x : ans1) printf("%d ", x);
    for(int x : ans2) printf("%d ", x);
    return 0;
}