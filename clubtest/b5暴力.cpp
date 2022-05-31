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


ll mpow(ll a, ll k) {
    int ans = 1;
    for (int i = 1; i <= k; i<<=1) {
        if (k & i)ans = mmul(a, ans);
        a = mmul(a, a);
    }
    return ans;
}

signed main() {_
    vector<ll>twos(105);
    vector<ll>fives(105);
    int n;
    cin >> n;
//    ll twopower = mpow(2, n-1);
//    ll zerocount = 0;
    vector<ll>arr(n);
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }
    int temp = 1;
    for (int i = 0; i <( 1<<n); ++i) {
        for (int j = 0; j < n; ++j) {
            if ((1<<j) & i) {
                temp = mmul(temp, arr[j]);
                while ( !(temp%10)) {
                    ans++;
                    debug(i,j,temp,ans);
                    temp/=10;
                }
            }
        }
    }
    cout << ans << endl;
}
