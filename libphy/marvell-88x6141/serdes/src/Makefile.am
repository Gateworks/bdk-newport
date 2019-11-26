## Makefile.am -- Process this file with automake to produce Makefile.in

lib_LTLIBRARIES         = lib@PACKAGE_NAME@.la
lib@PACKAGE_NAME@_la_LDFLAGS = -avoid-version @EXTRA_LIBTOOL_ARGS_DLL@
lib@PACKAGE_NAME@_la_LIBADD  = @EXTRA_LDFLAGS@
lib@PACKAGE_NAME@_la_CFLAGS  = -Iinclude

include_HEADERS = \
        include/aacs_server.h \
        include/aapl.h \
        include/aapl_core.h \
        include/aapl_library.h \
        include/asic_info.h \
        include/avsp.h \
        include/diag_core.h \
        include/eye.h \
        include/eye_math.h \
        include/gpio_mdio.h \
        include/i2c.h \
        include/logging.h \
        include/mdio.h \
        include/meas.h \
        include/pmd.h \
        include/pmro.h \
        include/sbm.h \
        include/sbus.h \
        include/sensor.h \
        include/serdes_core.h \
        include/serdes_dfe.h \
        include/spico.h \
        include/system_includes.h

lib@PACKAGE_NAME@_la_SOURCES = \
        aacs.c \
        aacs_server.c \
        aapl_core.c \
        avsp.c \
        avsp_5410.c \
        diag_core.c \
        gpio_mdio.c \
        i2c.c \
        library.c \
        logging.c \
        mdio.c \
        pmro.c \
        sbus.c \
        sbm.c \
        sensor.c \
        dfe.c \
        eye.c \
        eye_math.c \
        meas.c \
        pmd.c \
        serdes_core.c \
        spico.c \
        spico_diag.c \
        user_code.c
