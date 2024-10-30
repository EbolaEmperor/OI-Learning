#include <iostream>
#include <cstring>
#include <vector>
#include <array>
#include <queue>
#include <algorithm>
using namespace std;

class ACAM{
private:
    int tot;
    vector<array<int,26>> ch;
    vector<int> fail, cnt;

    void insert(const string& s){
        int cur = 0;
        for(char c : s){
            int j = c - 'a';
            if(!ch[cur][j]){
                ch[cur][j] = tot++;
                ch.push_back(array<int,26> {});
                cnt.push_back(0);
            }
            cur = ch[cur][j];
        }
        cnt[cur]++;
    }

    void getfail(){
        fail.resize(tot, 0);
        queue<int> q;
        for(int c = 0; c < 26; c ++)
            if(ch[0][c]) q.push(ch[0][c]);
        while(!q.empty()){
            int u = q.front(); q.pop();
            int f = fail[u];
            for(int c = 0; c < 26; c++){
                int& v = ch[u][c];
                if(!v) v = ch[f][c];
                else{
                    fail[v] = ch[f][c];
                    cnt[v] += cnt[fail[v]];
                    q.push(v);
                }
            }
        }
    }

public:
    ACAM(const vector<string>& patterns): tot(1), ch(1, array<int,26> {}), cnt(1, 0){
        for(auto& s : patterns)
            insert(s);
        getfail();
    }
    ~ACAM(){
        vector<int>().swap(fail);
        vector<array<int,26>>().swap(ch);
        tot = 0;
    }

    vector<int> traval(const string &t) const{
        vector<int> f(t.size());
        int cur = 0;
        for(int i = 0; i < t.size(); i++){
            cur = ch[cur][t[i] - 'a'];
            f[i] = cnt[cur];
        }
        return f;
    }
};

int main(){
    string t;
    int n;
    cin >> t >> n;
    vector<string> patterns(n);
    for(auto& s : patterns)
        cin >> s;
    
    ACAM acam(patterns);
    auto f = acam.traval(t);

    for(auto& s : patterns)
        reverse(s.begin(), s.end());
    reverse(t.begin(), t.end());
    ACAM invacam(patterns);
    auto invf = invacam.traval(t);
    reverse(invf.begin(), invf.end());

    long long ans = 0;
    for(int i = 0; i < t.size() - 1; i++)
        ans += (long long) f[i] * invf[i + 1];
    cout << ans << endl;
    return 0;
}