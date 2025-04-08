#ifndef MODINT_HPP
#define MODINT_HPP

#include <iostream>
#include <utility>
#include <cmath>
#include <cassert>
#include <algorithm>
#include <vector>

template<int mod>
class ModInt {
private:
    int x;

public:
    // 构造函数
    ModInt() : x(0) {}
    
    ModInt(long long y) {
        x = y % mod;
        if (x < 0) x += mod;
    }
    
    // 获取值
    int get() const { return x; }
    
    // 加法
    ModInt operator+(const ModInt& other) const {
        int res = x + other.x;
        if (res >= mod) res -= mod;
        return ModInt(res);
    }
    
    ModInt& operator+=(const ModInt& other) {
        x += other.x;
        if (x >= mod) x -= mod;
        return *this;
    }
    
    // 减法
    ModInt operator-(const ModInt& other) const {
        int res = x - other.x;
        if (res < 0) res += mod;
        return ModInt(res);
    }
    
    ModInt& operator-=(const ModInt& other) {
        x -= other.x;
        if (x < 0) x += mod;
        return *this;
    }
    
    // 乘法
    ModInt operator*(const ModInt& other) const {
        return ModInt(1LL * x * other.x);
    }
    
    ModInt& operator*=(const ModInt& other) {
        x = 1LL * x * other.x % mod;
        return *this;
    }
    
    // 幂运算
    friend ModInt modpow(ModInt a, long long n) {
        ModInt res(1);
        while (n > 0) {
            if (n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }
    
    // 求逆元（假设mod是质数）
    friend ModInt inv(const ModInt &a) {
        return modpow(a, mod - 2);  // 使用费马小定理: a^(p-1) ≡ 1 (mod p)
    }
    
    // 除法
    ModInt operator/(const ModInt& other) const {
        return *this * inv(other);
    }
    
    ModInt& operator/=(const ModInt& other) {
        return *this = *this * inv(other);
    }
    
    // 比较运算符
    bool operator==(const ModInt& other) const { return x == other.x; }
    bool operator!=(const ModInt& other) const { return x != other.x; }
    
    // 前缀增减
    ModInt& operator++() {
        x++;
        if (x == mod) x = 0;
        return *this;
    }
    
    ModInt& operator--() {
        if (x == 0) x = mod;
        x--;
        return *this;
    }
    
    // 后缀增减
    ModInt operator++(int) {
        ModInt result = *this;
        ++*this;
        return result;
    }
    
    ModInt operator--(int) {
        ModInt result = *this;
        --*this;
        return result;
    }

    // 二次剩余求解（返回较小的解）
    friend std::pair<ModInt,ModInt> sqrt(const ModInt& a) {
        // 如果a是0，则sqrt(a) = 0
        if (a.x == 0) return std::make_pair(ModInt(0), ModInt(0));
        
        // 如果mod不是质数或mod=2，这个方法可能不适用
        if (mod == 2) return std::make_pair(a, a);
        
        // 首先，检查a是否是二次剩余
        if (modpow(a, (mod - 1) / 2).x != 1)
            return std::make_pair(ModInt(-1), ModInt(-1)); // a不是二次剩余
        
        // 将p-1写成2^s * q的形式
        int s = 0;
        int q = mod - 1;
        while (q % 2 == 0) {
            q /= 2;
            ++s;
        }
        
        // 寻找一个二次非剩余z
        ModInt z(2);
        while (modpow(z, (mod - 1) / 2).x == 1)
            z = ModInt(z.x + 1);
        
        int m = s;
        ModInt c = modpow(z, q);
        ModInt t = modpow(a, q);
        ModInt r = modpow(a, (q + 1) / 2);
        
        while (t.x != 1) {
            // 找到最小的i使得t^(2^i) ≡ 1 (mod p)
            int i = 0;
            ModInt temp = t;
            while (temp.x != 1) {
                temp = temp * temp;
                ++i;
                if (i == s)
                    return std::make_pair(ModInt(-1), ModInt(-1)); // 没有找到合适的i
            }
            
            // 计算b = c^(2^(m-i-1))
            ModInt b = c;
            for (int j = 0; j < m - i - 1; ++j)
                b = b * b;
            
            m = i;
            c = b * b;
            t = t * c;
            r = r * b;
        }
        
        // 返回较小的那个解
        ModInt neg_r(mod - r.x);
        if(neg_r.x < r.x) return std::make_pair(neg_r, r);
        return std::make_pair(r, neg_r);
    }
    
    // 输入输出运算符重载
    friend std::ostream& operator<<(std::ostream& os, const ModInt& mi) {
        return os << mi.x;
    }
    
    friend std::istream& operator>>(std::istream& is, ModInt& mi) {
        long long t;
        is >> t;
        mi = ModInt(t);
        return is;
    }

    bool operator< (const ModInt& other) const {
        return x < other.x;
    }
    bool operator> (const ModInt& other) const {
        return x > other.x;
    }
    bool operator<= (const ModInt& other) const {
        return x <= other.x;
    }
    bool operator>= (const ModInt& other) const {
        return x >= other.x;
    }
};

#endif // MODINT_HPP