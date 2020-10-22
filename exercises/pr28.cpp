#include<iostream>
#include<sstream>
#include<string>
#include<algorithm>
#include<iterator>
#include<cmath>
#include<cassert>
#include<array>
#include<vector>
#include<iomanip>
#include<locale>

int max(int a, int b) {
    return a >= b ? a : b;
}
int min(int a, int b) {
    return a <= b ? a : b;
}

std::string longest_palindrome(std::string s)
{
    std::vector<int> rad(2*s.size());
    int i, j, k;
    for (i=0,j=0; i < 2*s.size(); i+=k, j=max(j-k,0)) {
        while (i-j >= 0 && i+j+1 < 2*s.size() && s[(i-j)/2] == s[(i+j+1)/2]) j++;
        rad[i] = j;
        for (k=1; i-k>=0 && rad[i]-k>=0 && rad[i-k] != rad[i]-k; ++k) {
            rad[i+k] = min(rad[i-k], rad[i]-k);
        }
    }
    int maxr = -1, maxi = -1;
    for (int i = 0; i < rad.size(); i++) {
        if (rad[i] > maxr) {
            maxr = rad[i]; maxi = i;
        }
    }
    if (maxr % 2 == 1) return s.substr(maxi/2-maxr/2, maxr);
    return s.substr(maxi/2-maxr/2+1, maxr);
}


int main() 
{
    std::cout << longest_palindrome("sahararahnide") << std::endl;
    std::cout << longest_palindrome("levels") << std::endl;
    std::cout << longest_palindrome("s") << std::endl;
    std::cout << longest_palindrome("scc") << std::endl;
}
