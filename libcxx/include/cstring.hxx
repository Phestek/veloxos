#pragma once

#include "cstddef.hxx"

namespace std {

    // TODO: Add: 'strcoll', 'strspn', 'strcspn', 'strpbrk', 'strstr', 'strtok'.

    // String manipulation.

    // Copies one string to another.
    char* strcpy(char* dest, const char* src) noexcept;

    // Copies a certain amount of characters from one string to another.
    char* strncpy(char* dest, const char* src, const std::size_t count) noexcept;

    // String examination.

    // Returns the length of a given string.
    std::size_t strlen(const char* s) noexcept;

    // Compares two strings.
    int strcmp(const char* left, const char* right) noexcept;

    // Compares a certain amount of characters of two strings.
    int strncmp(const char* left, const char* right, const std::size_t count) noexcept;

    // Finds the first occurrence of a character.
    const char* strchr(const char* str, const int c) noexcept;
    char* strchr(char* str, const int c) noexcept;

    // Finds the last occurrence of a character.
    const char* strrchr(const char* str, const int c) noexcept;
    char* strrchr(char* str, const int c) noexcept;

    // Character array manipulation.

    // Searches an array lexicographically for the first occurrence of a character.
    const void* memchr(const void* ptr, const int byte, const std::size_t count) noexcept;
    void* memchr(void* ptr, const int byte, const std::size_t count) noexcept;

    // Compares two buffers lexicographically.
    int memcmp(const void* left, const void* right, const std::size_t count) noexcept;

    // Fills a buffer with a character.
    void* memset(void* dest, const int fill_byte, const std::size_t count) noexcept;

    // Copies one buffer to another.
    void* memcpy(void* dest, const void* src, const std::size_t count) noexcept;

    // Moves one buffer to another.
    void* memmove(void* dest, const void* src, const std::size_t count) noexcept;

}
