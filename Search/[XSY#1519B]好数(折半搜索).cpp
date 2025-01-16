#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
LL R;

class Solver{
public:
    vector<int> p;
    vector<LL> num;
    void dfs(LL now, int pos){
        num.push_back(now);
        for(int i = pos; i < p.size(); ++i){
            if(now > R / p[i]) break;
            dfs(now * p[i], i);
        }
    }
} solver1, solver2;
#define num1 solver1.num
#define num2 solver2.num

int main(){
    int n;
    cin >> n >> R;
    vector<int> p(n);
    for(int i = 0; i < n; ++i) cin >> p[i];
    sort(p.begin(), p.end());
    for(int i = 0; i < n / 2; i++){
        solver1.p.push_back(p[2 * i]);
        solver2.p.push_back(p[2 * i + 1]);
    }
    if(n & 1) solver2.p.push_back(p[n - 1]);
    solver1.dfs(1, 0);
    solver2.dfs(1, 0);
    sort(num1.begin(), num1.end());
    sort(num2.begin(), num2.end());
    int cur = num2.size() - 1;
    LL cnt = 0, maxn = 0;
    for(LL x : num1){
        while(x > R / num2[cur]) --cur;
        cnt += cur + 1;
        maxn = max(maxn, x * num2[cur]);
    }
    cout << cnt << " " << maxn << endl;
    return 0;
}