#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef unsigned long long ULL;
const int BITSET_M = 64;
const int BITSET_MM = BITSET_M - 1;

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
        data_[i/BITSET_M] |= 1ull << (i & BITSET_MM);
    }

    bool operator [] (int i) const{
        return (data_[i / BITSET_M] >> (i & BITSET_MM)) & 1;
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

    BitSet operator << (int l) const{
        BitSet<N> ret;
        if (l <= 0) return *this;
        if (l >= N * BITSET_M) return ret;
        int unit_shift = l / BITSET_M;
        int bit_shift = l % BITSET_M;
        if (bit_shift == 0) {
            for (int i = 0; i + unit_shift < N; ++i)
                ret.data_[i + unit_shift] = data_[i];
        } else {
            for (int i = 0; i + unit_shift + 1 < N; ++i)
                ret.data_[i + unit_shift + 1] |= data_[i] >> (BITSET_M - bit_shift);
            for (int i = 0; i + unit_shift < N; ++i)
                ret.data_[i + unit_shift] |= data_[i] << bit_shift;
        }
        return ret;
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

    #define BinaryOp2(Op) BitSet<N> operator Op (const BitSet<N> &rhs) const{ \
        BitSet<N> ret;                                                 \
        for(int i = 0; i < N; ++i)                                     \
            ret.data_[i] = data_[i] Op rhs.data_[i];                   \
        return ret;                                                    \
    }
    BinaryOp2(&)
    BinaryOp2(^)
    BinaryOp2(|)
    #undef BinaryOp2

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

    int find_low() const{
        for(int i = 0; i < N; ++i){
            if(data_[i]){
                return i * BITSET_M + (63 - __builtin_ctzll(data_[i]));
            }
        }
        return -1;
    }

    int find_high() const{
        for(int i = N - 1; i >= 0; --i){
            if(data_[i]){
                return i * BITSET_M + (63 - __builtin_clzll(data_[i]));
            }
        }
        return -1;
    }

    bool is_zero() const{
        for(int i = 0; i < N; ++i){
            if(data_[i]) return false;
        }
        return true;
    }
    
    void clear(){
        memset(data_, 0, sizeof(data_));
    }

    // 注：这是将 BitSet 看作 mod 2 数域中的多项式，进行多项式取模
    BitSet operator % (const BitSet &rhs) const{
        BitSet<N> ret = *this;
        int l = find_high(), r = rhs.find_high();
        if(l < r) return ret;
        while(l >= r){
            int d = l - r;
            ret = ret ^ (rhs << d);
            l = ret.find_high();
        }
        return ret;
    }

    // 注：这是将 BitSet 看作 mod 2 数域中的多项式，进行多项式整除
    BitSet operator / (const BitSet &rhs) const{
        BitSet<N> dividend = *this;
        BitSet<N> quotient;
        int l = dividend.find_high();
        int r = rhs.find_high();
        if (l < r) return quotient;
        while (l >= r) {
            int d = l - r;
            quotient.setone(d);
            dividend = dividend ^ (rhs << d);
            l = dividend.find_high();
        }
        return quotient;
    }

    // 注：这是将 BitSet 看作 mod 2 数域中的多项式，进行多项式 gcd
    friend BitSet gcd(const BitSet &a, const BitSet &b){
        return b.is_zero() ? a : gcd(b, a % b);
    }

    int to_int(int mod) const{
        __uint128_t ret = 0;
        for(int i = N - 1; i >= 0; --i){
            ret = (ret << BITSET_M) + data_[i];
            ret %= mod;
        }
        return (int)ret;
    }

    friend istream &operator >> (istream &in, BitSet &A){
        string s;
        in >> s;
        int len = 0;
        for(int i = s.size() - 1; i >= 0; i--){
            if(s[i] - '0') A.setone(len);
            len++;
        }
        return in;
    }

    friend ostream &operator << (ostream &out, const BitSet &A){
        int len = A.find_high();
        if(len == -1) out << 0;
        else{
            for(int i = len; i >= 0; --i){
                out << A[i];
            }
        }
        return out;
    }

    bool operator <= (const BitSet &rhs) const{
        for(int i = N - 1; i >= 0; --i){
            if(data_[i] ^ rhs.data_[i])
                return data_[i] < rhs.data_[i];
        }
        return true;
    }
};