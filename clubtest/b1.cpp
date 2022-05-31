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

const int maxn = 200005;
void dfs(int x, bool tf, vector<vector<int>>& graph, vector<bool>&visited, vector<bool>& rec) {
    visited[x] = 1;
    rec[x]=tf;
    for (auto i : graph[x]) {
        if (!visited[i]) {
            dfs(i, !tf, graph, visited, rec);
        }
    }
}
signed main() {_
    int n,q;
    cin >> n >> q;
    vector<vector<int>>graph(maxn);
    for (int i = 0; i < n-1; i++) {
        int u,v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    vector<bool>visited(n+5);
    vector<bool>rec(n+5);
    dfs(1, 1, graph, visited, rec);
    for (int i = 0; i < q; ++i) {
        int x,y;
        cin >> x >> y;
        if (rec[x] == rec[y]) {
            cout << "node" << endl;
        }
        else {
            cout << "edge" << endl;
        }
    }
    return 0;
}
