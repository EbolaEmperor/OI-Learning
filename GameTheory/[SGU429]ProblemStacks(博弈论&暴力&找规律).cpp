#include <bits/stdc++.h>
using namespace std;

unordered_map<string, bool> memo;

string encode(const vector<int>& a){
    ostringstream oss;
    for (auto x : a) oss << x << "#";
    return oss.str();
}

bool canWin(vector<int> &a){
    if(a.empty()) return false;
    if(a.size() == 1) return true;
    else if(a.size() == 2) return a[0] != a[1];
    else if(a.size() == 3) return a[0] != a[2] || a[0] == a[1];
    // n = 4 的结论有问题，暂时不用了
    // else if(a.size() == 4){
    //     if(a[0] > a[3]){
    //         swap(a[0], a[3]);
    //         swap(a[1], a[2]);
    //     }
    //     if(a[0] == a[3]){
    //         if(a[0] < a[1] && a[0] < a[2]) return false;
    //         if(a[0] == a[1] && a[0] == a[2]) return false;
    //         if(a[0] > a[1] && a[0] > a[2]) return false;
    //         return true;
    //     } else if(a[0] + 1 == a[3]){
    //         return a[1] <= a[0] && a[2] >= a[3];
    //     }
    //     return true;
    // }
    // 如果没有堆了，说明轮到当前玩家时已经无法拿题目 -> 当前玩家输
    string key = encode(a);
    if(memo.count(key)) {
        return memo[key];
    }
    
    int leftCount = a.front();
    for(int x=1; x<=leftCount; x++){
        vector<int> newState = a;
        newState[0] -= x;
        if(newState[0] == 0){
            newState.erase(newState.begin());
        }
        if(!canWin(newState)){
            memo[key] = true;
            return true;
        }
    }

    int rightCount = a.back();
    for(int y=1; y<=rightCount; y++){
        vector<int> newState = a;
        newState.back() -= y;
        if(newState.back() == 0){
            newState.pop_back();
        }
        if(!canWin(newState)){
            memo[key] = true;
            return true;
        }
    }

    return memo[key] = false;
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int& x : a) cin >> x;
    vector<int> vals;
    vals.push_back(0);
    vals.push_back(1);
    vals.push_back(2);
    vals.push_back(3);
    for(int x : a){
        for(int i = x - 2; i <= x + 2; i++){
            if(i > 0) vals.push_back(i);
        }
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    for(int& x : a)
        x = lower_bound(vals.begin(), vals.end(), x) - vals.begin();
    cout << (canWin(a) ? "FEDOR" : "SERGEY") << endl;
    return 0;
}