set EMUL_DIR $env(EMUL_DIR)
set EMUL_PCL_DIR $EMUL_DIR/emulation_pcl
set EMUL_FC_DIR $EMUL_DIR/emulation_fc


#-- Trace ON if needed
#do $EMUL_DIR/utils/tr_on.tcl
do ../utils/uaa.tcl
#hwtrace setdepth max
#memory download -file  $EMUL_FC_DIR/bdk/bdk-boot.hex -instance tb.fc_wrapper.fc.dcp1.ddr01.lmc.mem -apply

###emmmc###
memory download -file $EMUL_FC_DIR/preload/preload_CID.hex -instance tb.fc_wrapper.emmc_sm_0.core_0.RESP_GEN_0.CID_0.mem -apply
memory download -file $EMUL_FC_DIR/preload/preload_CSD.hex -instance tb.fc_wrapper.emmc_sm_0.core_0.RESP_GEN_0.CSD_0.mem -apply
memory download -file $EMUL_FC_DIR/preload/preload_OCR.hex -instance tb.fc_wrapper.emmc_sm_0.core_0.RESP_GEN_0.OCR_0.mem -apply

###Load your emmc Image here####
memory download -file $EMUL_FC_DIR/bdk/thunder-emmc-ascii.img -instance tb.fc_wrapper.emmc_sm_0.core_0.EMEM_0.user_0.mem  -addr_format x -apply

#-- CSR configuration
memory download -file $EMUL_FC_DIR/../../../rtl/cpc/bnk0_rom0 -instance tb.fc_wrapper.fc.roc.cpc.cpc.mem.rom.boot_rom.bnk0_rom0.rom -apply
memory download -file $EMUL_FC_DIR/../../../rtl/cpc/bnk0_rom1 -instance tb.fc_wrapper.fc.roc.cpc.cpc.mem.rom.boot_rom.bnk0_rom1.rom -apply
memory download -file $EMUL_FC_DIR/../../../rtl/cpc/bnk1_rom0 -instance tb.fc_wrapper.fc.roc.cpc.cpc.mem.rom.boot_rom.bnk1_rom0.rom -apply
memory download -file $EMUL_FC_DIR/../../../rtl/cpc/bnk1_rom1 -instance tb.fc_wrapper.fc.roc.cpc.cpc.mem.rom.boot_rom.bnk1_rom1.rom -apply

# Set GPIO 10 to enable trust
#reg setvalue tb.fc_wrapper.gpi_gpio_r[10]  0x1

run 1ps

# Fix AP reset address in case emulator changed it
reg setvalue {tb.fc_wrapper.fc.pcl.clu0.ap0.ap_frontend.ap_issue.ap_issue_ctl.ap_issue_csr.tbv_reset_address[63:0]} 0x87d000000000
reg setvalue {tb.fc_wrapper.fc.pcl.clu1.ap0.ap_frontend.ap_issue.ap_issue_ctl.ap_issue_csr.tbv_reset_address[63:0]} 0x87d000000000
reg setvalue {tb.fc_wrapper.fc.pcl.clu2.ap0.ap_frontend.ap_issue.ap_issue_ctl.ap_issue_csr.tbv_reset_address[63:0]} 0x87d000000000
reg setvalue {tb.fc_wrapper.fc.pcl.clu3.ap0.ap_frontend.ap_issue.ap_issue_ctl.ap_issue_csr.tbv_reset_address[63:0]} 0x87d000000000

# -- Rom data fetching
trigger download $EMUL_DIR/utils/scp_bl0.trigger -position 10
run
waitfor trigger
trigger delete

# TrustZone keys
# ROTPK 1 and 0
reg setvalue tb.fc_wrapper.fc.roc.rst.rst.fusf.rck.r_fus_dat_bnk6 0x2e0ed8920c32b5d9b78cb8eafb7775e9
reg setvalue tb.fc_wrapper.fc.roc.rst.rst.fusf.rck.r_fus_dat_bnk7 0x005efb3f7f1426d8f2d8e81abcdb6d4d
# SSK
reg setvalue tb.fc_wrapper.fc.roc.rst.rst.fusf.rck.r_fus_dat_bnk8 0x00000000000000000000000000000000
# HUK
reg setvalue tb.fc_wrapper.fc.roc.rst.rst.fusf.rck.r_fus_dat_bnk9 0x00000000000000000000000000000000
# force trustzone, not working
#reg setvalue tb.fc_wrapper.fc.roc.rst.rst.fusf.rck.r_fus_dat_bnk0_noscan[8] 0x1

# Blow platform fuse
reg setvalue tb.fc_wrapper.fc.roc.rst.rst.fus.rck.r_fus_dat_bnk0[117] 1
reg setvalue tb.fc_wrapper.fc.roc.rst.rst.fus.rck.r_fus_dat_bnk3[23:0] 0xfffff0

run

# -- Start of firmware
#trigger download $EMUL_DIR/utils/start_of_firmware.trigger -position 10
#run
#waitfor trigger
#trigger delete
#run 200us
#trigger download ../utils/scp_bl1_start.trigger -position 10
#run
#waitfor trigger
#trigger delete
# --


