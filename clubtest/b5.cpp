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

vector<int>twos(15);
vector<int>fives(15);
const int mod = 998244353;
ll ans = 0;

int mabs(long long a) { //轉成 0 <= a < mod的形式
    return (a % mod + mod) % mod;
}
int madd(long long a, long long b) { // a + b
    return mabs(a % mod + b % mod);
}
int mmin(long long a, long long b) { // a - b
    return mabs(a % mod - b % mod);
}
int mmul(long long a, long long b) {
    return mabs((a % mod)*(b % mod));
}


ll pow(ll a, ll k) {
    int ans = 1;
    for (int i = 1; i <= k; i<<=1) {
        if (k & i)ans = mmul(ans,a);
        a = mmul(a, a);
    }
    return ans;
}

pair<map<ll, ll>,map<ll, ll>> fun(int l, int r, ll &zerosol, ll &curzero){
    map<ll, ll>curtwo;
    map<ll, ll>curfive;
    if (l==r) {
        if (twos[l] >= fives[l]) {
            curzero = madd( min(twos[l] , fives[l]), curzero);
            curtwo[twos[l] - fives[l]] ++;
//            curfive[0]++;
        }
        else {
            curzero = madd( min(twos[l] , fives[l]) , curzero);
            curfive[fives[l] - twos[l]] ++;
//            curtwo[0]++;
        }
        return {curtwo,curfive};
    }
    int mid = (l+r)/2;
    ll ta=0,tb=0;
    ll azerosol = 0;
    ll bzerosol = 0;
    auto [A2, A5] = fun(l, mid, azerosol, ta);
    auto [B2, B5] = fun(mid+1, r,bzerosol, tb);
    curzero = madd(curzero, mmul(ta, pow(2,r-mid)));
    curzero = madd(curzero, mmul(tb, pow(2,mid-l+1)));
    for (auto [v2, w2] : A2) {
        for (auto [v5, w5] : B5) {
            debug(v2,w2,v5,w5);
            curzero = madd(curzero, mmul(min(v2,v5), mmul(w2, w5)));
            if (v2 > v5) {
                curtwo[v2-v5] = madd(curtwo[v2-v5], mmul(w2, w5));
            }
            if (v2==v5)zerosol++;
            if (v5 > v2) {
                curfive[v5-v2] = madd(curfive[v5-v2], mmul(w2, w5));
            }
        }
    }
    cerr << "====\n";
    for (auto [v2, w2] : B2) {
        for (auto [v5, w5] : A5) {
            debug(v2,w2,v5,w5);
            curzero = madd(curzero, mmul(min(v2,v5), mmul(w2, w5)));
            if (v2 > v5) {
                curtwo[v2-v5] = madd(curtwo[v2-v5], mmul(w2, w5));
            }
            if (v2==v5)zerosol++;
            if (v5 > v2) {
                curfive[v5-v2] = madd(curfive[v5-v2], mmul(w2, w5));
            }
        }
    }
    for (auto [v2, w2] : A2) curtwo[v2] = madd(curtwo[v2], mmul(w2, azerosol+1));
    for (auto [v2, w2] : B2) curtwo[v2] = madd(curtwo[v2], mmul(w2, bzerosol+1));
    for (auto [v5, w5] : A5) curfive[v5] = madd(curfive[v5],mmul(w5, azerosol+1));
    for (auto [v5, w5] : B5) curfive[v5] = madd(curfive[v5],mmul(w5, bzerosol+1));
    
    for (auto [av2, aw2] : A2) {
        for (auto [bv2, bw2] : B2) {
            curtwo[av2+bv2] = madd(curtwo[av2+bv2] , mmul(aw2, bw2));
        }
    }
    for (auto [av2, aw2] : A5) {
        for (auto [bv2, bw2] : B5) {
            curtwo[av2+bv2] = madd(curtwo[av2+bv2] , mmul(aw2, bw2));
        }
    }
    for (auto [e,r] : curtwo) {
        cout << e << " " << r << endl;
    }
    debug(l,r,curzero,mmul(ta, pow(2,r-mid)),mmul(tb, pow(2,mid-l+1)));
    return {curtwo,curfive};
}

signed main() {_
    int n;
    cin >> n;
//    ll twopower = pow(2, n-1);
    for (int i = 1; i <= n; ++i) {
        ll cur;
        cin >> cur;
//        while (!(cur%10)) {
//            ans = madd(ans, twopower);
//            cur/=10;
//        }
        while (!(cur%5)) {
            fives[i]++;
            cur/=5;
        }
        while (!(cur%2)) {
            twos[i]++;
            cur/=2;
        }
        
    }
    OI(AI(twos));
    OI(AI(fives));
    
    ll temp = 0;
    fun(1, n,temp, ans);
    cout << ans << endl;
    return 0;
}
