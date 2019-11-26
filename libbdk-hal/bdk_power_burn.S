/***********************license start***********************************
* Copyright (C) 2018 Marvell International Ltd.
* SPDX-License-Identifier: BSD-3-Clause
* https://spdx.org/licenses
***********************license end**************************************/
    .section .text
    .global __bdk_power_burn




__bdk_power_burn:
    stp     d30, d31, [sp, #-16]!
    stp     d28, d29, [sp, #-16]!
    stp     d26, d27, [sp, #-16]!
    stp     d24, d25, [sp, #-16]!
    stp     d22, d23, [sp, #-16]!
    stp     d20, d21, [sp, #-16]!
    stp     d18, d19, [sp, #-16]!
    stp     d16, d17, [sp, #-16]!
    stp     d14, d15, [sp, #-16]!
    stp     d12, d13, [sp, #-16]!
    stp     d10, d11, [sp, #-16]!
    stp     d8, d9, [sp, #-16]!
    stp     d6, d7, [sp, #-16]!
    stp     d4, d5, [sp, #-16]!
    stp     d2, d3, [sp, #-16]!
    stp     d0, d1, [sp, #-16]!
    stp     x20, x21, [sp, #-16]!
    stp     x10, x11, [sp, #-16]!
    stp     x12, x13, [sp, #-16]!
    sub	    sp, sp, 8192

    adr		x20, data
    mov		x0, 1<<15 /* About 1.9ms as 1Ghz */

    ldr		q0, [x20], #16
    ldr		q1, [x20], #16
    ldr		q2, [x20], #16
    ldr		q3, [x20], #16
    ldr		q4, [x20], #16
    ldr		q5, [x20], #16
    ldr		q6, [x20], #16
    ldr		q7, [x20], #16
    ldr		q8, [x20], #16
    ldr		q9, [x20], #16
    ldr		q10, [x20], #16
    ldr		q11, [x20], #16
    ldr		q12, [x20], #16
    ldr		q13, [x20], #16
    ldr		q14, [x20], #16
    ldr		q15, [x20], #16
    str		d0, [sp,#0]
    str		d1, [sp,#8]
    str		d2, [sp,#16]
    str		d3, [sp,#24]
    ldr		x10, [sp,#0]
    ldr		x11, [sp,#8]
    ldr		x12, [sp,#16]
    ldr		x13, [sp,#24]


.align 5
loop2:

    fmul	v20.2d, v0.2d, v1.2d
    ldr		d28, [x20], #8
    eor         x10, x10, x0, ASR #3
    str		x11, [sp,#8]

    fmul	v21.2d, v1.2d, v2.2d
    ldr		d29, [x20], #8
    add         x11, x11, x12, ASR #7
    str		x12, [sp,#128]
    fadd        v31.2d, v31.2d, v20.2d

    fmul	v22.2d, v2.2d, v3.2d
    ldr		d30, [x20], #8
    eor         x12, x12, x13, ASR #5
    str		x13, [sp,#272]
    fadd        v31.2d, v31.2d, v21.2d

    fmul	v23.2d, v3.2d, v4.2d
    ldr		d30, [x20], #8
    add         x13, x13, x10, ASR #1
    str		x10, [sp,#408]
    fadd        v31.2d, v31.2d, v22.2d

    fmul	v20.2d, v4.2d, v5.2d
    ldr		d28, [x20], #8
    eor         x10, x10, x0, ASR #3
    str		x11, [sp,#544]
    fadd        v31.2d, v31.2d, v23.2d

    fmul	v21.2d, v5.2d, v6.2d
    ldr		d29, [x20], #8
    add         x11, x11, x12, ASR #7
    str		x12, [sp,#680]
    fadd        v31.2d, v31.2d, v20.2d

    fmul	v22.2d, v6.2d, v7.2d
    ldr		d30, [x20], #8
    eor         x12, x12, x13, ASR #5
    str		x13, [sp,#816]
    fadd        v31.2d, v31.2d, v21.2d

    fmul	v23.2d, v7.2d, v8.2d
    ldr		d30, [x20], #8
    add         x13, x13, x10, ASR #1
    str		x10, [sp,#952]
    fadd        v31.2d, v31.2d, v22.2d

    fmul	v20.2d, v8.2d, v9.2d
    ldr		d28, [x20], #8
    eor         x10, x10, x0, ASR #3
    str		x11, [sp,#1088]
    fadd        v31.2d, v31.2d, v23.2d

    fmul	v21.2d, v9.2d, v10.2d
    ldr		d29, [x20], #8
    add         x11, x11, x12, ASR #7
    str		x12, [sp,#1224]
    fadd        v31.2d, v31.2d, v20.2d

    fmul	v22.2d, v10.2d, v11.2d
    ldr		d30, [x20], #8
    eor         x12, x12, x13, ASR #5
    str		x13, [sp,#1360]
    fadd        v31.2d, v31.2d, v21.2d

    fmul	v23.2d, v11.2d, v12.2d
    ldr		d30, [x20], #8
    add         x13, x13, x10, ASR #1
    str		x10, [sp,#1496]
    fadd        v31.2d, v31.2d, v22.2d

    fmul	v20.2d, v12.2d, v13.2d
    ldr		d28, [x20], #8
    eor         x10, x10, x0, ASR #3
    str		x11, [sp,#1632]
    fadd        v31.2d, v31.2d, v23.2d

    fmul	v21.2d, v13.2d, v14.2d
    ldr		d29, [x20], #8
    add         x11, x11, x12, ASR #7
    str		x12, [sp,#24]
    fadd        v31.2d, v31.2d, v20.2d

    fmul	v22.2d, v14.2d, v15.2d
    ldr		d30, [x20], #8
    eor         x12, x12, x13, ASR #5
    str		x13, [sp,#24]
    fadd        v31.2d, v31.2d, v21.2d

    fmul	v23.2d, v15.2d, v0.2d
    ldr		d30, [x20], #8
    add         x13, x13, x10, ASR #1
    str		x10, [sp,#24]
    fadd        v31.2d, v31.2d, v22.2d

    adr		x20, data
    subs	x0, x0, #1
    fadd        v31.2d, v31.2d, v23.2d
    b.ne	loop2

    adr         x20, correct    /* Address of correct result */
    fmov        x1, d31         /* Load low part in X1 */
    ldr         x0, [x20]       /* Load correct low part in X0 */
    fmov        x3, v31.d[1]    /* Load high part in X3 */
    ldr         x2, [x20, 8]    /* Load correct high part in X2 */
    eor         x0, x0, x1      /* XOR low with correct */
    eor         x2, x2, x3      /* XOR high with correct */
    orr         x0, x0, x2      /* OR together, result should be zero */

    add	    sp, sp, 8192
    ldp     x12, x13, [sp], #16
    ldp     x10, x11, [sp], #16
    ldp     x20, x21, [sp], #16
    ldp     d0, d1, [sp], #16
    ldp     d2, d3, [sp], #16
    ldp     d4, d5, [sp], #16
    ldp     d6, d7, [sp], #16
    ldp     d8, d9, [sp], #16
    ldp     d10, d11, [sp], #16
    ldp     d12, d13, [sp], #16
    ldp     d14, d15, [sp], #16
    ldp     d16, d17, [sp], #16
    ldp     d18, d19, [sp], #16
    ldp     d20, d21, [sp], #16
    ldp     d22, d23, [sp], #16
    ldp     d24, d25, [sp], #16
    ldp     d26, d27, [sp], #16
    ldp     d28, d29, [sp], #16
    ldp     d30, d31, [sp], #16


    ret





.align 7
 data:
.quad 0x42D473508C9FF7F3
.quad 0xC3DB49B8A9ECC40F
.quad 0xC00A7FE1F7E6DE0C
.quad 0x401465330D4281FA
.quad 0x4112D736B68ACF2A
.quad 0x43863228E83C3D40
.quad 0x40C9BDF2560B2F77
.quad 0x42E3071969AD6500
.quad 0x428CCC1BE902F518
.quad 0x41F60213E70A8F65
.quad 0xC2EFA253A7A5CBC2
.quad 0x435D82F16679ABB3
.quad 0xC312AECA5EDF7708
.quad 0xC2A6D0EB82CEE860
.quad 0xC368F3D5C78E2187
.quad 0x42E31B618F607BDC
.quad 0x4164199C648F32B4
.quad 0xC09913DEB3B07092
.quad 0xC1B8D0BF896318F9
.quad 0x408580385D565B2B
.quad 0x40D7A01C883CD6C4
.quad 0x42FCF74153CD7355
.quad 0xC38366FE69C970CA
.quad 0x40DA971FBF909CEE
.quad 0xC321D5B1C3A02E03
.quad 0xC10010D77AC12A20
.quad 0xC0D518EA303513F3
.quad 0x4141F30BDEE9119B
.quad 0x40A9E5239F220AE8
.quad 0xC2555D7764AEB6F7
.quad 0xC2E5B844CD95A89C
.quad 0x429464587A590A63
.quad 0xC0E4B649CBECFEAD
.quad 0x4315854E391EE9A3
.quad 0x41CCC01016437CD0
.quad 0x429AC42FDA4725E3
.quad 0x3FFFB367A21A8419
.quad 0xBFF7A0410A6B9ABC
.quad 0x4189FE6FEA922051
.quad 0xC2FCBE81B3CE9D2E
.quad 0x41B59839E8E86F5B
.quad 0xC0BD4E2804F3042C
.quad 0x43E7F5C5F0AC412A
.quad 0xC01C886827EDBC94
.quad 0xC277F472FA966113
.quad 0xC314EBE86EEB6BFE
.quad 0x40871E5CA2D41FED
.quad 0x43E52A3288ED2D95
.quad 0xC0635C82F29FCCE0
.quad 0x41A6A29BC1190375
.quad 0xC19A010AA4826F3E
.quad 0x4297B0215359F823
.quad 0x402C6066522BC522
.quad 0x427E899F62882EE3
.quad 0xC35E01CFAF2586F3
.quad 0xC278C6BBA706A543
.quad 0x4118C55F15FF8D4A
.quad 0x434605EDCCBEF07D
.quad 0xC31F863D78D35666
.quad 0x4019E31960A6FFC5
.quad 0x409F50EB4E5314AF
.quad 0xC35D102BCD038E8E
.quad 0xC1B8B9355489C76C
.quad 0x4369E3905AAA09D5
.quad 0xC3BE769532D404F3
.quad 0x41A89C8A4356BB2A
.quad 0xC0892C7E072CBF4C
.quad 0x4155D7D8FB637ABA
.quad 0x4334FB774FCDF155
.quad 0x4278BDBC158CC485
.quad 0x401ACA3DAACEC068
.quad 0x41E0DEB3F942CDF0
.quad 0xC176396E3908B875
.quad 0x4339399BD2AF0AB4
.quad 0x41AF6ABE6FD54385
.quad 0xC29320B656F5BDF5
.quad 0x410607B53C03AF45
.quad 0xC3E16C423B1F9785
.quad 0xC36711A2261FB69A
.quad 0x42198C11BE16D933
.quad 0x40E6E9F61EECF408
.quad 0x403E6E16CF7BE98C
.quad 0x437B227D3DAABC48
.quad 0xC0ECDFBE4A4C58A8
.quad 0x413F6AEABCA60C9F
.quad 0x43CDF634A840AEE1
.quad 0x404F13192105AAA7
.quad 0xBFF37A0739E63E28
.quad 0xC0D0D0CEC6D47497
.quad 0xC2104B013C7371AF
.quad 0xC021201BB2B856E7
.quad 0xC013624E4A60D5EE
.quad 0x41417D4EE2F52487
.quad 0x432764A70F1214B8
.quad 0xC271306C3A772B4C
.quad 0xC0D829FDAF12C3D2
.quad 0xC16B40D711AD3934
.quad 0xC3CAF5FFAC4C66CE
.quad 0x43EF7DAAA641AFCF
.quad 0xC1ACBB03412A7CE2
.quad 0x430740A8BC3868E1
.quad 0xC1EC20C7602C32C1
.quad 0xC24D8B2F1306FA04
.quad 0x429E30E734CD5844
.quad 0xC18DB8CC72E08DF4
.quad 0x41DE358C741BB0F6
.quad 0x40503D280B534A20
.quad 0xC233FE7EB9565C43
.quad 0x42F8D2BB4B5A2135
.quad 0xC0F1875FD9DFDCA7
.quad 0x4398A81828212EEE
.quad 0x40AB0330A0D9C17E
.quad 0xC1E14A44205F45AD
.quad 0x4220A235DC9B5A37
.quad 0x43A8403404F1922E
.quad 0x43CBF7D5E6202422
.quad 0xC0F37C49779BBBEF
.quad 0x436CBEB67C9C756B
.quad 0x415E93516A77E597
.quad 0xC0CF154BA6CCC151
.quad 0x405082E8FAFF64DE
.quad 0x41A1410A9411F0D8
.quad 0x401336CEDCAD9721
.quad 0xC00FC22EF7547B98
.quad 0x43B0C43BDDA5C68B
.quad 0x4127FED7078D6755
.quad 0xC35DFBCD5EABE07B
.quad 0xC0B17DC5A4A0EAD0
.quad 0x4305E124B6DDCAE8
.quad 0xC2CA68840623C2A8
.quad 0xC06B81C888B41D1F
.quad 0x40E223AC1D29223B
.quad 0x436B904306CCB8B6
.quad 0x40413FA1AE2217CA
.quad 0xC264CCBB2C58E09A
.quad 0x414A07DF1C17BBBB
.quad 0x406FA08B31526EA9
.quad 0xC173CE06739272D6
.quad 0xC18EED1C6844E72C
.quad 0x3FF4C301BC57F6A2
.quad 0x42329F67EC97D2DD
.quad 0xC2A97B131A31C928
.quad 0x4197DF717D952494
.quad 0xC2951A6F0B8DBE39
.quad 0xC03ED5746F59C789
.quad 0x42FA59537963E1B4
.quad 0xC2A315AFA8134D10
.quad 0x4148938796EE7745
.quad 0x407E342BEC2576C0
.quad 0xC22F312BB121F396
.quad 0xC3E1D3FDD3278C9E
.quad 0x41AD6C15EE7A80F7
.quad 0xC37F6B36E49FC76A
.quad 0x40B8872E7842D5AC
.quad 0x4031C5E6DD955E20
.quad 0x414E1DE68D96A04A
.quad 0x40680FAEFDD79FFB
.quad 0xC2395219E32FEC5B
.quad 0x4071BC8C54CF17AE
.quad 0xC004678A1B83AA7A
.quad 0x421572E29EB7FC72
.quad 0xC2F54CA9094672D4
.quad 0x40CCEAF3ACBD544C
.quad 0xC083FCC8F314CB10
.quad 0xC16714069F3779CE
.quad 0xC2FB456030C7DCFB
.quad 0xC1AB270852EED5CD
.quad 0xC18CC53D88A6E726
.quad 0xC02F528102029CD3
.quad 0xC33C606368A848AD
.quad 0xC15BD8350C8B31D2
.quad 0xC15E98AD482EE284
.quad 0x415F384ED12CB22D
.quad 0x40526A30A2A82209
.quad 0x408E26C7C1E904DE
.quad 0xC26138955A5BB385
.quad 0xC2E523CA4F116AD4
.quad 0x428DA47C2FF3B8F2
.quad 0xC1C92A863F21F6C5
.quad 0x429153D7BF0B8994
.quad 0x423323239F3FFAF8
.quad 0xC35CF9A8A4F5BF53
.quad 0xC03171DE60246964
.quad 0x42668F055678710D
.quad 0x433C178C03FDD610
.quad 0xC2576982DD236343
.quad 0xC396AF532835DA8C
.quad 0x40793EEE84A0105F
.quad 0x4186CFEF7D9A2F74
.quad 0xC1DBDD5BC8F2D511
.quad 0x401E62668EF32D4F
.quad 0xC2789376CC89373C
.quad 0xC1DC0EB163F1FA7E
.quad 0x4291CDB9F3D16D98
.quad 0xC087C0CB7E2B0025
.quad 0xC0B895007B4EC1C6
.quad 0xC393A7484D2E827A
.quad 0x41C900259D35642E
.quad 0xC31D4B2D071E2E36
.quad 0x43D9FF0EEA4C8727
.quad 0x4101EF142BA5727F
.quad 0xC00C8A81A957A87C
.quad 0xC2C7164EE1EAD292
.quad 0x4230F5FADAC583BC
.quad 0xC3E65C7B31A6E0F4
.quad 0xC2007CB994638703
.quad 0x43AD1D92CEA8DF57
.quad 0x41D659DDD84487FD
.quad 0xC0DAFCDC96313705
.quad 0xC217CEA800DB4BB3
.quad 0xC02CCACEABDF0C27
.quad 0x41874C7482B043D4
.quad 0x4140C3942B26687F
.quad 0xC3A52E28D4D9589F
.quad 0x3FFF68618D0D41EE
.quad 0xC3B56A97D03F4BFB
.quad 0x41D34F6E9D3BD0E6
.quad 0xC10725CB041BB5F6
.quad 0xC061E479BE90C897
.quad 0x400DE0F9EE56A811
.quad 0x4260C7B00B01FE6E
.quad 0x40133388A29E7093
.quad 0xC1367E9954A625D9
.quad 0x424062A9D8235DB9
.quad 0xC195D3AE34751C05
.quad 0xC05F38006909DAE4
.quad 0x4182555D99110C8E
.quad 0xC3440E6727F81C5F
.quad 0xC1612660A9C42158
.quad 0x42F4951452B9616F
.quad 0x40996C09AA77518F
.quad 0x41A525FF85CD6963
.quad 0xC0F5D25D500C1E83
.quad 0x435ABF1B6600CD51
.quad 0x42FD140E92573ECD
.quad 0xC15B90D792898FC6
.quad 0xC0BC7698CD4ECC3E
.quad 0x4246A00EB42E47BB
.quad 0xC1AB72E8359E804E
.quad 0xC1836BC7D801CBC2
.quad 0x428D0A951E14E82F
.quad 0x4316A5966021D7ED
.quad 0x429C3670A0441FCA
.quad 0xC303388705658ADE
.quad 0xC26D2260A20833B8
.quad 0xC0B84451F1D42C5C
.quad 0xC0F0447F20C2B4AD
.quad 0xC2B93D04D81FFDB2
.quad 0x41DBC88EB49156A0
.quad 0xC18781B57747ABED
.quad 0x40BC099449FA5490
.quad 0xC2D91851332FD02E
.quad 0xC17F1A42C045E221
.quad 0x4101CCB8F6A7F4FD
.quad 0xC2402DB651DA5E86
.quad 0x40C56DC8D0F71F27

correct:
.quad 0x47a94950e70e8b67 /* low */
.quad 0xc7516cdcc7d411f4 /* high */

