#include <bits/stdc++.h>
using namespace std;

const int N = 110;
struct Node{
    int require, earn;
    bool operator < (const Node &rhs) const{
        return earn > rhs.earn;
    }
};
bool cmp1(const Node &a, const Node &b){
    return a.require < b.require;
}
bool cmp2(const Node &a, const Node &b){
    return a.require + a.earn > b.require + b.earn;
}

int main(){
    int n, rating, ans = 0;
    vector<Node> positive, negative;

    cin >> n >> rating;
    for(int i = 1; i <= n; i++){
        Node tmp;
        cin >> tmp.require >> tmp.earn;
        if(tmp.earn >= 0) positive.push_back(tmp);
        else negative.push_back(tmp);
    }
    sort(positive.begin(), positive.end(), cmp1);
    sort(negative.begin(), negative.end(), cmp2);

    for(auto p : positive)
        if(rating >= p.require)
            ans++, rating += p.earn;
        else break;

    priority_queue<Node> pq;
    for(auto p : negative){
        if(rating >= p.require && rating + p.earn >= 0)
            pq.push(p), ans++, rating += p.earn;
        else{
            if(!pq.empty() && 
                  pq.top().earn < p.earn && 
                  rating - pq.top().earn >= p.require){
                rating -= pq.top().earn;
                pq.pop();
                rating += p.earn;
                pq.push(p);
            }
        }
    }

    cout << ans << endl;
    return 0;
}
