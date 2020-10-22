using namespace std;
#include<iostream>
typedef long long ll;

ll gcd(ll a, ll b) {
    if (a == 0) return b;
    else return gcd(b % a, a);
}

int main() {
    ll a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
}