#include<iostream>
#include<array>
#include<string>

class IPv4 {
    std::array<int,4> address;
public:
    IPv4() : address(std::array<int, 4>{0,0,0,0}) {}
    IPv4(std::array<int,4>& ad) : address(ad) {}
    ~IPv4() {}

    void read() {
        std::string s;
        std::cin >> s;
        for (int i = 0; i < 3; i++) {
            int tail = s.find_first_of('.');
            int c = std::stoi(s.substr(0,tail));
            address[i] = c;
            s.erase(s.begin(),s.begin()+tail+1);
        }
        address[3] = std::stoi(s);
    }

    void write() {
        std::string s;
        s += std::to_string(address[0]);
        for (int i = 1; i < 4; i++) {
            s += ".";
            s += std::to_string(address[i]);
        }
        std::cout << s << std::endl;
    }
};

int main() {
    IPv4 ad;
    ad.read();
    ad.write();
}