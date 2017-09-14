#include "terminal/terminal.hxx"

extern "C" void _start() {
    velox::Terminal terminal{80, 25};
    terminal.set_background_color(velox::Bios_Color::LIGHT_BLUE);
    terminal.set_foreground_color(velox::Bios_Color::WHITE);
    terminal.clear();
    terminal.print("VeloxOS v0.0.1\n");

    while(true) {
    }
}

