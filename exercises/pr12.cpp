using namespace std;
#include<iostream>
#include<vector>
#include<string>
typedef long long ll;

int main() {
    int N = 1000000;
    vector<int> collatz(N+1,0);
    for (int i = 2; i <= N; i++) {
        int k = i, c = 0;
        while (k >= i && k != 1) {
            if (k % 2 == 0) {
                k = k / 2;
            } else k = k * 3 + 1;
            c++;
        }
        collatz[i] = c + collatz[k];
    }
    int ans = 0, count = 0;
    for (int i = 1; i <= N; i++) {
        if (collatz[i] > count) {
            ans = i;
            count = collatz[i];
        }
    }
    cout << ans << " " << count << endl;
}