#ifndef VELOXOS_TERMINAL_TERMINAL_H
#define VELOXOS_TERMINAL_TERMINAL_H

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

        void set_background_color(const Bios_Color color) noexcept;
        void set_foreground_color(const Bios_Color color) noexcept;

        void set_cursor_position(const uint16 x, const uint16 y) noexcept;

        void clear() noexcept;

        void print(const char c) noexcept;
        void print(const char* s) noexcept;

    private:
        const uint16 _width;
        const uint16 _height;

        uint16* const _video_ram = reinterpret_cast<uint16*>(0x000B8000);

        uint16 _cursor_x = 0;
        uint16 _cursor_y = 0;
        uint8  _color = static_cast<uint8>(Bios_Color::BLACK) << 4 | static_cast<uint8>(Bios_Color::WHITE);
    };

}

#endif //VELOXOS_TERMINAL_TERMINAL_H

