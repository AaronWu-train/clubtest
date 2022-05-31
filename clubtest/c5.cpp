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

struct node{
    ll x;
    ll y;
    ll s;
};
bool cmp(node &a, node &b){
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}
vector<ll>bit(500005,0);

ll p,n,m,k;

vector<ll> d;
ll getid(ll x) {
    return lower_bound(AI(d), x) - d.begin() + 1;
}

void update(ll pos, ll x) {
    for (ll i = pos; i <= 500005; i+=(i&-i)) {
        bit[i] = max(bit[i], x);
    }
}
ll query(ll pos) {
    ll ret = 0;
    for (ll i = pos; i > 0; i-=(i&-i)) {
        ret = max(ret, bit[i]);
    }
    return ret;
}

signed main() {_
    cin >> p >> n >> m >> k;
    vector<node> arr;
    for (int i = 0; i < k; ++i) {
        node temp;
        cin >> temp.x >> temp.y >> temp.s;
        d.push_back(temp.y);
        arr.push_back(temp);
    }
    d.push_back(1);
    sort(AI(d));
    d.erase(unique(AI(d)),d.end());
    sort(AI(arr),cmp);
    update(getid(1), p);
    for (auto &i : arr) {
        auto ret = query(getid(i.y));
        ll ans = 0;
        if (ret + i.x + i.y - 2 >= i.s) ans = ret + i.s;
        else ans = ret;
//        debug(i.x, i.y, i.s, ret, ans);
        update(getid(i.y), ans);
    }
    cout << query(500000) + n + m - 2<< endl;
    return 0;
}
