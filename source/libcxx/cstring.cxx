#include "cstring.hxx"

namespace std {

    extern "C" std::size_t strlen(const char* s) {
        std::size_t len{};
        for(int i = 0; s[i] != '\0' ; ++i) {
            ++len;
        }
        return len;
    }

}
