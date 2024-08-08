// 复杂度 O(n log^2 n)
#include <bits/stdc++.h>
using namespace std;

long long work(){
    int n, k;
    scanf("%d%d", &n, &k);
    vector<int> w(k);
    for(int i = 0; i < k; ++i)
        scanf("%d", &w[i]);
    sort(w.begin(), w.end());
    multiset<long long> nodes;
    nodes.insert(0);
    long long sum = 0, ans = INT64_MAX;
    for(int i = 1; i <= n; i++){
        auto pr = *nodes.begin();
        nodes.erase(nodes.begin());
        sum -= pr;
        for(int j = 1; j <= k && i * j <= 2 * n; ++j){
            nodes.insert(pr + w[j-1]);
            sum += pr + w[j-1];
        }
        while(nodes.size() > n){
            auto it = nodes.end(); --it;
            sum -= *it;
            nodes.erase(it);
        }
        if(nodes.size() == n){
            if(sum < ans) ans = sum;
            else break;
        }
    }
    return ans;
}

int main(){
    cout << work() << endl;
    return 0;
}