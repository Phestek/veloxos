#include "terminal/terminal.hxx"

extern "C" void _start() {
    velox::Terminal terminal{80, 25};
    terminal.set_background_color(velox::Bios_Color::LIGHT_BLUE);
    terminal.set_foreground_color(velox::Bios_Color::WHITE);
    terminal.clear();
    terminal.print("VeloxOS - build 0009\n");

    terminal.print("Percent test:  \t%%\n");
    terminal.print("Character test:\t%c\n", 'c');
    terminal.print("String test:   \t%s\n", "string");
    terminal.print("Integer+ test: \t%d\n", 1234);
    terminal.print("Integer- test: \t%d\n", -123);
    terminal.print("UInteger- test:\t%d\n", 4321);

    while(true) {
    }
}
