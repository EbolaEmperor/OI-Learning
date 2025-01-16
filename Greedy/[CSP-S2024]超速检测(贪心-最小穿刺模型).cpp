#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cmath>
#define eps 1e-9
using namespace std;

class MinPunc{
private:
    vector<pair<int,int>> segments;
public:
    void insert(int l, int r){
        segments.emplace_back(r, l);
    }
    int getMinPunc(vector<int>& punc){
        sort(punc.begin(), punc.end());
        sort(segments.begin(), segments.end());
        int ans = 0, curP = -1;
        for(auto& seg : segments){
            if(curP == -1 || seg.second > punc[curP]){
                while(curP + 1 < punc.size() && punc[curP + 1] <= seg.first) curP++;
                ans++;
            }
        }
        return ans;
    }
    ~MinPunc(){
        vector<pair<int,int>>().swap(segments);
    }
};

const int N = 100010;
int d[N], v[N], a[N];
int sum[N * 10];

void work(){
    int n, m, len, vlim;
    cin >> n >> m >> len >> vlim;
    vector<int> punc(m);
    len++;
    MinPunc minpunc;
    for(int i = 1; i <= n; i++){
        cin >> d[i] >> v[i] >> a[i];
        d[i]++;
    }
    memset(sum, 0, sizeof(sum));
    for(int i = 0; i < m; i++){
        cin >> punc[i];
        punc[i]++;
        sum[punc[i]]++;
    }
    for(int i = 1; i < len; i++)
        sum[i + 1] += sum[i];
    int ans1 = 0;
    static bool fuck[N];
    for(int i = 1; i <= n; i++){
        if(a[i] > 0){
            int x = d[i];
            if(v[i] <= vlim){
                double t = (double) (vlim - v[i]) / a[i];
                double xtmp = v[i] * t + 0.5 * a[i] * t * t + d[i];
                x = ceil(xtmp + eps);
            }
            if(x > len) continue;
            if(sum[len] - sum[x - 1])
                ans1++, minpunc.insert(x, len), fuck[i] = 1;
        } else if(a[i] < 0){
            if(v[i] <= vlim) continue;
            double t = (double) (vlim - v[i]) / a[i];
            double xtmp = v[i] * t + 0.5 * a[i] * t * t + d[i];
            int x = min(len, (int)floor(xtmp - eps));
            if(sum[x] - sum[d[i] - 1])
                ans1++, minpunc.insert(d[i], x);
        } else if(v[i] > vlim && sum[len] - sum[d[i] - 1]){
            ans1++;
            minpunc.insert(d[i], len);
        }
    }
    cout << ans1 << " " << m - minpunc.getMinPunc(punc) << endl;
}

int main(){
    int T;
    cin >> T;
    while(T--) work();
    return 0;
}