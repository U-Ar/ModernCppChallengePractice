using namespace std;
#include<iostream>
#include<vector>
typedef long long ll;

int main() {
    for (ll a = 100; a < 1000; a++) {
        ll a1 = a % 10, a2 = (a%100)/10, a3 = a / 100;
        if (a1*a1*a1+a2*a2*a2+a3*a3*a3 == a) {
            cout << a << endl;
        }
    }
}