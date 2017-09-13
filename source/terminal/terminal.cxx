#include "terminal.hxx"

namespace velox {

    Terminal::Terminal(const uint16 width, const uint16 height) noexcept
            : _width{width}, _height{height} {
    }

    void Terminal::set_background_color(const Bios_Color color) noexcept {
        _color = static_cast<uint8>(color) << 4 | (_color & 0x0F);
    }

    void Terminal::set_cursor_position(const uint16 x, const uint16 y) noexcept {
        _cursor_x = x;
        _cursor_y = y;
    }

    void Terminal::set_foreground_color(const Bios_Color color) noexcept {
        _color = (_color & 0xF0) | (static_cast<uint8>(color) & 0x0F);
    }

    void Terminal::clear() noexcept {
        const auto clear_char = (_color << 8) | ' ';
        for(uint i = 0; i < static_cast<uint>(_width * _height); ++i) {
            _video_ram[i] = clear_char;
        }
        _cursor_x = 0;
        _cursor_y = 0;
    }

    void Terminal::print(const char c) noexcept {
        switch(c) {
            case '\n': {
                _cursor_x = 0;
                ++_cursor_y;
                break;
            }
            case '\r': {
                _cursor_x = 0;
                break;
            }
            case '\t': {
                _cursor_x += 8 - _cursor_x % 8;
                break;
            }
            default: {
                _video_ram[_cursor_x + _cursor_y * _width] = (_color << 8) | c;
                ++_cursor_x;
            }
        }
        if(_cursor_x >= _width) {
            ++_cursor_y;
            _cursor_x = 0;
        }
    }

    void Terminal::print(const char* s) noexcept {
        while(*s != '\0') {
            print(*s);
            ++s;
        }
    }

}

