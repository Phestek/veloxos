#! /usr/bin/env python2

import fnmatch
import os
import sys

sys.path.append(os.path.abspath("./scripts"))
from environment import Environment

asm = [ 'nasm', '-f', 'bin' ]
cxx = [
        'g++', '-std=c++17', '-Wall', '-Wextra', '-Wpedantic', '-O0', '-nostdlib', '-nostartfiles', '-masm=intel',
        '-march=x86-64', '-fomit-frame-pointer', '-fno-builtin', '-fno-stack-protector', '-nostdinc', '-nostdinc++', 
        '-Isource/kernel', '-Isource/libcxx'
]

env = Environment(asm, cxx)
env.add_object('asm', ['source/bootloader/stage1.asm'], 'build/stage1')
env.add_object('asm', ['source/bootloader/stage2.asm'], 'build/stage2')

# TODO: This is bad.
cxx_sources = []
for root, dirnames, filenames in os.walk('source/kernel/'):
    for filename in fnmatch.filter(filenames, '*.cxx'):
        cxx_sources.append(os.path.join(root, filename))
# TODO: libcxx in compiled to kernel, instead being separate library.
for root, dirnames, filenames in os.walk('source/libcxx/'):
    for filename in fnmatch.filter(filenames, '*.cxx'):
        cxx_sources.append(os.path.join(root, filename))
env.add_object('cxx', cxx_sources, 'build/kernel')

env.fix_stage1_size()

env.write_to_image('build/floppy.bin')
