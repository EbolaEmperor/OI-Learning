#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
int stklow[N], top1 = -1;
int stkhigh[N], top2 = 0;
int a[N], n, ans = 0;

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", a + i);
    for(int i = 1; i <= n; ++i){
        while(top1 >= 0 && a[stklow[top1]] >= a[i]) --top1;
        while(top2 >= 1 && a[stkhigh[top2]] < a[i]) --top2;
        if(top1 >= 0 && stklow[top1] > stkhigh[top2]){
            // 满足 a[j] < a[i] 且 (j,i) 中所有数都 > a[j] 的 j 一定在 stklow 中
            // i 左边第一个 >=a[i] 的位置是 stkhigh[top2]，这个位置必须在上述 j 的左侧
            // 所以在 stklow 里找到第一个大于 stkhigh[top2] 的位置 j
            int j = *upper_bound(stklow, stklow + top1 + 1, stkhigh[top2]);
            ans = max(ans, i - j + 1);
        }
        stklow[++top1] = stkhigh[++top2] = i;
    }
    cout << ans << endl;
    return 0;
}