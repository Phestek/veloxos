#! /usr/bin/env python2

from copy import *
import fnmatch
import os
import subprocess

class Environment:
    def __init__(self, asm, cxx):
        self.asm = asm
        self.cxx = cxx
        self.objects = []

    def add_object(self, lang, source_files, output_file):
        print "Building:\t" + output_file
        self.objects.append(output_file)
        if lang == 'asm':
            cmd = copy(self.asm)
            cmd.extend(source_files)
            cmd.extend(['-o', output_file])
            subprocess.call(cmd)
            return
        if lang == 'cxx':
            cmd = copy(self.cxx)
            cmd.extend(source_files)
            cmd.extend(['-o', output_file])
            subprocess.call(cmd)
            subprocess.call(['strip', output_file])
            return
        raise Exception('Unknown language.')

    def fix_stage1_size(self):
        # TODO: kernel should be loaded by stage2.
        image_size_in_segments = 0
        for i in range(1, len(self.objects)):   # 1st (index 0) object is always stage1.
            image_size_in_segments += os.stat(self.objects[i]).st_size
        image_size_in_segments = (image_size_in_segments + 511) / 512
        with open('build/stage1', 'rb+') as f:
            d = f.read()
            i = d.index('\xBE\xEF')
            d = bytearray(d)
            d[i + 0] = image_size_in_segments & 0x00FF
            d[i + 1] = image_size_in_segments & 0xFF00
            f.seek(0)
            f.write(d)

    def write_to_image(self, image_name):
        print "Writing to:\t" + image_name
        image = []
        for obj in self.objects:
            with open(obj, 'rb') as f:
                d = f.read()
                image.append(d)
                if len(d) % 512 == 0:
                    continue
                padding_size = 512 - len(d) % 512        
                image.append('\0' * padding_size);
        with open(image_name, 'wb') as f:
            f.write(''.join(image))


asm = [ 'nasm', '-f', 'bin' ]
cxx = [
        'g++', '-std=c++17', '-Wall', '-Wextra', '-Wpedantic', '-O0', '-nostdlib', '-nostartfiles', '-masm=intel',
        '-march=x86-64', '-fomit-frame-pointer', '-fno-builtin', '-Isource'
]

env = Environment(asm, cxx)
env.add_object('asm', ['source/bootloader/stage1.asm'], 'build/stage1')
env.add_object('asm', ['source/bootloader/stage2.asm'], 'build/stage2')

# TODO: This is bad.
cxx_sources = []
for root, dirnames, filenames in os.walk('source'):
    for filename in fnmatch.filter(filenames, '*.cxx'):
        cxx_sources.append(os.path.join(root, filename))
env.add_object('cxx', cxx_sources, 'build/kernel')

env.fix_stage1_size()

env.write_to_image('build/floppy.bin')

