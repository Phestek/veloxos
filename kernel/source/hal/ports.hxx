#pragma once

#include "utils/integer.hxx"

namespace velox {

    void port_out_byte(const uint16 port, const uint8 value) noexcept;
    void port_out_word(const uint16 port, const uint16 value) noexcept;
    void port_out_dword(const uint16 port, const uint32 value) noexcept;

    // TODO: Check correctness of these.
    uint8 port_in_byte(const uint16 port) noexcept;
    uint16 port_in_word(const uint16 port) noexcept;
    uint32 port_in_dword(const uint16 port) noexcept;

}

