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
    map<pair<char,char>, int>child;
};

int dfs(int pos, int i, string& s, vector<node>&arr){
    arr[pos].count++;
    int ans = arr[pos].count;
    if(pos==0)ans=0;
    if (i == s.size()-1) return ans;
    if (arr[pos].child[{s[i+1],s[s.size()-2-i]}] == 0) {
        node b;
        arr.push_back(b);
        arr[pos].child[{s[i+1],s[s.size()-2-i]}] = arr.size()-1;
    }
    auto c =dfs(arr[pos].child[{s[i+1],s[s.size()-2-i]}], i+1, s, arr);
//    debug(s[i+1],s[s.size()-2-i],ans,c);
    return ans + c;
}


signed main() {_
    int n;
    cin >> n;
    vector<node>arr(1);
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        cout << dfs(0, -1, s, arr) << endl;
    }
    return 0;
}
