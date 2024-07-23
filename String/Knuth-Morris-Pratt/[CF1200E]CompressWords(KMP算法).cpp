#include<bits/stdc++.h>
using namespace std;
const int N = 1000010;

int getBorder(char *s){
    static int nxt[N];
    int len = strlen(s+1), j = 0;
    memset(nxt, 0, sizeof(int) * (len + 1));
    for(int i = 2; i <= len; i++){
        while(j && s[i] != s[j + 1]) j = nxt[j];
        if(s[i] == s[j+1]) j++;
        nxt[i] = j;
    }
    return nxt[len];
}

int main(){
    int n, tot = 0;
    static char s[N], t[N];
    scanf("%d", &n);
    while(n--){
        scanf("%s", t + 1);
        int len = strlen(t + 1);
        int m = min(len, tot);
        t[++len] = '#';
        for(int i = 1; i <= m; ++i)
            t[++len] = s[tot - m + i];
        t[len + 1] = '\0';
        m = getBorder(t);
        while(t[m + 1] != '#') s[++tot] = t[++m];
    }
    printf("%s\n", s + 1);
    return 0;
}
