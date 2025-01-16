#include <bits/stdc++.h>
using namespace std;

stack<char> op;
struct Node{
    bool isnum;
    int num;
    char op;
};
Node newNum(int x){return (Node){true, x, ' '};}
Node newOp(char c){return (Node){false, 0, c};}
vector<Node> sufexpr;

int prio(char c){
    if(c == '+' || c == '-') return 1;
    else if(c == '*' || c == '/') return 2;
    else if(c == '^') return 3;
    else return 0;
}

void deal(int pri){
    while(!op.empty() && prio(op.top()) >= pri){
        if(op.top() == '('){
            op.pop();
            break;
        }
        sufexpr.push_back(newOp(op.top()));
        op.pop();
    }
}

void output(){
    for(Node p : sufexpr){
        if(p.isnum) printf("%d ", p.num);
        else printf("%c ", p.op);
    }
    printf("\n");
}

int calc(int a, int b, char c){
    if(c == '+') return a + b;
    else if(c == '-') return a - b;
    else if(c == '*') return a * b;
    else if(c == '/') return a / b;
    else return pow(a, b);
}

void compute(){
    while(sufexpr.size() > 1){
        for(auto it = sufexpr.begin(); it != sufexpr.end(); ++it)
            if(!it->isnum){
                auto jt = it; --jt; -- jt;
                int a = jt->num; sufexpr.erase(jt);
                int b = jt->num; sufexpr.erase(jt);
                jt->num = calc(a, b, jt->op);
                jt->isnum = true;
                break;
            }
        output();
    }
}

int main(){
    string s;
    cin >> s;
    s += '.';
    int pos = 0;
    char c = s[0];
    while(c != '.'){
        if(!isdigit(c)){
            if(c != '^' && c != '(') deal(prio(c));
            if(c != ')') op.push(c);
            c = s[++pos];
        } else {
            int x = 0;
            while(isdigit(c)){
                x = (x * 10 + (c - '0'));
                c = s[++pos];
            }
            sufexpr.push_back(newNum(x));
        }
    }
    deal(1);
    output();
    compute();
    return 0;
}