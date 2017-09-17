#include "interrupt_handlers.hxx"

#include "terminal/terminal.hxx"

namespace velox {

    extern "C" void int_00_division_error_handler([[maybe_unused]] Frame_Trap* frame_trap) noexcept {
        Terminal terminal{80, 25};
        terminal.set_background_color(Bios_Color::RED)
                .set_foreground_color(Bios_Color::WHITE)
                .clear()
                .print("Interrupt 0x00: Division error.\n");
        while(true);
    }

}
