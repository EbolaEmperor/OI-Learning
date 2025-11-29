// 对每个 i，求有多少个区间 [i,j] 满足 a[i] 是区间最小值、a[j] 是区间最大值
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    vector<int> cnt(n, 0);
    vector<int> cnt_real(n, 0);
    stack<int> stk1;
    vector<int> stk2;
    long long ans = 0;
    stk1.push(n);
    for(int i = n - 1; i >= 0; i--){
        cnt[i] = 1;
        while(stk1.size() > 1 && a[stk1.top()] >= a[i]){
            stk1.pop();
        }
        while(!stk2.empty() && a[stk2.back()] < a[i]){
            stk2.pop_back();
        }
        int p = lower_bound(stk2.rbegin(), stk2.rend(), stk1.top()) - stk2.rbegin();
        stk1.push(i);
        stk2.push_back(i);
        cnt[i] = p + 1;
        ans += cnt[i];
    }
    cout << ans << endl;
    return 0;
}