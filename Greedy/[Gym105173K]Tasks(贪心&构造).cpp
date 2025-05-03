#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;

const int N = 100010;
int n, l[N], b[N], r[N];
vector<pii> layer[N];

void fuck(int type = 0){
    cout << "-1" << endl;
    if(type) cerr << "fuck type: " << type << endl;
    exit(0);
}

int main(){
    cin >> n;
    for (int i = 1; i <= n; i++){
        cin >> l[i] >> b[i];
        b[i]++;
        layer[b[i]].emplace_back(l[i], i);
    }
    layer[0].emplace_back(0, 0);
    r[0] = 1e6 + 1;

    for(int i = 1; i <= n + 1; i++){
        if(layer[i].empty()) continue;
        if(i && layer[i - 1].empty()) fuck(1);

        sort(layer[i].begin(), layer[i].end());
        int m = layer[i].size();
        for(int j = 0; j < m - 1; j++)
            if(layer[i][j].first == layer[i][j + 1].first) fuck(2);

        int j_down = layer[i - 1].size() - 1, cr = 1e6;
        for(int j = m - 1; j >= 0; j--){
            int id = layer[i][j].second;
            while(j_down >= 0 && layer[i - 1][j_down].first > layer[i][j].first) j_down--;
            if(j_down < 0) fuck(3);
            cr = min(cr, r[layer[i - 1][j_down].second] - (l[id] == layer[i - 1][j_down].first));
            if(cr < l[id]) fuck(4);
            r[id] = cr--;
        }
    }

    for(int i = 1; i <= n; i++)
        cout << r[i] << "\n";
    return 0;
}
