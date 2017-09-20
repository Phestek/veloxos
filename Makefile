MD		:= mkdir -p
RM		:= rm

PROJECT_DIR	:= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR	:= $(PROJECT_DIR)/build

ASM		:= nasm -f bin
CXX		:= x86_64-elf-g++
AR		:= x86_64-elf-ar

ASM_FLAGS	:= -f bin
CXX_FLAGS	:= -std=c++17 -O0 -g0 -masm=intel
CXX_FLAGS	+= -Werror -Wall -Wextra -Wpedantic
CXX_FLAGS	+= -ffreestanding -fno-stack-protector -fno-builtin
CXX_FLAGS	+= -nostartfiles -nostdlib -nostdinc -nostdinc++

IMAGE_NAME	?= floppy.bin
FILES_TO_IMAGE	:= $(BUILD_DIR)/bootloader/stage1.o $(BUILD_DIR)/bootloader/stage2.o $(BUILD_DIR)/kernel.o

include bootloader/Makefile
include kernel/Makefile
include libcxx/Makefile

.PHONY: all libcxx kernel bootloader

all: bootloader kernel libcxx
	python2 scripts/fix_stage1_loaded_size.py
	cat $(BUILD_DIR)/bootloader/stage1.o $(BUILD_DIR)/bootloader/stage2.o $(BUILD_DIR)/kernel.o > $(BUILD_DIR)/$(IMAGE_NAME)
	echo "EVERYTHING BUILT SUCCESSFULLY!"
