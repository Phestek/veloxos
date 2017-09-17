#include "hal/ports.hxx"
#include "idt/interrupt_descriptor_table.hxx"
#include "terminal/terminal.hxx"

namespace velox {

    extern "C" void _start() {
        Interrupt_Descriptor_Table idt{};

        Terminal terminal{80, 25};
        terminal.set_background_color(velox::Bios_Color::LIGHT_BLUE)
                .set_foreground_color(velox::Bios_Color::WHITE)
                .clear()
                .print("VeloxOS - build 0019\n");

        while(true) {
        }
    }

}
