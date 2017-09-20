#pragma once

#include "utils/integer.hxx"

namespace velox {

    struct Frame_Trap {
        uint64 r15;
        uint64 r14;
        uint64 r13;
        uint64 r12;
        uint64 r11;
        uint64 r10;
        uint64 r9;
        uint64 r8;
        uint64 rbp;
        uint64 rdi;
        uint64 rsi;
        uint64 rdx;
        uint64 rcx;
        uint64 rbx;
        uint64 rax;
        uint64 rsp;
        uint64 rip;
        uint64 segment_cs;
    };

    extern "C" void int_00_division_error_handler(Frame_Trap* frame_trap) noexcept;

}
