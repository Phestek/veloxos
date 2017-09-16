#pragma once

#include "utils/attributes.hxx"
#include "utils/integer.hxx"

namespace velox {

    using Interrupt_Handler = void();

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
        void register_interrupt_handler(const uint8 int_number, Interrupt_Handler handler);
        void set_idtr();

    private:
        Idt_Entry _entries[256]{Idt_Entry{}};
    };

}
