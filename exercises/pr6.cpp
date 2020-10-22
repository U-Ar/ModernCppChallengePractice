using namespace std;
#include<iostream>
#include<vector>
typedef long long ll;

int main() {
    ll N;
    cin >> N;
    for (ll i = 1; i <= N; i++) {
        ll sum = 0;
        for (ll j = 1; j <= i; j++) {
            if (i % j == 0) sum += j;
        }
        if (sum > 2 * i) {
            cout << i << " excess: " << sum - 2 * i << endl;
        }
    }
}