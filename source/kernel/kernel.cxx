#include "terminal/terminal.hxx"

extern "C" void _start() {
    velox::Terminal terminal{80, 25};
    terminal.set_background_color(velox::Bios_Color::LIGHT_BLUE);
    terminal.set_foreground_color(velox::Bios_Color::WHITE);
    terminal.clear();
    terminal.print("VeloxOS - build 0011\n");

    terminal.print("Percent test:  \t%%\n");
    terminal.print("Character test:\t%c\n", 'c');
    terminal.print("String test:   \t%s\n", "string");
    terminal.print("Integer+ test: \t%d\n", 1234);
    terminal.print("Integer+ test: \t%d\n", 1234);
    terminal.print("Integer0 test: \t%d\n", 0);
    terminal.print("UInteger test: \t%u\n", 4321);

    terminal.print("Mixed test:    \t%% %c %s %d %d %u", 'x', "XXX", 1234, -1234, 4321);

    while(true) {
    }
}
