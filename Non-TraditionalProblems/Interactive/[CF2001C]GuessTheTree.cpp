#include <bits/stdc++.h>
using namespace std;

vector<int> fa;
int find(int x){
    return fa[x]==x ? x : fa[x] = find(fa[x]);
}

void work(int n){
    fa.resize(n);
    iota(fa.begin(), fa.end(), 0);
    vector<pair<int,int>> edges;
    for(int t = 1; t < n; t++){
        int x = 0, y, mid;
        for(y = 1; y < n; y++)
            if(find(x) != find(y)) break;
        while(1){
            cout << "? " << x+1 << " " << y+1 << endl;
            cout.flush();
            cin >> mid; mid--;
            if(mid == x){
                edges.emplace_back(x, y);
                fa[find(y)] = find(x);
                break;
            }
            if(find(mid) == find(x)) x = mid;
            else y = mid;
        }
    }
    cout << "! ";
    for(auto e : edges)
        cout << e.first+1 << " " << e.second+1 << " ";
    cout << endl;
    cout.flush();
}

int main(){
    int T, n;
    cin >> T;
    while(T--){
        cin >> n;
        work(n);
    }
    return 0;
}
