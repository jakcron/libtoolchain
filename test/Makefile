# Sources
SRC_DIR = .
OBJS = $(foreach dir,$(SRC_DIR),$(subst .cpp,.o,$(wildcard $(dir)/*.cpp))) $(foreach dir,$(SRC_DIR),$(subst .c,.o,$(wildcard $(dir)/*.c)))

# External dependencies
LIBS = "$(LIBTOOLCHAIN_COMPILE_PATH)/libtoolchain.a"
INCS = -I"$(LIBTOOLCHAIN_INCLUDE_PATH)"

# Compiler Settings
CXXFLAGS = -std=c++11 $(INCS) -D__STDC_FORMAT_MACROS -Wall -Wno-unused-value
CFLAGS = -std=c11 $(INCS) -Wall -Wno-unused-value
ifeq ($(OS),Windows_NT)
	# Windows Only Flags/Libs
	CC = x86_64-w64-mingw32-gcc
	CXX = x86_64-w64-mingw32-g++
	CFLAGS += -Wno-unused-but-set-variable
	CXXFLAGS += -Wno-unused-but-set-variable
	LIBS += -static
else
	UNAME = $(shell uname -s)
	ifeq ($(UNAME), Darwin)
		# MacOS Only Flags/Libs
		CFLAGS += -Wno-unused-private-field
		CXXFLAGS += -Wno-unused-private-field
		LIBS +=
	else
		# *nix Only Flags/Libs
		CFLAGS += -Wno-unused-but-set-variable
		CXXFLAGS += -Wno-unused-but-set-variable
		LIBS +=
	endif
endif

OUTPUT = $(PROJECT_BIN_PATH)/libtoolchain_test

all: build

build: $(OBJS)
	mkdir -p "$(PROJECT_BIN_PATH)"
	$(CXX) $(OBJS) $(LIBS) -o "$(OUTPUT)"

clean:
	rm -rf $(OBJS) "$(OUTPUT)"

.PHONY: clean