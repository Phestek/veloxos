#include "cstring.hxx"

namespace std {

    char* strcpy(char* dest, const char* src) noexcept {
        const auto length = strlen(src);
        for(std::size_t i{}; i < length; ++i) {
            dest[i] = src[i];
        }
        dest[length] = '\0';
        return dest;
    }

    char* strncpy(char* dest, const char* src, const std::size_t count) noexcept {
        std::size_t i{};
        for(; src[i] != '\0' && i < count; ++i) {
            dest[i] = src[i];
        }
        if(i < count) {
            for(; i < count; ++i) {
                dest[i] = '\0';
            }
        }
        return dest;
    }

    std::size_t strlen(const char* s) noexcept {
        std::size_t len{};
        for(std::size_t i{}; s[i] != '\0' ; ++i) {
            ++len;
        }
        return len;
    }

    int strcmp(const char* left, const char* right) noexcept {
        std::size_t i{};
        while(left[i] == right[i]) {
            ++i;
        }
        return left[i] - right[i];
    }

    int strncmp(const char* left, const char* right, const std::size_t count) noexcept {
        std::size_t i{};
        while(left[i] == right[i] && i < count) {
            ++i;
        }
        return left[i] - right[i];
    }

    const char* strchr(const char* str, const int c) noexcept {
        const auto length = strlen(str);
        for(std::size_t i{}; i < length; ++i) {
            if(str[i] == static_cast<char>(c)) {
                return str + i;
            }
        }
        return nullptr;
    }

    char* strchr(char* str, const int c) noexcept {
        const auto length = strlen(str);
        for(std::size_t i{}; i < length; ++i) {
            if(str[i] == static_cast<char>(c)) {
                return str + i;
            }
        }
        return nullptr;
    }

    const char* strrchr(const char* str, const int c) noexcept {
        auto length = strlen(str);
        while(length--) {
            if(str[length] == static_cast<char>(c)) {
                return str + length;
            }
        }
        return nullptr;
    }

    char* strrchr(char* str, const int c) noexcept {
        auto length = strlen(str);
        while(length--) {
            if(str[length] == static_cast<char>(c)) {
                return str + length;
            }
        }
        return nullptr;
    }

    const void* memchr(const void* ptr, const int byte, const std::size_t count) noexcept {
        auto ptr_bytes = static_cast<const unsigned char*>(ptr);
        for(std::size_t i{}; i < count; ++i) {
            if(ptr_bytes[i] == static_cast<unsigned char>(byte)) {
                return static_cast<const unsigned char*>(ptr) + i;
            }
        }
        return nullptr;
    }

    void* memchr(void* ptr, const int byte, const std::size_t count) noexcept {
        auto ptr_bytes = static_cast<unsigned char*>(ptr);
        for(std::size_t i{}; i < count; ++i) {
            if(ptr_bytes[i] == static_cast<unsigned char>(byte)) {
                return static_cast<unsigned char*>(ptr) + i;
            }
        }
        return nullptr;
    }

    int memcmp(const void* left, const void* right, const std::size_t count) noexcept {
        auto left_bytes  = static_cast<const unsigned char*>(left);
        auto right_bytes = static_cast<const unsigned char*>(right);
        for(std::size_t i{}; i < count; ++i) {
            if(left_bytes[i] > right_bytes[i]) {
                return 1;
            }
            if(left_bytes[i] < right_bytes[i]) {
                return -1;
            }
        }
        return 0;
    }

    void* memset(void* dest, const int fill_byte, const std::size_t count) noexcept {
        auto dest_bytes = static_cast<unsigned char*>(dest);
        for(std::size_t i{}; i < count; ++i) {
            dest_bytes[i] = static_cast<unsigned char>(fill_byte);
        }
        return dest;
    }

    void* memcpy(void* dest, const void* src, const std::size_t count) noexcept {
        auto dest_bytes = static_cast<unsigned char*>(dest);
        auto src_bytes  = static_cast<const unsigned char*>(src);
        for(std::size_t i = 0; i < count; ++i) {
            dest_bytes[i] = src_bytes[i];
        }
        return dest;
    }

    void* memmove(void* dest, const void* src, const std::size_t count) noexcept {
        if(dest == nullptr || src == nullptr) {
            return nullptr;
        }
        if(dest == src) {
            return dest;
        }
        auto dest_bytes = static_cast<unsigned char*>(dest);
        auto src_bytes  = static_cast<const unsigned char*>(src);
        if(dest < src) {
            for(std::size_t i{}; i < count; ++i) {
                dest_bytes[i] = src_bytes[i];
            }
        } else {
            auto i = count;
            while(i--) {
                dest_bytes[i] = src_bytes[i];
            }
        }
        return dest;
    }

}
