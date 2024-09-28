#include <bits/stdc++.h>
using namespace std;

const int N = 100010;
char s[N];
int z[N], cnt[N];
bool perfect[N];

void get_z(char s[], int z[]){
    int n = strlen(s+1);
    int l = 1, r = 1;
    for(int i = 2; i <= n; i++){
        z[i] = (i <= r) ? min(z[i-l+1], r-i+1) : 0;
        while(i+z[i] <= n && s[1+z[i]] == s[i+z[i]]) z[i]++;
        if(i+z[i]-1 > r) l = i, r = i+z[i]-1;
    }
    z[1] = n;
}

int main(){
    scanf("%s", s+1);
    get_z(s, z);

    int n = strlen(s+1), sum = 0;
    for(int i = 1; i <= n; i++){
        cnt[z[i]]++;
        if(i + z[i] - 1 == n)
            sum++, perfect[z[i]] = true;
    }
    for(int i = n-1; i >= 1; i--)
        cnt[i] += cnt[i+1];

    printf("%d\n", sum);
    for(int i = 1; i <= n; i++)
        if(perfect[i]) printf("%d %d\n", i, cnt[i]);

    return 0;
}