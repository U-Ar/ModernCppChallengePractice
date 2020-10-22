using namespace std;
#include<iostream>
#include<vector>
#include<cstdio>
#include<bitset>
typedef long long ll;

int main() {
    for (int i = 0; i <= 63; i++) {
        cout << bitset<5>(i) << " " << bitset<5>(i ^ i/2) << " " << noshowbase << (i ^ i/2) << endl;
    }
}