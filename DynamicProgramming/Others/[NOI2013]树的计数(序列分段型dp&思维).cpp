#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;

struct Double{
    double val;
    int p;
    Double(double val = 0, int p = 0): val(val), p(p) {}
    Double& cap(){
        if(val == 0){
            p = 0;
            return *this;
        }
        while(abs(val) > 1e18) val /= 2, p++;
        while(abs(val) < 1e-18) val *= 2, p--;
        return *this;
    }
    void operator = (int x){p = 0; val = x;}
    Double operator + (const Double &x){
        if(x.p - p > 50)return x;
        if(p - x.p > 50)return *this;
        return Double(val + x.val * pow(2.0, x.p - p), p).cap();
    }
    void operator += (const Double &x){*this = *this + x; cap();}
    Double operator - (){return Double(-val, p);}
    Double operator - (Double &x){return ((*this) + (-x)).cap();}
    Double operator / (const Double &x){return Double(val / x.val, p - x.p).cap();}
    double get() const{return val * pow(2.0, p);}
};

const int N = 200005;
int a[N], p[N], b[N], n;
int nx[N];
Double sum[N][2], sumsum[N][2];
int pre[N];

int main(){
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
        scanf("%d", a + i);
    for(int i = 1; i <= n; i++)
        scanf("%d", b + i), p[b[i]] = i;
    for(int i = 1; i <= n; i++)
        a[i] = p[a[i]];
    for(int i = 1; i <= n; i++)
        p[a[i]] = i;
    pre[2] = 2;
    for(int i = 3; i <= n; i++)
        pre[i] = (p[i-1] < p[i]) ? pre[i-1] : i;
    for(int j = 2; j <= n; j++)
        nx[j] = a[p[j-1]+1];
    sum[1][0] = 1; sum[1][1] = 1;
    sumsum[1][0] = 1; sumsum[1][1] = 1;
    int r = 2;
    for(int i = 2; i <= n; i++){
        // 条件 2 的提前判定
        // for(int k = 1; k < n; k++)
        //     if(a[k] < pre[i]-1 && a[k+1] > i) break;
        // 如果上面 break 了，就不行。
        // 对于 a[k+1] <= i 的情况，在 i 之前的循环里就已经判过了，保证了 a[k] < pre[i'] - 1 对某个 i'<i 成立
        // 而 pre 是递增的，所以 a[k] < pre[i] - 1 对 i 肯定也成立，所以不用判了
        r = max(r, pre[i] - 1);
        while(r < i && nx[r + 1] <= i) r++;
        if(r >= pre[i]){
            sum[i][0] = sumsum[r - 1][0] - sumsum[pre[i] - 2][0];
            sum[i][1] = sumsum[r - 1][1] - sumsum[pre[i] - 2][1] + sum[i][0];
        }
        sumsum[i][0] = sumsum[i - 1][0] + sum[i][0];
        sumsum[i][1] = sumsum[i - 1][1] + sum[i][1];
    }
    printf("%.3lf\n", (sum[n][1] / sum[n][0]).get());
    return 0;
}