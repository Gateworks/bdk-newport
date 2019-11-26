# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

#
# Setup the compile flags
#
CPPFLAGS = -I $(BDK_ROOT) -I $(BDK_ROOT)/liblua -I $(BDK_ROOT)/libbdk -D_GNU_SOURCE -DBDK_BUILD_HOST
CFLAGS = -Wall -Wextra -Wno-unused-parameter -O3 -g -std=gnu99
ASFLAGS = $(CFLAGS)
LDFLAGS = -lm -ldl

# This is needed to avoid using tmpnam, which creates a warning
CPPFLAGS += -DLUA_USE_MKSTEMP

# These are needed for luasocket to compile cleanly
CPPFLAGS += -DLUA_COMPAT_MODULE -DluaL_putchar=luaL_addchar

# Building for x86
CPPFLAGS_x86 =
CFLAGS_x86 =
ASFLAGS_x86 =
LDFLAGS_x86 =
CC_x86 = gcc
STRIP_x86 = strip

# Building for Thunder
CPPFLAGS_thunder =
CFLAGS_thunder =
ASFLAGS_thunder =
LDFLAGS_thunder =
CC_thunder = $(BDK_GCC_PREFIX)-gcc
STRIP_thunder = $(BDK_GCC_PREFIX)-strip
# GCC7 creates a whole bunch of flase warnings with -Wformat-truncation
GCCVERSIONGTEQ7 := $(shell expr $(shell $(CC_thunder) -dumpversion | cut -f1 -d.) \>= 7)
ifeq "$(GCCVERSIONGTEQ7)" "1"
    CFLAGS_thunder += -Wno-format-truncation
endif

#
# These are the directories where source files are found
#
dirs = liblua
dirs += utils/bdk-lua
dirs += utils/bdk-lua/libluasocket

#
# Create a list of all source files
#
src := $(foreach d,$(dirs),$(BDK_ROOT)/$(d)/*.[c])
src := $(wildcard $(src))
src += $(BDK_ROOT)/libbdk-os/bdk-readline.c
src += $(BDK_ROOT)/libbdk-lua/bdk-lua.c
src += $(BDK_ROOT)/libbdk-lua/lbitlib64.c
src += $(BDK_ROOT)/libbdk-lua/readline.c
src += $(BDK_ROOT)/libbdk-lua/rpc-support.c

.DEFAULT: all
all: bdk-lua-x86


define build_rule
obj-$(2)/$$(notdir $(1:%.c=%.o)): $(1) | obj-$(2)
	$$(CC_$(2)) $(CPPFLAGS) $$(CPPFLAGS_$(2)) $$(CFLAGS) $$(CFLAGS_$(2)) -o $$@ -c $$^
endef

define build_arch
obj_$(1) := $$(foreach s,$$(src),obj-$(1)/$$(notdir $$(s:%.c=%.o)))
obj-$(1):
	mkdir obj-$(1)
bdk-lua-$(1): $$(obj_$(1))
	$$(CC_$(arch)) $$(CFLAGS_$(1)) -o $$@ $$^ $$(LDFLAGS) $$(LDFLAGS_$(1))
	$$(STRIP_$(arch)) $$@
endef

$(foreach arch,x86 thunder,\
	$(eval $(call build_arch,$(arch))) \
	$(foreach s,$(src), \
		$(eval $(call build_rule,$(s),$(arch))) \
	) \
)

.PHONY: clean
clean:
	rm -rf bdk-lua-* *.o *.bin obj-*

.PHONY: suid
suid:
	sudo chown root bdk-lua-x86
	sudo chmod +s bdk-lua-x86

