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
    int count = 0;
    map<int, int>child;
//    int child[26]={0};
};

int dfs(int pos, int i, string& s, vector<node>&arr){
//    debug(s[i]);
    arr[pos].count++;
    int ans = arr[pos].count;
    if (i == s.size()-1) return ans;
    auto nchr = s[i+1]-'a';
    if (arr[pos].child[nchr] == 0) {
        node b;
        arr.push_back(b);
        arr[pos].child[nchr] = arr.size()-1;
    }
    auto b = dfs(arr[pos].child[nchr], i+1, s, arr);
//    debug(s[i],ans,b);
    return ans + b;
}

int dfs2(int pos, int i, string& s, vector<node>&arr){
    arr[pos].count++;
    int ans = arr[pos].count;
    if (i == 0) return ans;
    auto nchr = s[i-1]-'a';
    if (arr[pos].child[nchr] == 0) {
        node b;
        arr.push_back(b);
        arr[pos].child[nchr] = arr.size()-1;
    }
    auto b =dfs2(arr[pos].child[nchr], i-1, s, arr);
//    debug(s[i],ans,b);
    return ans + b;
}

signed main() {_
    int n;
    cin >> n;
    if (n < 1e4) {
        vector<string>a;
        for (int i = 0; i < n; ++i) {
            string b;
            cin >> b;
            a.push_back(b);
            int ret=0;
            for (auto x : a) {
                int i = 0;
                int ans = 0;
                while (i < x.size() and i < b.size() and b[i] == x[i]) {
                    ans++;
                    i++;
                }
                i = 0;
                int nans = 0;
                while (i < x.size() and i < b.size() and b[b.size()-i-1]  == x[x.size()-i-1]) {
                    nans++;
                    i++;
                }
    //            debug(x,b,ans,nans);
                ret+=min(ans, nans);
            }
            cout << ret << endl;
        }
    }
    else {
        vector<node>ffront(26);
        vector<node>bback(26);
        for (int i = 0; i < n; ++i) {
            string s;
            cin >> s;
            auto a = dfs(s[0]-'a', 0, s, ffront);
            auto b = dfs2(s.back()-'a', s.size()-1, s, bback);
            cout << min(a,b) << endl;
        }
    }
    
    return 0;
}
