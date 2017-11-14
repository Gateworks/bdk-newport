ABOUT cortina-phy-updater
=========================

The cortina-phy-updater.bin is a boot stage that gets inserted into the
ThunderX boot process after boot.bin. The binary contains a Cortina PHY
firmware image. The firmware image date is compared to the date of the firmware
image in the Cortina PHY ROM. If the image in the file is newer than the ROM
image the ROM image will be updated.


COMPILING
=========

Image files are located in the images directory and are provided in an ASCII
format. As the ASCII files are very big, the build system compiles them into a
binary format using the:

   cortina-convert.py

tool. The symbolic link:

    cortina-latest.txt

must point to the current image source file. The info file:

    cortina.inf

must contain the meta information for the image file. The resulting image file
is called:

    cortina.img

and will be added to the cortina-phy-updater.bin file's ROM fs. No image or
meta files are being copied into FAT fs.


IMAGE INFO FILE
===============

The image info file is located in the images directory and called:

    cortina.inf

It contains the information about the available image, such as the date stamps
as well as the name of the binary image file. This file will be copied into the
cortina-phy-updater.bin file's ROM fs.

The file contains one line in the following format:

0702 2015 1557 /rom/cortina.img auto
^    ^    ^    ^                ^
|    |    |    |                +- Update mode:
|    |    |    |                   auto  = update if provided firmware is newer
|    |    |    |                   match = update if provided firmware is not the same
|    |    |    +------------------ Full Path to binary image file name
|    |    +----------------------- Time stamp
|    +---------------------------- Year stamp
+--------------------------------- Month / Day stamp

The date stamps are taken from the vendor provided list. Examples are below.


IMAGE SOURCE FILES
==================

0x8   - Ucode Month and day
0x9   - Ucode Year
0xa   - Ucode Time
0x22  - Image creation date
0x24  - SW API version

Image                                               Offset 0x8     0x9     0xa    0x22    0x24
==============================================================================================
CS4343_SR2SR_10GE_eeprom_11_26_2014.txt                 0x1126  0x2014  0x1259  0x0000  0x3402
CS4343_10G_BP_2_SR_10GE_eeprom_1_8_2015.txt             0x0108  0x2015  0x1903  0x0000  0x3592
CS4343_10GBP_2_DAC_eeprom_6_24_2015.txt*                0x0507  0x2015  0x1530  0x1861  0x3648
CS4343_10GBP_2_CX1_4dB_patched_eeprom_9_16_2015.txt     0x0702  0x2015  0x1557  0x1091  0x3679
CS4343_10GE_eeprom_10_23_2015.txt                       0x0807  0x2015  0x1409  0x1da1  0x3801

* not checked in
