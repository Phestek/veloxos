#include "hal/ports.hxx"
#include "idt/interrupt_descriptor_table.hxx"
#include "terminal/terminal.hxx"

namespace velox {

    extern "C" void _start() {
        Interrupt_Descriptor_Table idt{};

        Terminal terminal{80, 25};
        terminal.clear();
        terminal << "VeloxOS build 0021\n";

        while(true) {
        }
    }

}
