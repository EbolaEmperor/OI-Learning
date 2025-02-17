#include <bits/stdc++.h>
using namespace std;

const int N = 200010;
const char optype[] = "+-*/";
int lson[N], rson[N], n, special;
double val[N];
int op[N << 1];
random_device rd;
mt19937 rnd(rd());

enum SpecialType{
    Normal, Negative, Scientific, MissingBrackets, ManyZeros, Chaos, Pai
};

inline int oplevel(int u){
    return (op[u] <= 1) ? 1 : 2;
}

inline double calc(int op, double a, double b){
    if(op == 0) return a + b;
    else if(op == 1) return a - b;
    else if(op == 2) return a * b;
    else return a / b;
}

double output(int u){
    if(u < n){
        cout << val[u];
        return val[u];
    }
    double a, b;
    // lson
    if(lson[u] >= n && oplevel(lson[u]) < oplevel(u)){
        if(special != MissingBrackets || rnd() % 10) putchar('(');
        a = output(lson[u]);
        if(special != MissingBrackets || rnd() % 10) putchar(')');
    }
    else
        a = output(lson[u]);
    // operator
    putchar(optype[op[u]]);
    // rson
    if(rson[u] < n || rson[u] >= n && oplevel(rson[u]) > oplevel(u))
        b = output(rson[u]);
    else {
        if(special != MissingBrackets || rnd() % 10) putchar('(');
        b = output(rson[u]);
        if(special != MissingBrackets || rnd() % 10) putchar(')');
    }
    return calc(op[u], a, b);
}

void genChaos(){
    int cnt = 0;
    static const char s[] = "0123456789+-*/().";
    for(int i = 0; i < n; i++){
        int c = rnd() % 17;
        if(s[c] == '(') ++cnt;
        if(s[c] == ')'){
            if(cnt) --cnt;
            else putchar('(');
        }
        putchar(s[c]);
    }
    while(cnt--) putchar(')');
    putchar('\n');
}

int main(int argc, char *argv[]){
    if(argc < 2){
        cerr << "Please provide the file name." << endl;
        return 0;
    }
    n = (argc >= 3) ? stoi(argv[2]) : 10;
    int maxv = (argc >= 4) ? stoi(argv[3]) : 100;
    special = (argc >= 5) ? stoi(argv[4]) : Normal;

    string infname = argv[1];
    infname += ".in";
    freopen(infname.c_str(), "w", stdout);
    double ans = nan(0);

    if(special == Chaos)
        genChaos();
    else {
        deque<int> q;
        for(int i = 0; i < n; i++){
            if(special == Negative || special == Scientific)
                val[i] = ((double) rnd() / rnd.max() - 0.5) * maxv * 2;
            else if(special == Pai)
                val[i] = (double) (rnd() % 100) / 100 * maxv;
            else
                val[i] = (double) rnd() / rnd.max() * maxv;
            if(special == ManyZeros && rnd() % 10 == 0) val[i] = 0;
            q.push_back(i);
        }
        for(int i = n; i < 2 * n - 1; i++){
            op[i] = rnd() % 4;
            assert(q.size() >= 2);
            // lson
            if(rnd() & 1) lson[i] = q.front(), q.pop_front();
            else lson[i] = q.back(), q.pop_back();
            // rson
            if(rnd() & 1) rson[i] = q.front(), q.pop_front();
            else rson[i] = q.back(), q.pop_back();
            q.push_back(i);
        }
        if(special == 2) cout << scientific;
        cout << setprecision(12);
        ans = output(q.front());
        putchar('\n');
    }
    fclose(stdout);

    infname = argv[1];
    infname += ".out";
    freopen(infname.c_str(), "w", stdout);
    if(isnan(ans) || isinf(ans))
        cout << "ILLEGAL" << endl;
    else
        cout << fixed << ans << endl;
    fclose(stdout);

    return 0;
}