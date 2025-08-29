#include <vector>
#include <string>
#include <queue>
#include <tuple>
#include <algorithm>
using namespace std;

static const int DR[4] = {-1, 1, 0, 0};
static const int DC[4] = { 0, 0,-1, 1};

struct Solver {
    int R, C;
    vector<string> raw;
    vector<vector<int>> want;   // -1: 无数字；否则 0..4
    vector<vector<int>> val;    // -1: 未赋值；0:'.'；1:'*'
    vector<pair<int,int>> order;

    Solver(const vector<string>& g){
        raw=g; R=g.size(); C=R?g[0].size():0;
        want.assign(R, vector<int>(C,-1));
        val.assign(R, vector<int>(C,-1));
        for(int i=0;i<R;++i)for(int j=0;j<C;++j){
            char ch=g[i][j];
            if('0'<=ch && ch<='9') want[i][j]=ch-'0';
        }
        buildOrder();
    }

    void buildOrder(){
        vector<tuple<int,int,int,int>> key;
        for(int i=0;i<R;++i)for(int j=0;j<C;++j){
            int hasNum = (want[i][j]>=0);
            int neiNum = 0;
            for(int d=0;d<4;++d){
                int ni=i+DR[d], nj=j+DC[d];
                if(0<=ni&&ni<R&&0<=nj&&nj<C) if(want[ni][nj]>=0) ++neiNum;
            }
            int border = (i==0)+(i==R-1)+(j==0)+(j==C-1);
            key.emplace_back(-hasNum, -neiNum, -border, i*C+j);
        }
        sort(key.begin(), key.end());
        order.reserve(R*C);
        for(auto &t:key){ int id; tie(ignore,ignore,ignore,id)=t; order.push_back({id/C,id%C}); }
    }

    pair<int,int> boundsCell(int i,int j){
        if(want[i][j]<0) return {0,4};
        int mn=0,mx=0;
        for(int d=0;d<4;++d){
            int ni=i+DR[d], nj=j+DC[d];
            if(0<=ni&&ni<R&&0<=nj&&nj<C){
                int a=val[i][j], b=val[ni][nj];
                if(a!=-1 && b!=-1){ mn += (a^b); mx += (a^b); }
                else mx += 1;
            }else{
                int a=val[i][j];
                if(a!=-1){ mn += a; mx += a; }
                else mx += 1;
            }
        }
        return {mn,mx};
    }

    bool vertex_ok_after_set(int i,int j){
        for(int vr=i-1; vr<=i; ++vr) for(int vc=j-1; vc<=j; ++vc){
            if(!(0<=vr && vr+1<R && 0<=vc && vc+1<C)) continue;
            int a=val[vr][vc], b=val[vr][vc+1], c=val[vr+1][vc], d=val[vr+1][vc+1];
            if(a==-1||b==-1||c==-1||d==-1) continue;
            int e_top=(a!=b), e_left=(a!=c), e_right=(b!=d), e_bottom=(c!=d);
            int deg=e_top+e_left+e_right+e_bottom;
            if(deg==4) return false; // 禁止十字相交
        }
        return true;
    }

    bool local_constraints_ok(int i,int j){
        int qi[5], qj[5], cnt=0;
        qi[cnt]=i; qj[cnt]=j; ++cnt;
        for(int d=0;d<4;++d){
            int ni=i+DR[d], nj=j+DC[d];
            if(0<=ni&&ni<R&&0<=nj&&nj<C){ qi[cnt]=ni; qj[cnt]=nj; ++cnt; }
        }
        for(int k=0;k<cnt;++k){
            int r=qi[k], c=qj[k];
            if(want[r][c]<0) continue;
            auto [mn,mx]=boundsCell(r,c);
            int dneed=want[r][c];
            if(dneed<mn || dneed>mx) return false;
        }
        return true;
    }

    // —— 连通性（单连通 & 无洞）检查：满赋值后调用 ——
    bool connectivity_ok(){
        // 1) '*' 恰好一个连通块
        vector<vector<int>> vis(R, vector<int>(C,0));
        int total1=0, comps1=0;
        for(int i=0;i<R;++i) for(int j=0;j<C;++j) if(val[i][j]==1) ++total1;
        if(total1==0) return false;
        for(int i=0;i<R;++i) for(int j=0;j<C;++j) if(val[i][j]==1 && !vis[i][j]){
            ++comps1;
            if(comps1>1) return false;
            queue<pair<int,int>> q; q.push({i,j}); vis[i][j]=1;
            while(!q.empty()){
                auto [r,c]=q.front(); q.pop();
                for(int d=0;d<4;++d){
                    int nr=r+DR[d], nc=c+DC[d];
                    if(0<=nr&&nr<R&&0<=nc&&nc<C && val[nr][nc]==1 && !vis[nr][nc]){
                        vis[nr][nc]=1; q.push({nr,nc});
                    }
                }
            }
        }
        // 2) '.' 不允许有“内洞”：所有 '.' 必须与边界某处相连
        int total0=R*C-total1;
        if(total0==0) return true; // 没有 '.'
        vector<vector<int>> seen(R, vector<int>(C,0));
        queue<pair<int,int>> q;
        for(int j=0;j<C;++j){ // 上下边界
            if(val[0][j]==0 && !seen[0][j]){ seen[0][j]=1; q.push({0,j}); }
            if(val[R-1][j]==0 && !seen[R-1][j]){ seen[R-1][j]=1; q.push({R-1,j}); }
        }
        for(int i=0;i<R;++i){ // 左右边界
            if(val[i][0]==0 && !seen[i][0]){ seen[i][0]=1; q.push({i,0}); }
            if(val[i][C-1]==0 && !seen[i][C-1]){ seen[i][C-1]=1; q.push({i,C-1}); }
        }
        int reach0=0;
        while(!q.empty()){
            auto [r,c]=q.front(); q.pop(); ++reach0;
            for(int d=0; d<4; ++d){
                int nr=r+DR[d], nc=c+DC[d];
                if(0<=nr&&nr<R&&0<=nc&&nc<C && val[nr][nc]==0 && !seen[nr][nc]){
                    seen[nr][nc]=1; q.push({nr,nc});
                }
            }
        }
        // 若边界无 '.', 但存在 '.', 则必有洞
        if(reach0==0 && total0>0) return false;
        return reach0==total0;
    }

    bool dfs(int idx){
        if(idx==(int)order.size()){
            // 数字与顶点检查
            for(int i=0;i<R;++i) for(int j=0;j<C;++j) if(want[i][j]>=0){
                int s=0;
                for(int d=0; d<4; ++d){
                    int ni=i+DR[d], nj=j+DC[d];
                    if(0<=ni&&ni<R&&0<=nj&&nj<C) s += (val[i][j]^val[ni][nj]);
                    else s += val[i][j];
                }
                if(s!=want[i][j]) return false;
            }
            for(int vr=0; vr+1<R; ++vr) for(int vc=0; vc+1<C; ++vc){
                int a=val[vr][vc], b=val[vr][vc+1], c=val[vr+1][vc], d=val[vr+1][vc+1];
                int deg=(a!=b)+(a!=c)+(b!=d)+(c!=d);
                if(deg==4) return false;
            }
            // —— 新增：单连通性与无洞 —— 
            return connectivity_ok();
        }
        int i=order[idx].first, j=order[idx].second;
        for(int v=0; v<=1; ++v){
            val[i][j]=v;
            if(!vertex_ok_after_set(i,j)){ val[i][j]=-1; continue; }
            if(local_constraints_ok(i,j) && dfs(idx+1)) return true;
            val[i][j]=-1;
        }
        return false;
    }

    vector<string> solve(){
        dfs(0);
        vector<string> out(R,string(C,'.'));
        for(int i=0;i<R;++i) for(int j=0;j<C;++j)
            out[i][j] = (val[i][j]==1 ? '*' : '.');
        return out;
    }
};

vector<string> Slitherlink(vector<string> slitherMap){
    Solver S(slitherMap);
    return S.solve();
}