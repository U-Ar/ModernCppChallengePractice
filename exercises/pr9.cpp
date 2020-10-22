using namespace std;
#include<iostream>
#include<vector>
typedef long long ll;

int main() {
    ll N; 
    cin >> N;
    vector<pair<ll,ll>> factor;
    ll f = 2;
    while (N > 1) {
        ll c = 0;
        while (N % f == 0) {
            N = N / f;
            c++;
        }
        if (c != 0) factor.push_back(make_pair(f,c));
        f++;
    }
    for (ll i = 0; i < factor.size(); i++) {
        cout << factor[i].first << " : " << factor[i].second << endl;
    }
}