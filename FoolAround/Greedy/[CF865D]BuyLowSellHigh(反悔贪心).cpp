#include <bits/stdc++.h>
using namespace std;

priority_queue<int> pq;

int main(){
    int n, x;
    long long ans = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i){
        scanf("%d", &x);
        if(!pq.empty() && -pq.top() < x) // 只要之前有更低价，就在之前买入，现在卖出
            ans += x + pq.top(), pq.pop(), pq.push(-x); // 加入 x，允许之后撤销本次交易，实际上就是买回卖掉的股票
        pq.push(-x); // 提供在此处买入的选择
    }
    cout << ans << endl;
    return 0;
}