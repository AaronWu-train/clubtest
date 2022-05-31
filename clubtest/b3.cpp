#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define AI(x) begin(x),end(x)
#define ll long long
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

const ll INF = LLONG_MAX;
vector<pair<ll, ll>>graph[200000];

signed main() {_
    int n,m,k;
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i) {
        int s,u,t,v,w;
        cin >> s >> u >> t >> v >> w;
        graph[s*n+u].push_back(make_pair(t*n+v, w));
        graph[t*n+v].push_back(make_pair(s*n+u, w));
    }
    vector<bool> visited(170000,0);
    vector<ll>dis(170000,INF);
    
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<pair<ll,ll>>> pq;
    dis[1*n+1]=0;
    pq.push({0,1*n+1});
    while(pq.size()){
        auto [w,v] = pq.top();
        pq.pop();
        if(visited[v]) continue;
        visited[v] = 1;
        for(auto [v_2,w_2]:graph[v]){
            if(w+w_2<dis[v_2]){//relaxation
                dis[v_2] = w+w_2;
                pq.push({dis[v_2],v_2});
            }
        }
    }
    ll q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int x,y;
        cin >> x >> y;
        if (dis[x*n+y] == INF) cout << -1 << endl;
        else cout << dis[x*n+y] << endl;
    }
    return 0;
}
