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

//using A = B は typedef B Aと同じ
template <class Elem>
using tstring = std::basic_string<Elem, std::char_traits<Elem>, 
                                    std::allocator<Elem> >;
template <class Elem>
using tstringstream = std::basic_stringstream<Elem, std::char_traits<Elem>, 
                                    std::allocator<Elem> >;

template <class Elem>
tstring<Elem> capitalize(tstring<Elem> const & text)
{
    tstringstream<Elem> result;
    bool newWord = true; 
    for (auto const ch : text)
    {
        newWord = newWord || std::ispunct(ch) || std::isspace(ch);
        if (std::isalpha(ch))
        {
            if (newWord)
            {
                result << static_cast<Elem> (std::toupper(ch));
                newWord = false;
            }
            else result << static_cast<Elem> (std::tolower(ch));
        }
        else result << ch;
    }
    return result.str();
}

int main() {
    using namespace std::string_literals;
    assert("The C++ Challengers"s == capitalize("the c++ challengers"s));
    assert("This Is An Example, Should Work"s == 
    capitalize("THIS IS an ExamplE, should wORK!"s));
}
