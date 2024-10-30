#include <iostream>
#include <cstring>
using namespace std;

const int ha = 998244353;
const int N = 17, L = 1010;
int n, tot;
string str;
int cnt[N+1][1<<N];
// cnt[k][s]: 可用字符集总大小为 k，实际用且仅用集合 s 中的字符，可以产生多少回文子串
int pwk[N+1][L];

inline void add(int &x, const int &y){
    x = (x + y >= ha) ? (x + y - ha) : (x + y);
}

void extend(int l, int r, bool odd){
    if(odd){
        for(int k = 1; k <= 17; k++)
            add(cnt[k][0], pwk[k][tot]);
    }
    int nofree = 0, used = 0;
    while(l >= 0 && r < str.size()){
        if(str[l] == '?' && str[r] != '?')
            ++nofree, used |= 1 << (str[r] - 'a');
        else if(str[l] != '?' && str[r] == '?')
            ++nofree, used |= 1 << (str[l] - 'a');
        else if(str[l] == '?' && str[r] == '?')
            ++nofree;
        else if(str[l] != '?' && str[r] != '?' && str[l] != str[r])
            break;
        for(int k = 1; k <= 17; k++)
            add(cnt[k][used], pwk[k][tot - nofree]);
        l--; r++;
    }
}

int main(){
    cin >> n >> str;
    for(char c : str) tot += (c == '?');
    for(int k = 1; k <= 17; k++){
        pwk[k][0] = 1;
        for(int i = 1; i <= tot; i++)
            pwk[k][i] = (long long) pwk[k][i-1] * k % ha;
    }

    for(int i = 0; i < str.size(); i++){
        // 以 i 为中心的回文串
        extend(i-1, i+1, 1);
        // 以 i 和 i+1 中间的缝为中心的回文串
        if(i < str.size() - 1) extend(i, i+1, 0);
    }

    // 下面做子集前缀和，做完之后，cnt[k][s] 的含义变为：
    //    - 可用字符集总大小为 k，实际使用的字符被集合 s 包含，可以产生多少回文子串
    // 注意子集前缀和要避免重复累加，所以先枚举元素，再枚举集合
    for(int k = 1; k <= 17; k++)
        for(int i = 0; i < 17; i++)
            for(int s = 0; s < (1<<17); s++)
                if(s>>i&1) add(cnt[k][s], cnt[k][s^(1<<i)]);
    int q;
    string t;
    cin >> q;
    while(q--){
        cin >> t;
        int sta = 0;
        for(char c : t) sta |= 1 << (c - 'a');
        cout << cnt[t.size()][sta] << "\n";
    }
    return 0;
}