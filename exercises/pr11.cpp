using namespace std;
#include<iostream>
#include<vector>
#include<string>
typedef long long ll;

int main() {
    vector<string> s1 = 
    {"","I","II","III","IV","V","VI","VII","VIII","IX"};
    vector<string> s2 =
    {"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
    vector<string> s3 = 
    {"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
    vector<string> s4 =
    {"","M", "MM", "MMM"};

    int N;
    cin >> N;
    if (N <= 0 || N >= 4000) {
        cout << "Impossible\n";
        return 0;
    } else {
        cout << s4[N/1000];
        N = N % 1000;
        cout << s3[N/100];
        N = N % 100;
        cout << s2[N/10];
        N = N % 10;
        cout << s1[N];
        cout << endl;
    }
}