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

signed main() {_
    int t;
    cin >> t;
    ll ans = 0;
    for (int i = 0; i < t; ++i) {
        string type;
        cin >> type;
        if (type == "CLEAR") {
            ans = 0;
            continue;
        }
        else if (type == "OUTPUT") {
            cout << ans << endl;
            continue;
        }
        else if (type == "ADD"){
            int k;
            cin >> k;
            ans+=k;
            if (abs(ans) > 1e9) {
                cout << "ERROR" << endl;
                ans = 0;
            }
        }
        else if (type == "MINUS") {
            int k;
            cin >> k;
            ans-=k;
            if (abs(ans) > 1e9) {
                cout << "ERROR" << endl;
                ans = 0;
            }
        }
        else if (type == "MULTIPLY") {
            ll k;
            cin >> k;
            ans*=k;
            if (abs(ans) > 1e9) {
                cout << "ERROR" << endl;
                ans = 0;
            }
        }
        else if (type == "MOD") {
            ll k;
            cin >> k;
            if (ans < 0) {
                cout << "ERROR" << endl;
                ans = 0;
            }
            else ans %= k;
        }
        
    }
    return 0;
}
