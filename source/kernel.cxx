using uint8  = unsigned char;
using uint16 = unsigned short;
using uint32 = unsigned int;
using uint64 = unsigned long;

using int8   = char;
using int16  = short;
using int32  = int;
using int64  = long;

extern "C" void _start() {
    auto vram = reinterpret_cast<uint16*>(0xB8000);
    // Print 'KERNEL'.
    vram[0] = 0x9F4B; vram[1] = 0x9F45; vram[2] = 0x9F52; vram[3] = 0x9F4E; vram[4] = 0x9F45; vram[5] = 0x9F4C;
    while(true) {
    }
}

