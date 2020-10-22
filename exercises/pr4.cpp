using namespace std;
#include<iostream>
#include<vector>
typedef long long ll;

int main() {
    ll N;
    cin >> N;
    vector<bool> isprime(N,true);
    for (ll i = 2; i <= N; i++) {
        if (isprime[i]) {
            for (ll j = i*2; j <= N; j += i) {
                isprime[j] = false;
            }
        }
    }

    for (ll i = N; i >= 2; i--) {
        if (isprime[i]) {
            cout << i << endl;
            return 0;
        }
    }
    cout << "-1\n";
}