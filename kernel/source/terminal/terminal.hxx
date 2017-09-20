#pragma once

#include "utils/integer.hxx"

namespace velox {

    enum class Bios_Color : uint8 {
        BLACK,
        BLUE,
        GREEN,
        CYAN,
        RED,
        MAGENTA,
        BROWN,
        LIGHT_GREY,
        DARK_GREY,
        LIGHT_BLUE,
        LIGHT_GREEN,
        LIGHT_CYAN,
        LIGHT_RED,
        LIGHT_MAGENTA,
        YELLOW,
        WHITE
    };

    // TODO: Should inherit from 'std::basic_ostream' / 'std::basic_ios' / 'std::ios_base'.
    class Terminal {
    public:
        Terminal(const uint16 width, const uint16 height) noexcept;

        Terminal(const Terminal&) = delete;
        Terminal(Terminal&&) = delete;
        Terminal& operator=(const Terminal&) = delete;
        Terminal& operator=(Terminal&&) = delete;

        uint16 width() const noexcept;
        uint16 height() const noexcept;

        Terminal& set_background_color(const Bios_Color color) noexcept;
        Terminal& set_foreground_color(const Bios_Color color) noexcept;
        Terminal& set_color(const uint16 color) noexcept;
        uint16 get_color() const noexcept;

        Terminal& set_cursor_position(const uint16 x, const uint16 y) noexcept;
        uint16 cursor_x() const noexcept;
        uint16 cursor_y() const noexcept;

        Terminal& clear() noexcept;

        Terminal& print(const char* fmt, ...) noexcept;

        Terminal& operator<<(const char value);
        Terminal& operator<<(const unsigned char value);
        Terminal& operator<<(const short value);
        Terminal& operator<<(const unsigned short value);
        Terminal& operator<<(const int value);
        Terminal& operator<<(const unsigned int value);
        Terminal& operator<<(const long value);
        Terminal& operator<<(const unsigned long value);
        Terminal& operator<<(const long long value);
        Terminal& operator<<(const unsigned long long value);
        Terminal& operator<<(const bool value);
        Terminal& operator<<(const char* string);

    private:
        void print_char(const char c) noexcept;
        void print_string(const char* s) noexcept;
        void print_int(int64 integer) noexcept;
        void print_uint(uint64 integer) noexcept;

        const uint16 _width;
        const uint16 _height;

        uint16* const _video_ram = reinterpret_cast<uint16*>(0x000B8000);

        uint16 _cursor_x = 0;
        uint16 _cursor_y = 0;
        uint8  _color = static_cast<uint8>(Bios_Color::BLACK) << 4 | static_cast<uint8>(Bios_Color::WHITE);
    };

}
