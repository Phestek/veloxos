#include "interrupt_descriptor_table.hxx"

namespace velox {

    void Interrupt_Descriptor_Table::register_interrupt_handler(const uint8 int_number, Interrupt_Handler handler) {
        VELOX_IDT_ENTRY(_entries[int_number], handler, 0);
    }

    void Interrupt_Descriptor_Table::set_idtr() {
        Idt_Ptr ptr{256 * 16 - 1, reinterpret_cast<uint64>(&_entries)};
        asm("lidt %0" :: "m"(ptr));
    }

}
