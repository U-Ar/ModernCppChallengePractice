using namespace std;
#include<iostream>

int main() {
    int upper_bound, ans = 0;
    cin >> upper_bound;
    for (int i = 1; i <= upper_bound; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            ans += i;
        }
    }
    cout << ans << endl;
}