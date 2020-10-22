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

    for (ll i = 8; i <= N-6; i++) {
        if (isprime[i] && isprime[i-6]) {
            cout << i-6 << " and " << i << endl;
        }
    }    
}