#include <bits/stdc++.h>
using namespace std;

const int N = 300010;
struct Node{
    int L, R, val;
    bool del;
} node[N];
typedef pair<int,int> pii;
priority_queue<pii> pq;

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &node[i].val);
        node[i].L = i - 1;
        node[i].R = i + 1;
        node[i].del = 0;
        pq.push(make_pair(node[i].val, i));
    }
    long long ans = 0;
    for(int c = 1; c <= k; ++c){
        while(!pq.empty() && node[pq.top().second].del) pq.pop();
        if(pq.empty()) break;
        int i = pq.top().second; pq.pop();
        if(node[i].val <= 0) break;
        ans += node[i].val;
        node[i].val = node[node[i].L].val + node[node[i].R].val - node[i].val;
        pq.push(make_pair(node[i].val, i));
        if(node[i].L > 0){
            node[node[i].L].del = 1;
            if(node[node[i].L].L > 0){
                node[node[node[i].L].L].R = i;
                node[i].L = node[node[i].L].L;
            }
        }
        if(node[i].R <= n){
            node[node[i].R].del = 1;
            if(node[node[i].R].R <= n){
                node[node[node[i].R].R].L = i;
                node[i].R = node[node[i].R].R;
            }
        }
    }
    cout << ans << endl;
    return 0;
}