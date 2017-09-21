MD		:= mkdir -p
RM		:= rm

PROJECT_DIR	:= $(shell dirname $(realpath $(lastword $(MAKEFILE_LIST))))
BUILD_DIR	:= $(PROJECT_DIR)/build

QEMU	:= qemu-system-x86_64

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

.PHONY: all clean qemu libcxx kernel bootloader

all: bootloader kernel libcxx
	printf "Fixing:\t\tsize loaded by stage1\n"
	python2 scripts/fix_stage1_loaded_size.py
	echo Writing to image: $(IMAGE_NAME)
	cat $(FILES_TO_IMAGE) > $(BUILD_DIR)/$(IMAGE_NAME)

clean:
	rm -rf $(BUILD_DIR)/**/*.o

qemu:
	$(QEMU) -drive format=raw,file=$(BUILD_DIR)/$(IMAGE_NAME)
