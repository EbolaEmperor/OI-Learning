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
    multiset< pair<int, int> > nodes;
    nodes.insert(make_pair(0, 0));
    int dele = k;
    long long sum = 0, ans = INT64_MAX;
    while(1){
        auto pr = *nodes.begin();
        nodes.erase(nodes.begin());
        sum -= pr.first;
        for(int i = 0; i < dele; ++i){
            nodes.insert(make_pair(pr.first + w[i], i));
            sum += pr.first + w[i];
        }
        while(nodes.size() > n){
            auto it = nodes.end(); --it;
            sum -= it->first;
            dele = min(dele, it->second);
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
    printf("%lld\n", work());
    return 0;
}