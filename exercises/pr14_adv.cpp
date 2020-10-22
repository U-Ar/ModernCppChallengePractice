using namespace std;
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cctype>
#include<numeric>

void check_ISBN13(string& s) {
    vector<int> isbn(0);
    for (auto itr = s.begin(); itr != s.end(); itr++) {
        int c = *itr - '0';
        if (c >= 0 && c <= 9) isbn.push_back(c);
    }
    if (isbn.size() != 13) {
        cout << "Invalid Sequence.\n";
        return;
    }
    int sum = 0;
    for (int i = 0; i < 12; i++) {
        if (i % 2 == 0) {
            sum += isbn[i];
        } else {
            sum += 3 * isbn[i];
        }
    }
    sum = 10 - sum % 10;
    if (sum == isbn[12]) {
        cout << "Valid ISBN\n";
    } else {
        cout << "Invalid ISBN\n";
    }
}

int main() {
    string s;
    cin >> s;
    check_ISBN13(s);
}