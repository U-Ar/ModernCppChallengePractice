using namespace std;
#include<iostream>
#include<vector>
#include<string>

int c2i(char a) {
    if (a == 'X') return 10;
    int res = static_cast<int>(a-'0');
    if (res >= 0 && res <= 9) return res;
}

int main() {
    string s;
    cin >> s;
    if (s.size() != 10) {
        cout << "Invalid Sequence.\n";
        return 0;
    }

    int check = 0;
    for (int i = 0; i < 9; i++) {
        check += c2i(s[i]) * (10 - i);
    }
    check = 11 - check % 11;
    if (check == c2i(s[9])) {
        cout << "Valid ISBN." << endl;
        return 0;
    }
    cout << "Invalid ISBN." << endl;





}