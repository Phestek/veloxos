LIBCXX_CXX_FLAGS := -Ilibcxx/include

LIBCXX_SOURCES := $(shell find libcxx/source -name '*.cxx' -type f)
LIBCXX_SOURCES += $(shell find libcxx/source -name '*.s'   -type f)

LIBCXX_OBJECTS := $(patsubst libcxx/source/%,$(BUILD_DIR)/libcxx/%,$(LIBCXX_SOURCES))
LIBCXX_OBJECTS := $(addsuffix .o,$(LIBCXX_OBJECTS))

$(BUILD_DIR)/libcxx/%.cxx.o: $(PROJECT_DIR)/libcxx/source/%.cxx
	$(CXX) $(CXX_FLAGS) $(LIBCXX_CXX_FLAGS) -c $< -o $@

libcxx: $(LIBCXX_OBJECTS)
	printf "Building:\tlibcxx\n"
	ar rvs $(BUILD_DIR)/libcxx.a $(LIBCXX_OBJECTS)
