#include "interrupt_descriptor_table.hxx"

#define VELOX_IDT_FLAGS(ist, type, dpl, p) (static_cast<uint16>(ist | (type << 8) | (dpl << 13) | (p << 15)))

#define VELOX_IDT_OFFSET_LOW(func)  (static_cast<uint16>(reinterpret_cast<uint64>(func) & 0xFFFF))
#define VELOX_IDT_OFFSET_MID(func)  (static_cast<uint16>(reinterpret_cast<uint64>(func) & 0xFFFF0000))
#define VELOX_IDT_OFFSET_HIGH(func) (static_cast<uint32>(reinterpret_cast<uint64>(func) >> 32))

#define VELOX_IDT_ENTRY(entry, func, ist) { \
        entry.base_low         = VELOX_IDT_OFFSET_LOW(func); \
        entry.segment_selector = 0x0008; \
        entry.flags            = VELOX_IDT_FLAGS(ist, 0x0E, 0x00, 0x01); \
        entry.base_mid         = VELOX_IDT_OFFSET_MID(func); \
        entry.base_high        = VELOX_IDT_OFFSET_HIGH(func); \
    }

namespace velox {

    namespace {

        struct Idt_Ptr {
            uint16 limit{};
            uint64 ptr{};
        } VELOX_PACKED;

    }

    void Interrupt_Descriptor_Table::register_interrupt_handler(const uint8 int_number, Interrupt_Handler handler) {
        VELOX_IDT_ENTRY(_entries[int_number], handler, 0);
    }

    void Interrupt_Descriptor_Table::set_idtr() {
        Idt_Ptr ptr{256 * 16 - 1, reinterpret_cast<uint64>(&_entries)};
        asm("lidt %0" :: "m"(ptr));
    }

}
