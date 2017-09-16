#include "interrupt_handlers.hxx"

#include "terminal/terminal.hxx"

namespace velox {

    void int_00_division_error_handler() {
        Terminal terminal{80, 25};
        terminal.set_background_color(Bios_Color::RED)
                .set_foreground_color(Bios_Color::WHITE)
                .clear()
                .print("Int 0x00: Division by zero.\n");
    }

}
