# make ARCH=i386 SMALL=1 DEBUG=1

ARCH ?= amd64
STDLIB = 1
SMALL = 0
DEBUG = 0

ARCHS32 := i386
ARCHS64 := amd64
ARCHS := $(ARCHS32) $(ARCHS64)

CFLAGS += -pipe -Wall -Wextra -fPIC -fno-ident -fno-stack-protector -U _FORTIFY_SOURCE
CFLAGS += -DSTDLIB=$(STDLIB)
ifeq "$(STDLIB)" "0"
#LDFLAGS += -nostartfiles -nodefaultlibs -nostdlib
LDFLAGS += -nostartfiles -e z_start
endif
LDFLAGS += -pie -Wl,-Bsymbolic,--no-undefined,--build-id=none
TARGET := loader foreign_dlopen_demo

ifeq "$(filter $(ARCH),$(ARCHS))" ""
  $(error ARCH='$(ARCH)' is not supported)
endif

ifeq "$(filter $(ARCH),$(ARCHS32))" "$(ARCH)"
  CFLAGS += -m32 -DELFCLASS=ELFCLASS32
else
  CFLAGS += -DELFCLASS=ELFCLASS64
endif

ifeq "$(DEBUG)" "1"
  CFLAGS += -O0 -g
else
  CFLAGS += -fvisibility=hidden
  # Disable unwind info to make prog smaller.
  CFLAGS += -Os -fno-asynchronous-unwind-tables -fno-unwind-tables
  LDFLAGS += -s
endif

ASFLAGS = $(CFLAGS)

OBJS := loader.o z_err.o z_printf.o z_syscalls.o z_utils.o foreign_dlopen.o
OBJS += $(patsubst %.S,%.o, $(wildcard $(ARCH)/*.S))

ifeq "$(SMALL)" "1"
  OBJS := $(filter-out z_printf.%,$(OBJS))
  OBJS := $(filter-out z_err.%,$(OBJS))
  CFLAGS += -DZ_SMALL
endif

.PHONY: clean all

all: $(TARGET)

loader: main.o $(OBJS)

foreign_dlopen_demo: foreign_dlopen_demo.o $(OBJS)

clean:
	rm -rf *.o $(TARGET) */*.o

