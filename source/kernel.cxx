#include "terminal/terminal.hxx"

extern "C" void _start() {
    velox::Terminal terminal{80, 25};
    terminal.set_background_color(velox::Bios_Color::LIGHT_BLUE);
    terminal.set_foreground_color(velox::Bios_Color::WHITE);
    terminal.clear();
    terminal.print("VeloxOS v0.0.1");
    terminal.set_cursor_position(30, 12);
    terminal.print("Centered text test.");
    terminal.set_cursor_position(0, 1);
    terminal.print("qwer\ta\t\tasdf\nnot displayed\rthis is displayed\n");
    terminal.print("outofboundstestoutofboundstestoutofboundstestoutofboundstestoutofboundstestoutofboundstest\n");
    terminal.print("Hope this isn't broken.");

    while(true) {
    }
}

