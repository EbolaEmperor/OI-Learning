#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 800010;
int n, len, a[N], b[N], L[N], R[N];

// 检查每个新郎只匹配距离 <= d 的新娘是否可行
// 根据 Hall 定理，等价于：任取一些新郎，能与他们匹配的新娘数量不少于这些新郎的数量
// 设 [L[i], R[i]] 表示新郎 i 在距离 <=d 的前提下能匹配的新娘区间
// 考虑新郎区间 [l, r]，则能匹配的新娘区间为 [L[l], R[r]]
// 我们希望 R[r] - L[l] >= r - l
// 也就是 R[r] - r >= L[l] - l
// 进一步，对于每个 r，希望 R[r] - r >= max(L[l] - l) for all l <= r
bool check(int d){
    int pl = 1, pr = n;
    // 用双指针求出 L[i], R[i]，仔细思考断环为链时要复制几次！
    for(int i = n + 1; i <= 3 * n; i++){
        while(b[pl] < a[i] - d) pl++;
        while(b[pr + 1] <= a[i] + d) pr++;
        L[i] = pl; R[i] = pr;
    }
    int maxl = L[n + 1] - (n + 1);
    for(int i = n + 1; i <= 3 * n; i++){
        maxl = max(maxl, L[i] - i);
        if(R[i] - i < maxl) return false;
    }
    return true;
}

signed main(){
    scanf("%lld%lld", &n, &len);
    for(int i = 1; i <= n; i++) scanf("%lld", a + i);
    for(int i = 1; i <= n; i++) scanf("%lld", b + i);
    sort(a + 1, a + 1 + n);
    sort(b + 1, b + 1 + n);
    for(int i = n + 1; i <= 4 * n; i++) a[i] = a[i - n] + len;
    for(int i = n + 1; i <= 4 * n; i++) b[i] = b[i - n] + len;

    int l = 0, r = len / 2, mid;
    while(l < r){
        mid = (l + r) / 2;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << r << endl;

    return 0;
}