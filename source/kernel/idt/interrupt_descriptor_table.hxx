#pragma once

#include "utils/attributes.hxx"
#include "utils/integer.hxx"

namespace velox {

    struct Idt_Entry {
        uint16 base_low{};
        uint16 segment_selector{};
        uint16 flags{};
        uint16 base_mid{};
        uint32 base_high{};
        uint32 reserved{};
    } VELOX_PACKED;

    class Interrupt_Descriptor_Table {
    public:
        Interrupt_Descriptor_Table() noexcept;

    private:
        Idt_Entry _entries[256]{Idt_Entry{}};
    };

}
