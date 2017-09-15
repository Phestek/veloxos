#include "terminal/terminal.hxx"

extern "C" void _start() {
    velox::Terminal terminal{80, 25};
    terminal.set_background_color(velox::Bios_Color::LIGHT_BLUE)
            .set_foreground_color(velox::Bios_Color::WHITE)
            .clear()
            .print("VeloxOS - build 0012\n");
    while(true) {
    }
}
