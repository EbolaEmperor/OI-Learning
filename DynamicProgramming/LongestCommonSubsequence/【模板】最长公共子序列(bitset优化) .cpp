#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int M = 64;

template<int N> class BitSet{
private:
    ULL data_[N];
public:
    BitSet(){
        memset(data_, 0, sizeof(data_));
    }
    BitSet(const BitSet<N> &rhs) {
        memcpy(data_, rhs.data_, sizeof(data_));
    }

    void setone(int i){
        data_[i/M] |= 1ull << (i % M);
    }

    BitSet& lshift(){
        ULL last = 0;
        for(int i = 0; i < N; ++i){
            ULL cur = data_[i] >> 63;
            (data_[i] <<= 1) |= last;
            last = cur;
        }
        return *this;
    }

    #define BinaryOp(Op) BitSet<N>& operator Op (const BitSet<N> &rhs){ \
        for(int i = 0; i < N; ++i)                                      \
            data_[i] Op rhs.data_[i];                                   \
        return *this;                                                   \
    }
    BinaryOp(&=)
    BinaryOp(^=)
    BinaryOp(|=)
    BinaryOp(=)
    #undef BinaryOp

    friend BitSet<N> operator - (const BitSet<N> &lhs, const BitSet<N> &rhs) {
        ULL last = 0ull;
        BitSet<N> ret;
        for (int i = 0; i < N; i++){
            ULL cur = (lhs.data_[i] < rhs.data_[i] + last);
            ret.data_[i] = lhs.data_[i] - rhs.data_[i] - last;
            last = cur;
        }
        return ret;
    }

    int popcount() const{
        int ans = 0;
        for(int i = 0; i < N; ++i)
            ans += __builtin_popcountll(data_[i]);
        return ans;
    }
};

const int MAXN = 70000;
const int MAXV = MAXN;

int LCS(int n, int *a, int m, int *b){
    const int B = MAXV / M + 1;
    using BS = BitSet<B>;
    static BS p[MAXN];
    for(int i = 0; i < n; ++i) p[a[i]].setone(i);
    BS curM, lastM;
    for(int i = 0; i < m; ++i){
        int c = b[i];
        (curM = lastM) |= p[c];
        lastM.lshift().setone(0);
        lastM = curM - lastM;
        (lastM ^= curM) &= curM;
    }
    return lastM.popcount();
}

int main(){
    static int a[MAXN], b[MAXN];
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) scanf("%d", a+i);
    for(int i = 0; i < m; ++i) scanf("%d", b+i);
    cout << LCS(n, a, m, b) << endl;
    return 0;
}
