KERNEL_CXX_FLAGS := -Ikernel/source -Ilibcxx/include -static -L$(BUILD_DIR) -lcxx

KERNEL_SOURCES := $(shell find kernel/source -name '*.cxx' -type f)
KERNEL_SOURCES += $(shell find kernel/source -name '*.s'   -type f)

KERNEL_OBJECTS := $(patsubst kernel/source/%,$(BUILD_DIR)/kernel/%,$(KERNEL_SOURCES))
KERNEL_OBJECTS := $(addsuffix .o,$(KERNEL_OBJECTS))

$(BUILD_DIR)/kernel/%.cxx.o: $(PROJECT_DIR)/kernel/source/%.cxx
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/kernel/%.s.o: $(PROJECT_DIR)/kernel/source/%.s
	$(CXX) $(CXX_FLAGS) -c $< -o $@

kernel: $(KERNEL_OBJECTS)
	printf "Building:\tkernel\n"
	$(CXX) $(CXX_FLAGS) $(KERNEL_CXX_FLAGS) $(KERNEL_OBJECTS) -o $(BUILD_DIR)/kernel.o
