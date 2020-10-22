using namespace std;
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cctype>
#include<numeric>

void check_ISBN(string& s) {
    if (s.size() != 10 || !(all_of(s.begin(),s.end(),
    [](char ch) {return isdigit(ch);}))) {
        cout << "Invalid Sequence.\n";
        return ;
    }
    int w = 10;
    int sum = accumulate(s.cbegin(),s.cend(),0,
    [&w](int const total, char const c) {
        return total + (w--)*(c-'0');
    });
    if (sum % 11 == 0) {
        cout << "Valid ISBN\n";
    } else {
        cout << "Invalid ISBN\n";
    }
    
}

int main() {
    string s;
    cin >> s;
    check_ISBN(s);


}