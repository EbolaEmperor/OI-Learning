#include <bits/stdc++.h>
using namespace std;

const int N = 5010;
int n, h[N], sum[N];
int minop[N], minlast[N], tag[N];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", h + i), sum[i] = sum[i-1] + h[i];
    memset(minop, 0x3f, sizeof(minop));
    memset(minlast, 0x3f, sizeof(minlast));
    minop[0] = 0; minlast[0] = -0x3f3f3f3f;
    for(int i = 1; i <= n; ++i){
        // Find the last j such that minlast[j] + sum[j] <= sum[i].
        // --> Find the minimum p such that minlast[i] + sum[i] <= sum[p].
        //     Put a tag i on p.
        //     The tag should take max with the previous tag.
        // Note: Find the p for i-1 first, then update minop[i] and minlast[i].
        int p = lower_bound(sum + 1, sum + 1 + n, minlast[i-1] + sum[i-1]) - sum;
        tag[p] = i - 1;
        tag[i] = max(tag[i], tag[i-1]);
        minop[i] = minop[tag[i]] + (i - tag[i] - 1);
        minlast[i] = sum[i] - sum[tag[i]];
    }
    cout << minop[n] << endl;
    return 0;
}