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


const ll mod = 998244353;

ll mabs(long long a) { //轉成 0 <= a < mod的形式
    return (a % mod + mod) % mod;
}
ll madd(long long a, long long b) { // a + b
    return mabs(a % mod + b % mod);
}
ll mmin(long long a, long long b) { // a - b
    return mabs(a % mod - b % mod);
}
ll mmul(long long a, long long b) {
    return mabs((a % mod)*(b % mod));
}


ll mpow(ll a, ll k) {
    ll ans = 1;
    for (int i = 1; i <= k; i<<=1) {
        if (k & i)ans = mmul(a, ans);
        a = mmul(a, a);
    }
    return ans;
}

signed main() {_
    ll ans = 0;
    vector<ll>twos(105,0);
    vector<ll>fives(105,0);
    ll n;
    cin >> n;
    ll twopower = mpow(2, n-1);
    ll zerocount = 1;
    map<ll, ll>curtwo;
    map<ll, ll>curfive;
    for (int i = 1; i <= n; ++i) {
        ll cur;
        cin >> cur;
        if(cur){
        while (!(cur%10)) {
            ans = madd(ans, twopower);
            cur/=10;
        }
        while (!(cur%5)) {
            fives[i]++;
            cur/=5;
        }
        while (!(cur%2)) {
            twos[i]++;
            cur/=2;
        }
            
        }
        debug(twos[i],fives[i]);
        if (twos[i]){
//            cerr << "twos\n";
            map<ll, ll>temp;
            for (auto j = curtwo.begin(); j != curtwo.end(); ++j) {
                auto [v, w] = *j;
//                debug(v,w);
                temp[v+twos[i]] = madd( temp[v+twos[i]] , w);
            }
            for (auto [v,w] : temp) curtwo[v]=madd(w,curtwo[v]);
            curtwo[twos[i]] = madd(curtwo[twos[i]], zerocount);
            for (auto [v, w] : curfive) {
                ans = madd(ans,mmul (mmul(min(v,twos[i]) , w) , mpow(2, n-i)));
                if (v > twos[i]) curfive[v-twos[i]] = madd(curfive[v-twos[i]], w);
                if (v == twos[i]) zerocount = madd(zerocount, w);
                if (v < twos[i]) curtwo[twos[i]-v] = madd(curtwo[twos[i]-v], w);
            }
            
        }
        else if (fives[i]) {
//            cerr << "fives\n";
            map<ll, ll>temp;
            for (auto j = curfive.begin(); j != curfive.end(); ++j) {
                auto [v, w] = *j;
//                debug(v,w);
                temp[v+fives[i]] = madd( temp[v+fives[i]] , w);
            }
            for (auto [v,w] : temp) curfive[v]=madd(w,curfive[v]);
            curfive[fives[i]] = madd(curfive[fives[i]], zerocount);
            for (auto [v, w] : curtwo) {
                ans = madd(ans,mmul (mmul(min(v,fives[i]) , w) , mpow(2, n-i)));
                if (v > fives[i]) curtwo[v-fives[i]] = madd(curtwo[v-fives[i]], w);
                if (v == fives[i]) zerocount = madd(zerocount, w);
                if (v < fives[i]) curfive[fives[i]-v] = madd(curfive[fives[i]-v], w);
            }
            
        }
        else {
//            cerr << "else\n";
            zerocount = mmul(zerocount,2);
            for (auto &i : curtwo) i.second = mmul(i.second, 2);
            for (auto &i : curfive) i.second = mmul(i.second, 2);
        }
//        ll fff=zerocount;
//        cerr << "curtwo: ";
//        for (auto [t,y] : curtwo) {cerr << "{"<<t<<","<<y<<"} ";fff+=y;}
//        cerr << "\ncurfive: ";
//        for (auto [t,y] : curfive) {cerr << "{"<<t<<","<<y<<"} ";fff+=y;}
//        cerr<<endl;
//        debug(ans, zerocount, fff);
//        cerr<<endl;

    }

    cout << ans%mod << endl;
    return 0;
}
