.section .rodata


.global x6141_sbus_master_image_start, x6141_sbus_master_image_end

x6141_sbus_master_image_start:
    .incbin "sbus_master.bin"
x6141_sbus_master_image_end:


.global x6141_serdes_image_start, x6141_serdes_image_end

x6141_serdes_image_start:
    .incbin "serdes.bin"
x6141_serdes_image_end:
