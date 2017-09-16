#include "terminal/terminal.hxx"
#include "idt/interrupt_descriptor_table.hxx"
#include "idt/interrupt_handlers.hxx"

namespace velox {

    extern "C" void _start() {
        Interrupt_Descriptor_Table idt{};
        idt.register_interrupt_handler(0x00, int_00_division_error_handler);
        idt.set_idtr();

        Terminal terminal{80, 25};
        terminal.set_background_color(velox::Bios_Color::LIGHT_BLUE)
                .set_foreground_color(velox::Bios_Color::WHITE)
                .clear()
                .print("VeloxOS - build 0014\n");

        const auto a = 2 / 0;

        while(true) {
        }
    }

}
