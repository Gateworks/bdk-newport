# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************

TOOLCHAINS=$(HOME)/work/tools
BDK_EXTRA_CPPFLAGS=-Werror
export BDK_EXTRA_CPPFLAGS

CMD_BUILD=make -s -j8 BDK_ROOT=$(BDK_ROOT) LIBC_DIR=$(LIBC_DIR) BDK_GCC_ROOT=$(BDK_GCC_ROOT) BDK_CLANG_ROOT=$(BDK_CLANG_ROOT) -C bdk-$@
CMD_TEST=make -s -j BDK_ROOT=$(BDK_ROOT) LIBC_DIR=$(LIBC_DIR) BDK_GCC_ROOT=$(BDK_GCC_ROOT) BDK_CLANG_ROOT=$(BDK_CLANG_ROOT) -C bdk-$@ test

.PHONY: compilers
compilers: gcc llvm

.PHONY: gcc
gcc: gcc5 gcc6 gcc7 gcc7-be

.PHONY: llvm
llvm: llvm4 llvm5 llvm6 llvm7 llvm8

.PHONY: gcc7
gcc7: private LIBC_DIR=aarch64-marvell-elf
gcc7: private BDK_GCC_ROOT=$(TOOLCHAINS)/gcc7/marvell-tools-236.0
gcc7: private BDK_CLANG_ROOT=
gcc7: private BDK_ROOT=$(shell pwd)/bdk-gcc7
gcc7: bdk-gcc7
	echo "*****************************"
	echo "$@"
	echo "*****************************"
	$(CMD_BUILD)
	$(CMD_TEST)

.PHONY: gcc7-be
gcc7-be: private LIBC_DIR=aarch64-marvell-elf
gcc7-be: private BDK_GCC_ROOT=$(TOOLCHAINS)/gcc7/marvell-tools-236.0
gcc7-be: private BDK_CLANG_ROOT=
gcc7-be: private BDK_ROOT=$(shell pwd)/bdk-gcc7-be
gcc7-be: bdk-gcc7-be
	echo "*****************************"
	echo "$@"
	echo "*****************************"
	$(CMD_BUILD) BE=1
	$(CMD_TEST) BE=1

.PHONY: gcc6
gcc6: private LIBC_DIR=aarch64-thunderx-elf
gcc6: private BDK_GCC_ROOT=$(TOOLCHAINS)/gcc6/thunderx-tools-97
gcc6: private BDK_CLANG_ROOT=
gcc6: private BDK_ROOT=$(shell pwd)/bdk-gcc6
gcc6: bdk-gcc6
	echo "*****************************"
	echo "$@"
	echo "*****************************"
	$(CMD_BUILD)
	$(CMD_TEST)

.PHONY: gcc5
gcc5: private LIBC_DIR=aarch64-thunderx-elf
gcc5: private BDK_GCC_ROOT=$(TOOLCHAINS)/gcc5/thunderx-tools-451
gcc5: private BDK_CLANG_ROOT=
gcc5: private BDK_ROOT=$(shell pwd)/bdk-gcc5
gcc5: bdk-gcc5
	echo "*****************************"
	echo "$@"
	echo "*****************************"
	$(CMD_BUILD)
	$(CMD_TEST)

.PHONY: llvm8
llvm8: private LIBC_DIR=aarch64-marvell-elf
llvm8: private BDK_GCC_ROOT=$(TOOLCHAINS)/gcc7/marvell-tools-236.0
llvm8: private BDK_CLANG_ROOT=$(TOOLCHAINS)/llvm/clang+llvm-8.0.1-x86_64-linux-sles11.3/bin
llvm8: private BDK_ROOT=$(shell pwd)/bdk-llvm8
llvm8: bdk-llvm8
	echo "*****************************"
	echo "$@"
	echo "*****************************"
	$(CMD_BUILD)
	$(CMD_TEST)

.PHONY: llvm7
llvm7: private LIBC_DIR=aarch64-marvell-elf
llvm7: private BDK_GCC_ROOT=$(TOOLCHAINS)/gcc7/marvell-tools-236.0
llvm7: private BDK_CLANG_ROOT=$(TOOLCHAINS)/llvm/clang+llvm-7.1.0-x86_64-linux-sles11.3/bin
llvm7: private BDK_ROOT=$(shell pwd)/bdk-llvm7
llvm7: bdk-llvm7
	echo "*****************************"
	echo "$@"
	echo "*****************************"
	$(CMD_BUILD)
	$(CMD_TEST)

.PHONY: llvm6
llvm6: private LIBC_DIR=aarch64-marvell-elf
llvm6: private BDK_GCC_ROOT=$(TOOLCHAINS)/gcc7/marvell-tools-236.0
llvm6: private BDK_CLANG_ROOT=$(TOOLCHAINS)/llvm/clang+llvm-6.0.1-x86_64-linux-sles11.3/bin
llvm6: private BDK_ROOT=$(shell pwd)/bdk-llvm6
llvm6: bdk-llvm6
	echo "*****************************"
	echo "$@"
	echo "*****************************"
	$(CMD_BUILD)
	$(CMD_TEST)

.PHONY: llvm5
llvm5: private LIBC_DIR=aarch64-marvell-elf
llvm5: private BDK_GCC_ROOT=$(TOOLCHAINS)/gcc7/marvell-tools-236.0
llvm5: private BDK_CLANG_ROOT=$(TOOLCHAINS)/llvm/clang+llvm-5.0.2-x86_64-linux-sles11.3/bin
llvm5: private BDK_ROOT=$(shell pwd)/bdk-llvm5
llvm5: bdk-llvm5
	echo "*****************************"
	echo "$@"
	echo "*****************************"
	$(CMD_BUILD)
	$(CMD_TEST)

.PHONY: llvm4
llvm4: private LIBC_DIR=aarch64-marvell-elf
llvm4: private BDK_GCC_ROOT=$(TOOLCHAINS)/gcc7/marvell-tools-236.0
llvm4: private BDK_CLANG_ROOT=$(TOOLCHAINS)/llvm/clang+llvm-4.0.1-linux-x86_64-sles11.3/bin
llvm4: private BDK_ROOT=$(shell pwd)/bdk-llvm4
llvm4: bdk-llvm4
	echo "*****************************"
	echo "$@"
	echo "*****************************"
	$(CMD_BUILD)
	$(CMD_TEST)

.PHONY: bdk-gcc5 bdk-gcc6 bdk-gcc7 bdk-gcc7-be bdk-llvm4 bdk-llvm5 bdk-llvm6 bdk-llvm7 bdk-llvm8
bdk-gcc5 bdk-gcc6 bdk-gcc7 bdk-gcc7-be bdk-llvm4 bdk-llvm5 bdk-llvm6 bdk-llvm7 bdk-llvm8:
	rm -rf $@
	git clone -q $(BDK_ROOT) $@

