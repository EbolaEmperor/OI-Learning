/***************************************************************
 *
 * 这是一个利用高精度整数运算库
 * 运算效率较低，但能保证绝对精确的运算，可用于理论研究
 * 
 * copyright © 2022 Wenchong Huang, All rights reserved.
 *
 **************************************************************/

#ifndef _BIGINT_H_
#define _BIGINT_H_

#include <iostream>
#include <cstring>
#include <vector>

typedef unsigned long long ull;
const ull pre32 = ((1ull<<32)-1)<<32;
const ull aft32 = (1ull<<32)-1;

int debug = 0;

class bigint{
private:
    std::vector<unsigned> num;
    bool isneg() const{
        return (num.back()>>31)&1;
    }
    bool iszero() const{
        return num.size()==1 && num[0]==0;
    }
    void removeprezero(){
        while(num.size()>=2 && num.back()==0 && (num[num.size()-2]>>31)==0)
            num.pop_back();
    }
    void leftmove32(const int &x){
        num.resize(num.size()+x);
        for(int i = num.size()-1; i >= x; i--)
            num[i] = num[i-x];
        for(int i = x-1; i >= 0; i--)
            num[i] = 0;
    }

public:
    // 构造函数
    bigint(){
        num.clear();
        num.push_back(0);
    }
    bigint(int x){
        num.clear();
        num.push_back((unsigned)x);
    }
    bigint(long long x){
        num.clear();
        ull y = (ull)x;
        num.push_back( (unsigned)(y & aft32) );
        num.push_back( (unsigned)((y & pre32)>>32) );
    }
    bigint(const std::string &s){
        bigint c;
        if(!s.empty()){
            int bg = 0;
            if(s[0]=='-') bg = 1;
            for(int i = bg; i < s.size(); i++){
                c = c*10 + (s[i]-'0');
            }
            if(!bg && c.isneg()){
                c.num.push_back(0);
            }
            if(bg) c = -c;
        }
        std::swap(num, c.num);
    }
    bigint(const bigint &rhs){
        num = rhs.num;
    }
    ~bigint(){
        num.clear();
    }

    // 基础运算
    bigint & operator = (const bigint & rhs){
        bigint copy(rhs);
        std::swap(*this, copy);
        return *this;
    }
    bigint & operator = (bigint && rhs){
        std::swap(num, rhs.num);
        return *this;
    }
    bigint operator - () const{
        bigint c(*this);
        if(c.iszero()) return c;
        else if(!c.isneg()){
            for(unsigned &x : c.num)
                x = ~x;
            ull tmp = 1ull;
            for(int i = 0; i < c.num.size(); i++){
                tmp += (ull)c.num[i];
                c.num[i] = (unsigned)(tmp&aft32);
                tmp >>= 32;
            }
        }
        else{
            int k = 0;
            while(c.num[k]==0) k++;
            c.num[k]--;
            for(int i = k-1; i>=0; i--)
                c.num[i] = (unsigned)aft32;
            for(unsigned &x : c.num)
                x = ~x;
        }
        return c;
    }
    bigint operator + (const bigint &rhs) const{
        if(isneg() && rhs.isneg())
            return -( -(*this) + -rhs );
        bigint a(*this), b(rhs);
        int m = std::max(a.num.size(), b.num.size());
        for(int i = a.num.size(); i < m; i++)
            a.num.push_back(a.isneg() ? aft32 : 0);
        for(int i = b.num.size(); i < m; i++)
            b.num.push_back(b.isneg() ? aft32 : 0);
        bigint c;
        c.num.resize(m);
        ull tmp = 0;
        for(int i = 0; i < m; i++){
            tmp += (ull)a.num[i] + b.num[i];
            c.num[i] = (unsigned)(tmp&aft32);
            tmp >>= 32;
        }
        if(!isneg() && !rhs.isneg() && c.isneg())
            c.num.push_back(0);
        c.removeprezero();
        return c;
    }
    bigint operator - (const bigint &b) const{
        return (*this) + -b;
    }
    bigint operator * (const long long &x) const{
        if(x==0 || iszero()) return bigint();
        if(!isneg() && x>0){
            ull carry = 0;
            bigint c;
            c.num.resize(num.size());
            for(int i = 0; i < num.size(); i++){
                ull tmp = (ull)num[i]*x + carry;
                c.num[i] = (unsigned)(tmp&aft32);
                carry = tmp >> 32;
            }
            if(carry) c.num.push_back(carry);
            if(c.isneg()) c.num.push_back(0);
            c.removeprezero();
            return c;
        } else if(isneg() && x>0){
            return -( -(*this) * x );
        } else if(!isneg() && x<0){
            return -( (*this) * -x );
        } else {
            return -(*this) * -x;
        }
    }
    bigint operator / (const int &x) const{
        if(iszero()) return bigint();
        if(x==0){
            std::cerr << "Math Error!" << std::endl;
            exit(-1);
        }
        if(!isneg() && x>0){
            bigint c;
            ull tmp = 0;
            c.num.resize(num.size());
            for(int i = num.size()-1; i >= 0; i--){
                tmp = tmp << 32 | num[i];
                c.num[i] = tmp/x;
                tmp -= tmp/x*x;
            }
            c.removeprezero();
            if(c.isneg()) c.num.push_back(0);
            return c;
        } else if(isneg() && x>0){
            return -( -(*this) / x );
        } else if(!isneg() && x<0){
            return -( (*this) / -x );
        } else {
            return -(*this) / -x;
        }
    }
    int operator % (const int &x) const{
        if(iszero()) return 0;
        if(x==0){
            std::cerr << "Math Error!" << std::endl;
            exit(-1);
        }
        if(!isneg() && x>0){
            bigint c = (*this) - (*this)/x*x;
            return c.num[0];
        } else if(isneg() && x>0){
            return -( -(*this) % x );
        } else if(!isneg() && x<0){
            return -( (*this) % -x );
        } else {
            return -(*this) % -x;
        }
    }
    bigint operator * (const bigint &x) const{
        if(x.iszero() || iszero()) return bigint();
        if(!isneg() && !x.isneg()){
            bigint c;
            for(int i = 0; i < x.num.size(); i++){
                bigint tmp = (*this) * x.num[i];
                tmp.leftmove32(i);
                c = c + tmp;
            }
            return c;
        } else if(isneg() && !x.isneg()){
            return -( -(*this) * x );
        } else if(!isneg() && x.isneg()){
            return -( (*this) * -x );
        } else {
            return -(*this) * -x;
        }
    }
    bigint operator / (const bigint &x) const{
        if(iszero()) return bigint();
        if(x.iszero()){
            std::cerr << "Math Error!" << std::endl;
            exit(-1);
        }
        if(!isneg() && !x.isneg()){
            bigint l, mid;
            bigint r(*this);
            while(l<=r){
                mid = (l+r)/2;
                if(x*mid<=(*this)) l=mid+1;
                else r=mid-1;
            }
            return r;
        } else if(isneg() && !x.isneg()){
            return -( -(*this) / x );
        } else if(!isneg() && x.isneg()){
            return -( (*this) / -x );
        } else {
            return -(*this) / -x;
        }
    }
    bigint operator % (const bigint &x) const{
        if(iszero()) return bigint();
        if(x.iszero()){
            std::cerr << "Math Error!" << std::endl;
            exit(-1);
        }
        if(!isneg() && !x.isneg()){
            return (*this) - (*this)/x*x;
        } else if(isneg() && !x.isneg()){
            return -( -(*this) % x );
        } else if(!isneg() && x.isneg()){
            return -( (*this) % -x );
        } else {
            return -(*this) % -x;
        }
    }
    bigint abs() const{
        if(isneg()) return -(*this);
        else return (*this);
    }

    // pow(a,b): a的b次方，只支持b为正整数，采用快速幂算法
    friend bigint pow(bigint a, bigint b){
        if(b.isneg()){
            std::cerr << "Bigint Error! Cannot calculate negative exponent in pow()";
            return 0;
        }
        bigint ans(1);
        while(!b.iszero()){
            if(b%2==1) ans = ans * a;
            a = a * a;
            b = b / 2;
        }
        return ans;
    }

    // bigFactorial(n): n的阶乘
    friend bigint bigFactorial(const bigint &n){
        if(n.isneg()){
            std::cerr << "Bigint Error! Cannot calculate negative fractorial.";
            return 0;
        }
        bigint ans(1), a(n);
        while(!a.iszero()){
            ans = ans * a;
            a = a - 1;
        }
        return ans;
    }

    // sqrt(a): 平方根(向下取整)
    friend bigint sqrt(const bigint &a){
        if(a.isneg()){
            std::cerr << "Bigint Error! Cannot calculate negative square root.";
            return 0;
        }
        bigint l=0, r=a, mid;
        while(l<=r){
            mid = (l+r)/2;
            if(mid*mid<=a) l=mid+1;
            else r=mid-1;
        }
        return r;
    }

    // downpow(n,k): 下降幂，即 n(n-1)...(n-k+1)
    friend bigint downpow(const bigint &n, const int &k){
        if(k<0){
            std::cerr << "Bigint Error! Cannot calculate negative exponent in downpow()";
            return 0;
        }
        bigint ans(1), a(n);
        for(int i = 0; i < k; i++){
            ans = ans * a;
            a = a - 1;
        }
        return ans;
    }

    // uppow(n,k): 上升幂，即 n(n+1)...(n+k-1)
    friend bigint uppow(const bigint &n, const int &k){
        if(k<0){
            std::cerr << "Bigint Error! Cannot calculate negative exponent in uppow()";
            return 0;
        }
        bigint ans(1), a(n);
        for(int i = 0; i < k; i++){
            ans = ans * a;
            a = a + 1;
        }
        return ans;
    }

    // 比较运算
    bool operator == (const bigint &b) const{
        bigint c = (*this) - b;
        return c.iszero();
    }
    bool operator < (const bigint &b) const{
        bigint c = (*this) - b;
        return c.isneg();
    }
    bool operator > (const bigint &b) const{
        bigint c = (*this) - b;
        return !c.isneg() && !c.iszero();
    }
    bool operator <= (const bigint &b) const{
        bigint c = (*this) - b;
        return c.isneg() || c.iszero();
    }
    bool operator >= (const bigint &b) const{
        bigint c = (*this) - b;
        return !c.isneg();
    }

    // 输入输出
    void bitprint() const{
        for(int i = num.size()-1; i>=0; i--)
            for(int k = 31; k>=0; k--){
                std::cout << ((num[i]>>k)&1);
                if(k%8==0) std::cout << ' ';
            }
        std::cout << std::endl;
    }
    friend std::istream & operator >> (std::istream & in, bigint &a){
        std::string s;
        in >> s;
        a = bigint(s);
        return in;
    }
    friend std::ostream & operator << (std::ostream & out, const bigint &a){
        if(a.iszero())
            return out << 0;
        bigint c(a);
        if(c.isneg()) out << '-', c = -c;
        std::string res;
        while(!c.iszero()){
            res += '0' + c%10;
            c = c / 10;
        }
        for(int i = res.size()-1; i >= 0; i--)
            out << res[i];
        return out;
    }
    double todouble(){
        const double g = (double)(1ll<<32);
        bigint c = isneg() ? -(*this) : *this;
        double res = 0;
        for(int i = c.num.size()-1; i >= 0; i--)
            res = res * g + (double)c.num[i];
        return isneg() ? -res : res;
    }

    friend bigint gcd(const bigint &a, const bigint &b){
        return b.iszero() ? a : gcd(b,a%b);
    }
};

#endif
