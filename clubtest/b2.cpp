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

struct mat{
    int w;
    int h;
    vector<vector<ll>> arr;
    mat(int _h,int _w){
        this->w = _w;
        this->h = _h;
        for(int i=0;i<this->h;i++){
            arr.push_back(vector<ll>(this->w,0));
        }
    }
};

mat operator*(const mat &a,const mat &b){
    assert(a.w==b.h);
    mat re(a.h, b.w);
    for(int i=0;i<re.h;i++){
        for(int j=0;j<re.w;j++){
            for(int k=0;k<b.h;k++){
                re.arr[i][j]+=(1LL*a.arr[i][k]*b.arr[k][j])%mod;
                re.arr[i][j]%=mod;
            }
        }
    }
    return re;
}

mat mpow(mat a, ll n) {
    mat ans(a.h,a.w);
    for (int i = 0; i < 6; ++i) {
        ans.arr[i][i] = 1;
    }
    for (ll i = 1; i <= n; i<<=1) {
        if (i&n) ans = ans*a;
            a = a*a;
        }
    return ans;
}
ll npow(ll a, ll n) {
    ll ans = 1;
      for (ll i = 1; i <= n; i*=2) {
        if (i&n) ans = ans*a%mod;
        a = a*a%mod;
      }
      return ans%mod;
}


signed main() {_
    ll t;
    cin >> t;
    string s;
    cin >> s;
    int onecount = 0;
    for (auto i : s) {
        if (i=='1') onecount++;
    }
    
    if (onecount == 1) {
        cout << npow(5ll, t) << endl;
        return 0;
    }
    if (onecount == 3) {
        cout << npow(3ll, t) << endl;
        return 0;
    }
    vector<vector<ll>> temp = {{2,1,1,0,0,1},{1,2,1,1,0,0},{1,1,2,0,1,1},{0,1,0,2,1,0},{0,0,1,1,2,1},{1,0,1,0,1,2}};
    mat a(6,6);
    a.arr = temp;
    mat b(6,1);
    if (s=="10100") b.arr[0][0]=1;
    else if (s=="10010")b.arr[1][0]=1;
    else if (s=="10001")b.arr[2][0]=1;
    else if (s=="01010")b.arr[3][0]=1;
    else if (s=="01001")b.arr[4][0]=1;
    else if (s=="00101")b.arr[5][0]=1;
    auto k = mpow(a, t)*b;
    ll sum=0;
    for (auto i : k.arr) {
        sum = (sum+i[0])%mod;
    }
    cout << sum << endl;
    return 0;
}
