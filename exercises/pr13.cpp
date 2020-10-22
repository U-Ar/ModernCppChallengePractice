using namespace std;
#include<iostream>
#include<vector>
#include<string>
#include<cmath>
typedef long long ll;

int main() {
    double a = 1.0, b = sqrt(2)/2.0, t = 0.25, p = 1.0;

    for (int i = 0; i < 10; i++) {
        double tmp = a;
        a = (a+b)/2.0;
        b = sqrt(tmp*b);
        t = t - p * (tmp - a)*(tmp-a);
        p = 2 * p;
    }
    cout << (a+b)*(a+b)/(4*t) << endl;
}