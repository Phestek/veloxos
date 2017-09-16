#include "terminal.hxx"

#include <cstdarg.hxx>
#include <cstring.hxx>

#include "hal/ports.hxx"

namespace velox {

    Terminal::Terminal(const uint16 width, const uint16 height) noexcept
            : _width{width}, _height{height} {
    }

    Terminal& Terminal::set_background_color(const Bios_Color color) noexcept {
        _color = static_cast<uint8>(color) << 4 | (_color & 0x0F);
        return *this;
    }

    Terminal& Terminal::set_cursor_position(const uint16 x, const uint16 y) noexcept {
        _cursor_x = x;
        _cursor_y = y;
        const auto offset = x + y * _width;
        port_out_byte(0x03D4, 0x0F);    // TODO: Get rid of magic numbers.
        port_out_byte(0x03D5, offset & 0xFF);
        port_out_byte(0x03D4, 0x0E);
        port_out_byte(0x03D5, offset >> 8);
        return *this;
    }

    Terminal& Terminal::set_foreground_color(const Bios_Color color) noexcept {
        _color = (_color & 0xF0) | (static_cast<uint8>(color) & 0x0F);
        return *this;
    }

    Terminal& Terminal::set_color(const uint16 color) noexcept {
        _color = color;
        return *this;
    }

    uint16 Terminal::get_color() const noexcept {
        return _color;
    }

    Terminal& Terminal::clear() noexcept {
        const auto clear_char = (_color << 8) | ' ';
        for(uint i = 0; i < static_cast<uint>(_width * _height); ++i) {
            _video_ram[i] = clear_char;
        }
        set_cursor_position(0, 0);
        return *this;
    }

    Terminal& Terminal::print(const char* fmt, ...) noexcept {
        va_list args{};
        va_start(args, fmt);
        const char* text = fmt;
        while(*text != '\0') {
            if(*text != '%') {
                print_char(*text);
                ++text;
                continue;
            }
            ++text;
            switch(*text) {
                case '%': {
                    print_char('%');
                    ++text;
                    continue;
                }
                case 'c': {
                    ++text;
                    print_char(va_arg(args, int));  // Char instead of int, because of C++'s implicit promotions.
                    continue;
                }
                case 's': {
                    ++text;
                    print_string(va_arg(args, const char*));
                    continue;
                }
                case 'd':
                case 'i': {
                    ++text;
                    print_int(va_arg(args, int));
                    continue;
                }
                case 'u': {
                    ++text;
                    print_uint(va_arg(args, uint64));
                    continue;
                }
                default: {
                    ++text;
                }
            }
        }
        va_end(args);
        return *this;
    }

    void Terminal::print_char(const char c) noexcept {
        switch(c) {
            case '\n': {
                set_cursor_position(0, ++_cursor_y);
                break;
            }
            case '\r': {
                set_cursor_position(0, _cursor_y);
                break;
            }
            case '\t': {
                set_cursor_position(_cursor_x + (8 - _cursor_x % 8), _cursor_y);
                break;
            }
            default: {
                _video_ram[_cursor_x + _cursor_y * _width] = (_color << 8) | c;
                set_cursor_position(++_cursor_x, _cursor_y);
            }
        }
        if(_cursor_x >= _width) {
            set_cursor_position(0, ++_cursor_y);
        }
    }

    void Terminal::print_string(const char* s) noexcept {
        while(*s != '\0') {
            print_char(*s);
            ++s;
        }
    }

    void Terminal::print_int(int64 integer) noexcept {
        if(integer == 0) {
            print_char('0');
            return;
        }
        if(integer < 0) {
            print_char('-');
            integer = -integer;
        }
        const uint max_int64_length{19};
        char number_as_string[max_int64_length]{'\0'};
        std::size_t length{};
        while(integer != 0) {
            number_as_string[length] = integer % 10 + '0';
            integer /= 10;
            ++length;
        }
        // The 'number_as_string' is reversed, so we have to print it back-to-front.
        while(length--) {
            print_char(number_as_string[length]);
        }
    }

    void Terminal::print_uint(uint64 integer) noexcept {
        if(integer == 0) {
            print_char('0');
            return;
        }
        const uint max_uint64_length{20};
        char number_as_string[max_uint64_length]{'\0'};
        std::size_t length{};
        while(integer != 0) {
            number_as_string[length] = integer % 10 + '0';
            integer /= 10;
            ++length;
        }
        // The 'number_as_string' is reversed, so we have to print it back-to-front.
        while(length--) {
            print_char(number_as_string[length]);
        }
    }

}
