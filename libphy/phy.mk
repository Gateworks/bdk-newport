# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

dirs += libphy
dirs += libphy/marvell-88x5123
dirs += libphy/marvell-88x5123/serdes
dirs += libphy/marvell-88x5113
dirs += libphy/marvell-88x5113/serdes/src
dirs += libphy/marvell-88x6141
dirs += libphy/marvell-88x6141/serdes/src
dirs += libphy/marvell-88x3310

#
# The Marvell 88x5123 code requires some extra defines and warning supression
# to compile cleanly. Create a list of all the source this affects and only
# apply the compiler flags to the correct files
#
x5123_dir := libphy/marvell-88x5123
x5123_dir += libphy/marvell-88x5123/serdes
x5123_src := $(foreach d,$(x5123_dir),$(BDK_ROOT)/$(d)/*.[cS])
x5123_src := $(wildcard $(x5123_src))
x5123_src += $(BDK_ROOT)/libphy/bdk-phy-88x5123.c
x5123_objs = $(addsuffix .o, $(basename $(x5123_src)))
x5123_deps = $(addsuffix .d, $(basename $(x5123_src)))
x5123_inc := -I $(BDK_ROOT)/libphy/marvell-88x5123
x5123_inc += -I $(BDK_ROOT)/libphy/marvell-88x5123/serdes/include
x5123_inc += -I $(BDK_ROOT)/libphy/marvell-88x5123/serdes/marvell
x5123_flags := $(x5123_inc) -D AAPL_ENABLE_DIAG=0 -D C_LINKAGE=1 -D CPSS_BLOB=1 -D AAPL_ENABLE_EYE_MEASUREMENT=1 -DMS_SLEEP=0
ifdef USE_LLVM
    x5123_flags+=-Wno-self-assign
endif

$(x5123_objs) $(x5123_deps): CPPFLAGS += $(x5123_flags)

#
# The Marvell 88x5113 code requires some extra defines and warning supression
# to compile cleanly. Create a list of all the source this affects and only
# apply the compiler flags to the correct files
#
x5113_dir := libphy/marvell-88x5113
x5113_dir += libphy/marvell-88x5113/serdes/src
x5113_src := $(foreach d,$(x5113_dir),$(BDK_ROOT)/$(d)/*.[cS])
x5113_src := $(wildcard $(x5113_src))
x5113_src += $(BDK_ROOT)/libphy/bdk-phy-88x5113.c
x5113_objs = $(addsuffix .o, $(basename $(x5113_src)))
x5113_deps = $(addsuffix .d, $(basename $(x5113_src)))
x5113_inc := -I $(BDK_ROOT)/libphy/marvell-88x5113
x5113_inc += -I $(BDK_ROOT)/libphy/marvell-88x5113/serdes/src/include
x5113_flags := $(x5113_inc) -D HAVE_UNISTD_H=0 -D C_LINKAGE=1 -D AAPL_ENABLE_MAIN=0 -D AAPL_ENABLE_ESCOPE_MEASUREMENT=0
ifndef USE_LLVM
x5113_flags+=-Wno-unused-but-set-variable
endif

$(x5113_objs) $(x5113_deps): CPPFLAGS += $(x5113_flags)

#
# The Marvell 88x6141 code requires some extra defines and warning supression
# to compile cleanly. Create a list of all the source this affects and only
# apply the compiler flags to the correct files
#
x6141_dir := libphy/marvell-88x6141
x6141_dir += libphy/marvell-88x6141/serdes/src
x6141_src := $(foreach d,$(x6141_dir),$(BDK_ROOT)/$(d)/*.[cS])
x6141_src := $(wildcard $(x6141_src))
x6141_src += $(BDK_ROOT)/libphy/bdk-phy-88x6141.c
x6141_objs = $(addsuffix .o, $(basename $(x6141_src)))
x6141_deps = $(addsuffix .d, $(basename $(x6141_src)))
x6141_inc := -I $(BDK_ROOT)/libphy/marvell-88x6141
x6141_inc += -I $(BDK_ROOT)/libphy/marvell-88x6141/serdes/src/include
x6141_flags := $(x6141_inc) -D HAVE_UNISTD_H=0 -D C_LINKAGE=1

$(x6141_objs) $(x6141_deps): CPPFLAGS += $(x6141_flags)

#
# The Marvell 88x3310 code requires some extra defines and warning supression
# to compile cleanly. Create a list of all the source this affects and only
# apply the compiler flags to the correct files
#
x3310p_dir := libphy/marvell-88x3310
x3310p_src := $(foreach d,$(x3310p_dir),$(BDK_ROOT)/$(d)/*.[cS])
x3310p_src := $(wildcard $(x3310p_src))
x3310p_src += $(BDK_ROOT)/libphy/bdk-phy-88x3310p.c
x3310p_objs = $(addsuffix .o, $(basename $(x3310p_src)))
x3310p_deps = $(addsuffix .d, $(basename $(x3310p_src)))
x3310p_inc := -I $(BDK_ROOT)/libphy/marvell-88x3310
x3310p_flags := $(x3310p_inc)  -D HAVE_UNISTD_H=0 -D C_LINKAGE=1

$(x3310p_objs) $(x3310p_deps): CPPFLAGS += $(x3310p_flags)
