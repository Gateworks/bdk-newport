# ***********************license start***********************************
# Copyright (c) 2003-2017  Cavium Inc. (support@cavium.com). All rights
# reserved.
#
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#   * Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#   * Redistributions in binary form must reproduce the above
#     copyright notice, this list of conditions and the following
#     disclaimer in the documentation and/or other materials provided
#     with the distribution.
#
#   * Neither the name of Cavium Inc. nor the names of
#     its contributors may be used to endorse or promote products
#     derived from this software without specific prior written
#     permission.
#
# This Software, including technical data, may be subject to U.S. export
# control laws, including the U.S. Export Administration Act and its
# associated regulations, and may be subject to export or import
# regulations in other countries.
#
# TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS PROVIDED "AS IS"
# AND WITH ALL FAULTS AND CAVIUM INC. MAKES NO PROMISES, REPRESENTATIONS OR
# WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE, WITH RESPECT
# TO THE SOFTWARE, INCLUDING ITS CONDITION, ITS CONFORMITY TO ANY
# REPRESENTATION OR DESCRIPTION, OR THE EXISTENCE OF ANY LATENT OR PATENT
# DEFECTS, AND CAVIUM SPECIFICALLY DISCLAIMS ALL IMPLIED (IF ANY) WARRANTIES
# OF TITLE, MERCHANTABILITY, NONINFRINGEMENT, FITNESS FOR A PARTICULAR
# PURPOSE, LACK OF VIRUSES, ACCURACY OR COMPLETENESS, QUIET ENJOYMENT,
# QUIET POSSESSION OR CORRESPONDENCE TO DESCRIPTION. THE ENTIRE  RISK
# ARISING OUT OF USE OR PERFORMANCE OF THE SOFTWARE LIES WITH YOU.
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
CC_thunder = aarch64-thunderx-linux-gnu-gcc
STRIP_thunder = aarch64-thunderx-linux-gnu-strip

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
all: bdk-lua-x86 bdk-lua-thunder


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

