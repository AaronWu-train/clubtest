#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define AI(x) begin(x),end(x)
#define ll long long int
#define endl '\n'
#ifdef DEBUG
#define debug(args...) LKJ("[ "+string(#args)+" ]", args)
template<class I> void LKJ(I&&x){ cerr << x << '\n'; }
template<class I, class...T> void LKJ(I&&x, T&&...t){ cerr << x << ", ", LKJ(t...); }
template<class I> void OI(I a, I b){ while(a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define OI(...) 0
#endif
#define _ ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
const int maxn = 5e5+5;

vector<vector <pair<int, int>>> adj(maxn);
vector<pair<int, int>>bridge;
int bcccnt = 0;
int bl[maxn], odep[maxn], low[maxn];
bool vis[maxn];
stack <int, vector<int>> dfsr;
void dfs(int x, int fr){
    dfsr.push(x);
    vis[x]=1;
    odep[x]=odep[fr]+1;
    low[x]=odep[x];
    for (auto &j:adj[x]){
        auto &i = j.first;
        if (i != fr){
            if (vis[i]) low[x] = min(low[x], odep[i]);
            else{
                dfs(i, x);
                low[x] = min(low[x], low[i]);
            }
        }
    }
    if (low[x] == odep[x]){
        ++bcccnt;
        int k;
        do{
            k = dfsr.top(); dfsr.pop();
            bl[k] = bcccnt;
        }while (k != x);
        bridge.push_back(make_pair(x, fr));
    }
}

//void dfs2(int s, int e,vector<int>&dis, vector<bool>&visited, vector<vector<pair<int, int>>>&nadj) {
//    visited[s]=1;
//    for (auto [v,w] : nadj[s]) {
//        if(!visited[v]) {
//            dis[v]=min(dis[s], w);
//            dfs2(v, e, dis, visited, nadj);
//        }
//    }
//};

vector<int>dep(maxn);
int rmq[maxn][30]={0};
int st[maxn][30]={0};
//int ma = 0;
void dfs3(int fa, int x, vector<bool>&visited, vector<vector<pair<int, int>>>&nadj) {
    dep[x] = dep[fa]+1;
//    ma = max(dep[x],ma);
    visited[x] = 1;
    rmq[x][0] = x;
    rmq[x][1] = fa;
    for (int j = 2; j <= 20; ++j){
        rmq[x][j] = rmq[rmq[x][j-1]][j-1];
        st[x][j] = min(st[x][j-1], st[rmq[x][j-1]][j-1]);
    }
    for (auto& [v,w] : nadj[x]) {
        if (!visited[v]) {
            st[v][0] = INT_MAX;
            st[v][1] = w;
            dfs3(x,v,visited,nadj);
        }
    }
}

int lca(int a,int b){
    if(dep[a]>dep[b])swap(a,b);
    int jump=dep[b]-dep[a];
    for(int i=0;i<=20;i++){
        if(jump&(1<<i))b=rmq[b][i+1];
    }
    if(a==b)return a;
    for(int i=20;i>=0;i--){
        if(rmq[a][i]!=rmq[b][i]){
//            debug(a,b,rmq[a][i],rmq[b][i]);
            a=rmq[a][i];b=rmq[b][i];
        }
    }
    return rmq[a][1];
}

signed main() {_
    int n,m,q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; ++i) {
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    dfs(1, 1);
//    for (auto[c,d] : bridge) cerr << c<< "," << d << " ";cerr<<endl;
//    for (int i = 1; i <= n; ++i) {
//        cerr << "{"<<i<<","<<bl[i]<<"}";
//    }
    vector<vector<pair<int, int>>>nadj(bcccnt+5);
    for (auto i : bridge){
        if (i.first == i.second) continue;
        int we;
        for (auto [vvv,www] : adj[i.first]) {
            if (vvv==i.second){
                we = www;
                break;
            }
        }
//        debug(i.first, i.second, bl[i.first],bl[i.second],we);
        nadj[bl[i.first]].push_back({bl[i.second], we});
        nadj[bl[i.second]].push_back({bl[i.first], we});
    }
    for (auto &i : rmq[bl[1]]) {
        i = bl[1];
    }
//    fill(rmq[bl[1]], rmq[1]+20, bl[1]);
    for (auto &i : st) {
        for (auto &j : i) {
            j = INT_MAX;
        }
    }
    vector<bool>temp(maxn);
    dfs3(bl[1], bl[1], temp, nadj);
    for (int i = 0; i < q; ++i) {
        int s,e;
        cin >> s >> e;
        if (bl[s]==bl[e]){
            cout << -1 << endl;
            continue;
        }
        auto retlca = lca(bl[s], bl[e]);
//        debug(bl[s],bl[e],retlca);
        int ans = INT_MAX;
        int b =bl[s];
        int jump=dep[bl[s]]-dep[retlca];
//        debug(jump);
        for(int i=20;i>=0;i--){
            if(jump&(1<<i)){
//                debug(i,b,st[b][i+1]);
                ans=min(st[b][i+1],ans);
                b = rmq[b][i+1];
            }
        }
        b = bl[e];
        jump=dep[bl[e]]-dep[retlca];
        for(int i=20;i>=0;i--){
            if(jump&(1<<i)){
//                debug(i,b,st[b][i+1]);
                ans=min(st[b][i+1],ans);
                b = rmq[b][i+1];
            }
        }
        cout << ans << endl;
//        vector<bool>visited(bcccnt+5);
//        vector<int>dis(bcccnt+5,INT_MAX);
//        dfs2(bl[s], bl[e], dis, visited, nadj);
//        debug(bl[s],bl[e]);
//        OI(AI(dis));
//        OI(bl,bl+10);
//        cout << dis[bl[e]] << endl;
    }
    return 0;
}
