#include "Utils.hpp"
#include <cctype>

// to keep track of global post time
long long GLOBAL_POST_TIME = 0;

// convert string to lowercase
string convert_lower(string s) {
    for(char &c : s) c = tolower(c);
    return s;
}
