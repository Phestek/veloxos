#! /usr/bin/env python2

import os

image_size = 0
image_size += os.stat('build/kernel.o').st_size
image_size += os.stat('build/bootloader/stage2.o').st_size
image_size_in_segments = (image_size + 511) / 512
with open('build/bootloader/stage1.o', 'rb+') as f:
    d = f.read()
    i = d.index('\xCC\xCC')
    d = bytearray(d)
    d[i + 0] = image_size_in_segments & 0x00FF
    d[i + 1] = image_size_in_segments & 0xFF00
    f.seek(0)
    f.write(d)
