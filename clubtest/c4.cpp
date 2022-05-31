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
const int mod = 1e9+7;

struct Node{
    ll v = 0, sqv = 0, tag = 0;
    ll size = 1;
    ll rv() {
        return ( v + tag*size%mod ) % mod;
    }
    ll rsqv(){
        return ( sqv + (2*tag*v%mod+mod)%mod + (((tag*tag)%mod)*size)%mod +mod ) % mod;
    }
};

void push(ll x, vector<Node>&st){
    st[2 * x].tag = (st[2 * x].tag + st[x].tag + mod) % mod;
    st[2 * x + 1].tag = ( st[2 * x + 1].tag + st[x].tag  + mod)%mod;
    st[x].sqv = st[x].rsqv();
    st[x].v = st[x].rv();
    st[x].tag = 0;
}

void build(ll l, ll r, ll x, vector<ll>&arr, vector<Node>&st) {
    if (l == r) {
        st[x].v = arr[l];
        st[x].sqv = (arr[l]*arr[l]%mod+mod)%mod;
        st[x].size = 1;
        return;
    }
    auto mid = (r+l)/2;
    build(l, mid, 2*x, arr, st);
    build(mid+1, r, 2*x+1, arr, st);
    st[x].sqv = (st[2 * x].rsqv() + st[2 * x + 1].rsqv() + mod)%mod;
    st[x].v = (st[2 * x].rv() + st[2 * x + 1].rv()+mod)%mod;
    st[x].size = (r-l+1);
}

void modify(ll ql, ll qr, ll v, ll l, ll r, ll x, vector<Node>& st) {
    if(l == ql && r == qr) {
        st[x].tag = (st[x].tag + v + mod)%mod;
        return;
    }
    push(x,st);
    auto mid = (r+l)/2;
    if(qr <= mid)modify(ql, qr, v, l, mid, 2 * x, st);
    else if(mid < ql) modify(ql, qr, v, mid + 1, r, 2 * x + 1, st);
    else {
        modify(ql, mid, v, l, mid, 2 * x, st);
        modify(mid + 1, qr, v, mid + 1, r, 2 * x + 1, st);
    }
    st[x].sqv = (st[2 * x].rsqv() + st[2 * x + 1].rsqv()+mod)%mod;
    st[x].v = (st[2 * x].rv() + st[2 * x + 1].rv()+mod)%mod;
    
}

pair<ll, ll> query(ll ql, ll qr, ll l, ll r, ll x, vector<Node> &st) {
    if(l == ql && r == qr) {
        return make_pair(st[x].rv()%mod, st[x].rsqv()%mod);
    }
    push(x, st);
    auto mid = (r+l)/2;
    if(qr <= mid) return query(ql, qr, l, mid, 2 * x,st);
    else if(mid < ql) return query(ql, qr, mid + 1, r, 2 * x + 1, st);
    else {
        auto p1 = query(ql, mid, l, mid, 2 * x,st);
        auto p2 = query(mid + 1, qr, mid + 1, r, 2 * x + 1,st);
        return make_pair((p1.first + p2.first)%mod, (p1.second + p2.second)%mod);
    }
}

signed main() {_
    int n, q;
    cin >> n >> q;
    vector<ll>arr1(n+5);
    vector<ll>arr2(n+5);
    for (int i = 1; i <= n; ++i) {
        cin >> arr1[i];
        arr2[i] = arr1[i]*arr1[i]%mod;
    }
    vector<Node>st1(4*n);
    
    build(1, n, 1, arr1, st1);
    

    for (int i = 0; i < q; ++i) {
        int type;
        cin >> type;
        if (type == 1) {
            ll l, r, v;
            cin >> l >> r >> v;
            modify(l, r, (v)%mod, 1, n, 1, st1);
        }
        else{
            ll l,r;
            cin >> l >> r;
//            if (l==r){
//                cout << 0 << endl;
//                continue;
//            }
            auto ret1 = query(l, r, 1, n, 1, st1);
            debug(ret1.first,ret1.second);
            debug(r-l+1);
            cout << ( (ret1.second*(r-l+1) )%mod - ((ret1.first)*(ret1.first))%mod +mod)%mod << endl;
        }
    }
    return 0;
}
