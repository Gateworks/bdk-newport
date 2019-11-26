X6141_SBUS_MASTER_ROM := $(wildcard $(BDK_ROOT)/libphy/marvell-88x6141/sbus_master.*.rom)
X6141_SERDES_ROM      := $(wildcard $(BDK_ROOT)/libphy/marvell-88x6141/serdes.*.rom)

X6141_SBUS_MASTER_ROM_COUNT := $(words $(X6141_SBUS_MASTER_ROM))
X6141_SERDES_ROM_COUNT      := $(words $(X6141_SERDES_ROM))

ifneq ($(X6141_SBUS_MASTER_ROM_COUNT), 1)
    $(error There must be exactly one 88X6141 sbus master rom file.  The problem is it's either missing or there's more than one)
endif

ifneq ($(X6141_SERDES_ROM_COUNT), 1)
    $(error There must be exactly one 88X6141 serdes rom file.  The problem is it's either missing or there's more than one)
endif

X6141_SBUS_MASTER_BIN := $(BDK_ROOT)/libphy/marvell-88x6141/sbus_master.bin
X6141_SERDES_BIN      := $(BDK_ROOT)/libphy/marvell-88x6141/serdes.bin

X6141_ROM_TO_BIN      := $(BDK_ROOT)/libphy/marvell-88x6141/rom_to_bin.pl

$(X6141_SBUS_MASTER_BIN): $(X6141_SBUS_MASTER_ROM)
	$(X6141_ROM_TO_BIN) < $< > $@

$(X6141_SERDES_BIN): $(X6141_SERDES_ROM)
	$(X6141_ROM_TO_BIN) < $< > $@

$(BDK_ROOT)/libphy/marvell-88x6141/mydFwImages.o: $(X6141_SBUS_MASTER_BIN) $(X6141_SERDES_BIN) $(BDK_ROOT)/libphy/marvell-88x6141/mydFwImages.S
