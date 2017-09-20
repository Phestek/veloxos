#include "ports.hxx"

namespace velox {

    void port_out_byte(const uint16 port, const uint8 value) noexcept {
        asm("out dx, al\n" :: "d"(port), "a"(value));
    }

    void port_out_word(const uint16 port, const uint16 value) noexcept {
        asm("out dx, ax\n" :: "d"(port), "a"(value));
    }

    void port_out_dword(const uint16 port, const uint32 value) noexcept {
        asm("out dx, eax\n" :: "d"(port), "a"(value));
    }

    uint8 port_in_byte(const uint16 port) noexcept {
        uint8 value{};
        asm("in al, dx\n" :: "a"(value), "d"(port));
        return value;
    }

    uint16 port_in_word(const uint16 port) noexcept {
        uint8 value{};
        asm("in ax, dx\n" :: "a"(value), "d"(port));
        return value;
    }

    uint32 port_in_dword(const uint16 port) noexcept {
        uint8 value{};
        asm("in eax, dx\n" :: "a"(value), "d"(port));
        return value;
    }

}

