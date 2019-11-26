# ***********************license start***********************************
# Copyright (C) 2018 Marvell International Ltd.
# SPDX-License-Identifier: BSD-3-Clause
# https://spdx.org/licenses
# **********************license end**************************************
NAME	= fatfs-tool

CC		= gcc
INC_DIR	= -I $(FATFS_DIR)/src -I.
LIB_DIR	=
LIBS	=
FATFS_DIR	= FatFs

CPP_COMPILE_FLAGS	= -Wall -O2 -std=c99 $(INC_DIR)
CPP_LINK_FLAGS		= $(LIB_DIR) $(LIBS)

OBJS =	main.o \
		cmd.o \
		bdk-aes.o \
		$(FATFS_DIR)/src/ff.o \
		$(FATFS_DIR)/src/option/unicode.o \
		$(FATFS_DIR)/src/diskio.o \
		$(FATFS_DIR)/src/diskio_img_file.o

HDRS =	*.h $(FATFS_DIR)/src/*.h

.SUFFIXES: .c .h .o

all: $(NAME)

$(OBJS): $(HDRS)

$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(CPP_LINK_FLAGS) $(OBJS)

.c.o:
	$(CC) $(CPP_COMPILE_FLAGS) -c $*.c -o $*.o

clean:
	rm -f $(NAME) $(OBJS)
	rm -f *~ *.bak *.bck
