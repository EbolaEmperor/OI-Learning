#include <iostream>
#include <cstring>
#include <vector>
#include <array>
using namespace std;

class Trie{
private:
    int tot;
    vector<array<int,2>> ch;
    vector<bool> isfull;

public:
    void insert(const string& s){
        int cur = 0;
        for(char c : s){
            int j = c - '0';
            if(!ch[cur][j]){
                ch[cur][j] = tot++;
                ch.push_back(array<int,2> {});
                isfull.push_back(0);
            }
            cur = ch[cur][j];
        }
        isfull[cur] = 1;
    }

    void finalize(int cur = 0){
        if(!ch[cur][0] && !ch[cur][1]) return;
        if(ch[cur][0]) finalize(ch[cur][0]);
        if(ch[cur][1]) finalize(ch[cur][1]);
        isfull[cur] = (ch[cur][0] && ch[cur][1]) ? (isfull[ch[cur][0]] && isfull[ch[cur][1]]) : 0;
    }

    bool full() const{
        return isfull[0];
    }

    string getmin(int k) const{
        int cur = 0;
        string ans;
        while(k){
            int c = isfull[ch[cur][0]] ? 1 : 0;
            ans += (char)(c + '0');
            cur = ch[cur][c];
            k--;
            if(!cur) break;
        }
        while(k--) ans += '0';
        return ans;
    }

    Trie(): tot(1), ch(1, array<int,2> {}), isfull(1, 0) {}
    ~Trie(){
        vector<bool>().swap(isfull);
        vector<array<int,2>>().swap(ch);
        tot = 0;
    }
};

void work(){
    int n, k;
    string s;
    cin >> n >> k >> s;
    for(char &c : s) c = (c == '0') ? '1' : '0';
    int l = min(k, 20), acc0 = 0;
    Trie trie;
    for(int i = 0; i <= n - l; i++){
        if(acc0 >= k - l) trie.insert(s.substr(i, l));
        if(s[i] == '0') ++acc0;
        else acc0 = 0;
    }
    trie.finalize();
    if(trie.full()) puts("NO");
    else {
        puts("YES");
        string ans(k - l, '0');
        ans += trie.getmin(l);
        cout << ans << "\n";
    }
}

int main(){
    int T;
    cin >> T;
    while(T--) work();
    return 0;
}