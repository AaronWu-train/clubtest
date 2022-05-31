#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;
    bool status;
    if (n%2==1) {
        for (int i = 1; i <= n; ++i) {
            cout << i << endl;
            cin >> status;
            if (status) return 0;
        }
        for (int i = 1; i <= n; ++i) {
            cout << i << endl;
            cin >> status;
            if (status) return 0;
        }
    }
    else{
        for (int i = 1; i <= n; ++i) {
            cout << i << endl;
            cin >> status;
            if (status) return 0;
        }
        for (int i = 2; i <= n; ++i) {
            cout << i << endl;
            cin >> status;
            if (status) return 0;
        }
    }
    
    return 0;
}
