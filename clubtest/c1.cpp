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

int n;
bool check(int d, vector<pair<int, int>>& arr) {
    for (int i = 0; i < n-1; ++i) {
        auto [curl, curr] = arr[i];
//        curr+=d;
//        curl-=d;
        auto [newl, newr] = arr[i+1];
//        debug(d,curl,curr,newl,newr);
        if (curr + d < newl || curl - d > newr) return 0;
        
        arr[i].first = max(newl-d, curl);
        arr[i].second = min (newr+d, curr);
        arr[i+1].first = max(curl-d, newl);
        arr[i+1].second = min(curr+d, newr);
        
    }
//    for (auto i : arr) cerr << i.first << " "; cerr << endl;
//    for (auto i : arr) cerr << i.second << " "; cerr << endl;

    return 1;
}

signed main() {_
    cin >> n;
    vector<pair<int, int>> arr;
    for (int i = 0; i < n; ++i) {
        int t1, t2;
        cin >> t1 >> t2;
        arr.push_back({t1,t2});
    }
//    for (auto i : arr) cerr << i.first << " "; cerr << endl;
//    for (auto i : arr) cerr << i.second << " "; cerr << endl;

    int l = 0, r= 1e9+1;
    while (l < r) {
        int mid = (l+r)/2;
        auto temp = arr;
        if (check(mid, temp)) {
            r = mid;
        } else {
            l = mid+1;
        }
    }
    check(l, arr);
    cout << l << endl;
    for (auto i : arr) {
        cout << i.first << " ";
    }
    cout << endl;
    return 0;
}
