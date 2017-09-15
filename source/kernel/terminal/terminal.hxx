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

    class Terminal {
    public:
        Terminal(const uint16 width, const uint16 height) noexcept;

        Terminal(const Terminal&) = delete;
        Terminal(Terminal&&) = delete;
        Terminal& operator=(const Terminal&) = delete;
        Terminal& operator=(Terminal&&) = delete;

        void set_background_color(const Bios_Color color) noexcept;
        void set_foreground_color(const Bios_Color color) noexcept;
        void set_color(const uint16 color) noexcept;
        uint16 get_color() const noexcept;

        void set_cursor_position(const uint16 x, const uint16 y) noexcept;

        void clear() noexcept;

        void print(const char* fmt, ...) noexcept;

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
