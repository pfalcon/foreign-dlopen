# make ARCH=i386 SMALL=1 DEBUG=1

ARCH ?= amd64
SMALL = 0
DEBUG = 0

ARCHS32 := i386
ARCHS64 := amd64
ARCHS := $(ARCHS32) $(ARCHS64)

CFLAGS += -pipe -Wall -Wextra -fPIC -fno-ident -fno-stack-protector -U _FORTIFY_SOURCE
LDFLAGS += -nostartfiles -nodefaultlibs -nostdlib 
LDFLAGS += -pie -e z_start -Wl,-Bsymbolic,--no-undefined,--build-id=none
TARGET := loader

ifeq "$(filter $(ARCH),$(ARCHS))" ""
  $(error ARCH='$(ARCH)' is not supported)
endif

ifeq "$(filter $(ARCH),$(ARCHS32))" "$(ARCH)"
  CFLAGS += -m32 -DELFCLASS=ELFCLASS32
  ASFLAGS += -m32
else
  CFLAGS += -DELFCLASS=ELFCLASS64
endif

ifeq "$(DEBUG)" "1"
  CFLAGS += -O0 -g
  ASFLAGS += -g
else
  CFLAGS += -fvisibility=hidden
  # Disable unwind info to make prog smaller.
  CFLAGS += -Os -fno-asynchronous-unwind-tables -fno-unwind-tables
  LDFLAGS += -s
endif

OBJS := $(patsubst %.c,%.o, $(wildcard *.c))
OBJS += $(patsubst %.S,%.o, $(wildcard $(ARCH)/*.S))

ifeq "$(SMALL)" "1"
  OBJS := $(filter-out z_printf.%,$(OBJS))
  OBJS := $(filter-out z_err.%,$(OBJS))
  CFLAGS += -DZ_SMALL
endif

.PHONY: clean all

all: $(TARGET)

loader: $(OBJS)

clean:
	rm -rf *.o $(TARGET) */*.o

