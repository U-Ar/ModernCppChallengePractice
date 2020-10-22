using namespace std;
#include<iostream>
#include<vector>
#include<cmath>
typedef long long ll;

ll sum_proper_divisors(ll const number) {
    ll result = 1;
    ll const root = static_cast<ll>(sqrt(number));
    for (ll i = 2; i <= root; i++) {
        if (number % i == 0) {
            if (i == number/i) result += i;
            else result += i + number/i;
        }
    }
    return result;
}

int main() {
    ll N = 100000;
    

    for (ll i = 1; i <= N; i++) {
        ll a = sum_proper_divisors(i);
        if (sum_proper_divisors(a) == i && i < a) {
            cout << i << " " << a << endl;
        }
    }

    

}