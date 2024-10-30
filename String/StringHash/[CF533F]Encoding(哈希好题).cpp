#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
using namespace std;

const int N = 200010;
const int mod = 1e9 + 7, base = 233;

class Hash{
private:
    int n;
    vector<int> pwB;
    vector<int> h[26];
    unordered_map<int, int> mp;

public:
    Hash(const string &s){
        n = s.size();
        for(int c = 0; c < 26; c++){
            h[c].resize(n + 1, 0);
            for(int i = 1; i <= n; i++){
                h[c][i] = (long long) h[c][i-1] * base % mod;
                if(s[i-1] - 'a' == c) h[c][i] = (h[c][i] + 1) % mod;
            }
            mp[h[c][n]] = c;
        }
        pwB.resize(n + 1, 0);
        pwB[0] = 1;
        for(int i = 1; i <= n; i++)
            pwB[i] = (long long) pwB[i-1] * base % mod;
    }
    
    int getHash(int l, int r, int c) const{
        return (h[c][r] - (long long) h[c][l-1] * pwB[r-l+1] % mod + mod) % mod;
    }
    
    int getFullHash(int c) const{
        return h[c][n];
    }

    int findChar(int hashval) const{
        auto it = mp.find(hashval);
        return it == mp.end() ? -1 : it->second;
    }
};

int main(){
    int n, m;
    cin >> n >> m;
    string s, t;
    cin >> s >> t;
    Hash hs(s), ht(t);
    vector<int> ans;

    for(int i = 1; i <= n-m+1; i++){
        bool matched = true;
        for(int c = 0; c < 26; c++){
            int tmp = hs.getHash(i, i+m-1, c);
            if(!tmp) continue;
            int d = ht.findChar(tmp);
            if(d == -1 || hs.getHash(i, i+m-1, d) != ht.getFullHash(c)){
                matched = false;
                break;
            }
        }
        if(matched) ans.push_back(i);
    }

    cout << ans.size() << endl;
    for(int x : ans)
        cout << x << " ";
    cout << endl;
    return 0;
}