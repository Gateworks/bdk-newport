#include <bdk.h>
#include <stdint.h>
#include "AQ_API.h"

BDK_REQUIRE_DEFINE(AQR107_SUPPORT);

#define aqr_issue(rc , function, args... ) do {         \
        rc = function (  args );                        \
        if (AQ_RET_OK != rc) printf(#function " returned rc %d\n", rc);  \
    } while (0)

#define makecase(var, token) case token: var = #token ; break

#define makecase2(var, token1, token2) case token1##token2 : var = #token2 ; break

/* token to show for unknown values */
static const char *unktoken = "???";

/*
 * Internal helper to form AQ_Port structure := aqr107 io address
 */
static void make_aqport(AQ_API_Port *aqport, const int node, const int mdio_bus, const int mdio_phy)
{
    if (aqport) {
        aqport->device = AQ_DEVICE_EUR; // According to AQR doc AQR107 is 28nm gen2 device
        aqport->PHY_ID.node = node;
        aqport->PHY_ID.mdio_bus = mdio_bus;
        aqport->PHY_ID.mdio_phy = mdio_phy;
    }
}

static void sayOK()
{
    printf("OK\n");
}

#if 0
/**
 * boot time phy setup
 * needs to be done only for phy images which have wrong MDI-ABCD inversion
 * At this time
 * NAS8104 board has MDI-ABCD inverted
 * SFF8104 board has MDI-ABCD non-inverted
 * Boards use different images.
 * If ABCD inversion has to be patched:
 * - flip 1.e400 bit0 := 0:staright 1: ABCD<->DCBA
 * restart autonegotiation
 */
int bdk_if_aqr_setup(bdk_node_t node) {
    for (int bgx = 0; bgx < 4; bgx++)
    {
        int port;
        for(port = 0;port<4;port++) {
            int phy_addr = bdk_config_get_int(BDK_CONFIG_PHY_ADDRESS, node, bgx, port);
            if (phy_addr != -1)
            {
                int node = (phy_addr >> 24) & 0xff;
                int mdio_bus = (phy_addr >> 8) & 0xff;
                int mdio_addr = phy_addr & 0xff;
                if (node == 0xff)
                    node = bdk_numa_local();
                if ((phy_addr & BDK_IF_PHY_TYPE_MASK) == BDK_IF_PHY_MDIO)
                {
                    int qlm = bdk_qlm_get(node, BDK_IF_BGX, bgx, port);
                    if (qlm != -1) {
                        int id = bdk_mdio_45_read(node, mdio_bus, mdio_addr, 1, BDK_MDIO_PHY_REG_ID1);
                        if (id != 0x3a1) continue;
                        int anr =  bdk_mdio_45_read(node, mdio_bus, mdio_addr, 1, 0xe400);
                        if (anr & 1) {
                            anr = anr & (0xffffu ^ 5); /* Disable fast retraining and MDIO-ABCD swap */
                            bdk_mdio_45_write(node, mdio_bus, mdio_addr, 1, 0xe400, anr);
                            {
                                AQ_API_Configuration cfg;
                                AQ_Retcode rc;
                                AQ_API_Port aq_port;
                                make_aqport(&aq_port, node, mdio_bus, mdio_addr);
                                rc = AQ_API_GetConfiguration( &aq_port,&cfg);
                                if (AQ_RET_OK == rc) {
                                    cfg.LED_Control[0].LED_On_WhenConnecting = True;
                                    cfg.LED_Control[1].LED_On_WhenConnecting = True;
                                    cfg.LED_Control[0].LED_TogglesOnTransmitActivity = False;
                                    cfg.LED_Control[0].LED_TogglesOnReceiveActivity = False;
                                    cfg.LED_Control[1].LED_TogglesOnTransmitActivity = False;
                                    cfg.LED_Control[1].LED_TogglesOnReceiveActivity = False;
                                    aqr_issue(rc, AQ_API_SetConfiguration, &aq_port,&cfg);
                                }
                            }
                            printf("AQR %d.%d Wrote %x to 1.e400, restarted autonegotiation rc %d\n",
                                   bgx,port, anr, bdk_aqr_restart_an(node,mdio_bus,mdio_addr));
                        } else {
                            printf("BGX%d.%d AQR already have ABCD set 1.e400 = 0x%04x\n",bgx,port,anr);
                        }
                    }
                }
            }
        }
    }
    return 0;
}
#endif

static void dump_response(const char *title, const void *data, const unsigned length)
{
    if (title) puts(title);
    int c = 0;
    const uint8_t *pstart = (uint8_t*) data;
    const uint8_t *pend = pstart + length;
    for ( const uint8_t *p = pstart; p != pend; p++){
        if (0 == c) printf("%03x: ", (unsigned) (p - pstart));
        printf("%02x%s",
               *p,
               (c&3) != 3 ? "" :(c==15) ? "\n" : " ");
        c = (c+1) & 0xf;
    }
    if (c) printf("\n");
}

int __bdk_aqr_load_ext_image(bdk_node_t node, int mdio_bus, int mdio_phy, const uint8_t *img, const uint32_t img_len)
{
    /* write image to flash */
    AQ_API_Port aq_port;
    AQ_API_Port *aq_ports[] = {&aq_port};
    AQ_Retcode result = 0;
    unsigned int provisioning_addr[] = {mdio_phy};
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc = AQ_API_WriteBootLoadImage(
        aq_ports,
        1, /* number of ports */
        provisioning_addr,
        &result,
	&img_len,
        img,
        mdio_phy,
        &aq_port);
    printf(" AQ_API_WriteBootloadImage rc %d result %d\n",
           rc, result);

    return rc;
}

int __bdk_aqr_write_ext_image(bdk_node_t node, int mdio_bus, int mdio_phy, const uint8_t *img, const uint32_t img_len)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    aqr_issue(rc, AQ_API_WriteAndVerifyFlashImage, &aq_port,
              &img_len, img);
    if ( AQ_RET_FLASH_PAGE_SIZE_CHANGED == rc) {
        bdk_warn("\nPage Size of flash device have been changed."
                 "\nCycle board power and update Phy flash one more time.\n");
    }
    return rc;
}

int bdk_aqr_get_status(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_API_Status status ;
    bzero(&status,sizeof(status));

    AQ_Retcode rc;
    aqr_issue(rc,AQ_API_GetStatus,&aq_port, &status);
    if (AQ_RET_OK == rc) {
        char buf[128];
        for(unsigned i = 0; i < sizeof(status.loadedImageInformation.imageID_String);i++) {
            if ('\0' == status.loadedImageInformation.imageID_String[i]) {
                buf[i] = '\0';
                break;
            }
            buf[i] = status.loadedImageInformation.imageID_String[i] > 0x1f ? status.loadedImageInformation.imageID_String[i] : '.';
        }
        buf[sizeof(status.loadedImageInformation.imageID_String) -1] = '\0';
        printf("AQR-107 status:\n\tTemperature:%d C\n"
               "\tProgrammed:%s Version:%d.%d\n"
               "\tImage:\"%s\"\n\tRomId:%d\n",
               (int) status.temperature,
               status.loadedImageInformation.programmed ? "Yes" : "No",
               status.loadedImageInformation.imageMajorRevisionNumber,
               status.loadedImageInformation.imageMinorRevisionNumber,
               buf,
               status.loadedImageInformation.imageROM_ID_Number
            );
    }
    return rc;
}

int bdk_aqr_reset(bdk_node_t node, int mdio_bus, int mdio_phy, int hard_reset)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    const char *msg;
    AQ_Retcode rc;
    if (hard_reset) {
        rc = AQ_API_HardReset(&aq_port);
        msg = "Hard";
    } else {
        rc = AQ_API_SoftReset(&aq_port);
        msg = "Soft";
    }
    if (AQ_RET_OK != rc)
        printf ("%s reset of AQR phy returned %d\n", msg, rc);
    else
        sayOK();
    return rc;
}

int bdk_aqr_raw_alarms(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_API_AlarmStatus alarm_status;
    bzero(&alarm_status, sizeof(alarm_status));
    AQ_Retcode rc;

    aqr_issue(rc,AQ_API_GetRawAlarmStatus, &aq_port, &alarm_status);
    if (AQ_RET_OK == rc)
     dump_response("Alarms:", &alarm_status, sizeof(alarm_status));
    return rc;
}

int bdk_aqr_debug_regs(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    char *regDump = malloc(1024*6); // requires 5025 bytes
    if (NULL == regDump) {
        bdk_error("Failed to allocate memory\n");
        return -1;
    }

    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    regDump[0] = '\0';
    printf("Collecting registers, it may take a while...\n");
    aqr_issue(rc,AQ_API_PrintDebugRegisters,&aq_port, regDump);
    if (AQ_RET_OK == rc) {
        puts(regDump);
        sayOK();
    }
    free(regDump);
    return rc;
}

int bdk_aqr_debug_trace(bdk_node_t node, int mdio_bus, int mdio_phy)
{
   char *traceDump = malloc(1024*20); // requires 18550 bytes
   if (NULL == traceDump) {
       bdk_error("Failed to allocate memory\n");
       return -1;
   }
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    traceDump[0] = '\0';
    printf("Collecting trace, it may take a while...\n");
    aqr_issue(rc,AQ_API_PrintDebugTrace,&aq_port, traceDump);

    if (AQ_RET_DEBUGTRACE_FREEZE_TIMEOUT != rc) {
        puts(traceDump);
        if (0 == rc) sayOK();
    } else {
        printf("No valid trace data\n");
    }
    free(traceDump);
    return rc;

}

int bdk_aqr_get_config(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_API_Configuration config;
    bzero(&config, sizeof(config));
    AQ_Retcode rc;
    aqr_issue(rc,AQ_API_GetConfiguration,&aq_port, &config);
    if (AQ_RET_OK == rc)
        dump_response("Configuration", &config, sizeof(config));

    return rc;
}

int bdk_aqr_flashinfo(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_API_FlashInformation flashinfo;
    bzero(&flashinfo, sizeof(flashinfo));
    AQ_Retcode rc;
    aqr_issue(rc,AQ_API_GetFlashInformation,&aq_port, &flashinfo);
    if (AQ_RET_OK == rc) {
        char buf[128];
        if (flashinfo.imageInformation.programmed) {
            for(unsigned i = 0; i < sizeof(flashinfo.imageInformation.imageID_String);i++) {
                if ('\0' == flashinfo.imageInformation.imageID_String[i]) {
                    buf[i] = '\0';
                    break;
                }
                buf[i] = flashinfo.imageInformation.imageID_String[i] > 0x1f ? flashinfo.imageInformation.imageID_String[i] : '.';
            }
            buf[sizeof(buf) - 1] = '\0';
        } else {
            buf[0] = '?';
            buf[1] = '\0';
        }
        const char *flashtype = unktoken;
        switch (flashinfo.flashType)
        {
            /*! Atmel 64K byte FLASH.*/
            makecase2(flashtype, AQ_API_F_,AT25F512A);
            /*! Atmel Smart 512K byte FLASH.*/
            makecase2(flashtype, AQ_API_F_,AT45DB041D);
            /*! Numonyx Microelectronics 64K byte FLASH.*/
            makecase2(flashtype, AQ_API_F_,M25P05A);
            /*! Atmel 256K byte byte FLASH.*/
            makecase2(flashtype, AQ_API_F_,AT25DF021A);
            /*! Atmel 512K byte byte FLASH.*/
            makecase2(flashtype, AQ_API_F_,AT25DF041A);
            /*! Numonyx 512K byte FLASH.*/
            makecase2(flashtype, AQ_API_F_,M25P40);
            /*! Macronix 512K byte FLASH.*/
            makecase2(flashtype, AQ_API_F_,MX25V4005C);
            /*! FLASH is not present as this is a daisy-chain slave device.*/
            makecase2(flashtype, AQ_API_F_,DaisyChainSlave);
            /*! FLASH is either absent or the type is unknown.*/
            makecase2(flashtype, AQ_API_F_,Indeterminate);
            /*! Adesto Smart 4M byte FLASH.*/
            makecase2(flashtype, AQ_API_F_,AT45DB321E);
        }
        printf("AQR-107 flash info:\n"
               "\tLoadCRC:%04x FlashType:%s(%d)\n"
               "\tProgrammed:%s Version:%d.%d\n"
               "\tImage:\"%s\"\n\tRomId:%d\n",
               flashinfo.flashLoadCRC, flashtype, flashinfo.flashType,
               flashinfo.imageInformation.programmed ? "Yes" : "No",
               flashinfo.imageInformation.imageMajorRevisionNumber,
               flashinfo.imageInformation.imageMinorRevisionNumber,
               buf,
               flashinfo.imageInformation.imageROM_ID_Number
            );
    }
    return rc;
}

int bdk_aqr_set_active(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);

    AQ_Retcode rc;
    aqr_issue(rc,AQ_API_SetActive,&aq_port);

    return rc;
}

int bdk_aqr_enable_daisychain(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);

    AQ_Retcode rc;
    aqr_issue(rc,AQ_API_EnableDaisyChain,&aq_port);

    return rc;
}

int bdk_aqr_set_an(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);

    AQ_Retcode rc;
    AQ_API_AutonegotiationControl anCtl;
    bzero(&anCtl,sizeof(anCtl));
    anCtl.advertise10GBASE_T = True;
    anCtl.shortReach = False;
    anCtl.advertise5G = False;
    anCtl.advertise2_5G = True;
    anCtl.advertise1000BASE_T_FullDuplex = False;
    anCtl.advertise1000BASE_T_HalfDuplex = False;
    anCtl.advertise100BASE_TX_FullDuplex = False;
    anCtl.advertise100BASE_TX_HalfDuplex = False;
    anCtl.advertise10BASE_T_FullDuplex = False;
    anCtl.advertise10BASE_T_HalfDuplex = False;
    anCtl.advertiseAsymmetricPAUSE = True;
    anCtl.enableAutomaticDownshift = False;
    anCtl.automaticDownshiftRetryAttempts = 4;
    anCtl.masterSlaveControl = AQ_API_AN_Automatic ;
    anCtl.portType = AQ_API_AN_SinglePort;
    anCtl.MDI_MDI_X_Control = AQ_API_MDC_Automatic;
    anCtl.forceConnRate = AQ_API_ForceConnRate_Autonegotiate; /* As opposed to forcing 100Mbps */

    aqr_issue(rc,AQ_API_SetAutonegotiationControl,&aq_port,&anCtl);

    return rc;
}

#define TF(x) ((x) ? "True" : "False")
int bdk_aqr_get_an(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);

    AQ_Retcode rc;
    AQ_API_AutonegotiationControl anCtl;
    bzero(&anCtl,sizeof(anCtl));

    aqr_issue(rc, AQ_API_GetAutonegotiationControl,&aq_port,&anCtl);
    printf("anCtl.advertise10GBASE_T = %s\n"
           "anCtl.shortReach = %s\n"
           "anCtl.advertise5G = %s\n"
           "anCtl.advertise2_5G = %s\n"
           "anCtl.advertise1000BASE_T_FullDuplex = %s\n"
           "anCtl.advertise1000BASE_T_HalfDuplex = %s\n"
           "anCtl.advertise100BASE_TX_FullDuplex = %s\n"
           "anCtl.advertise100BASE_TX_HalfDuplex = %s\n"
           "anCtl.advertise10BASE_T_FullDuplex = %s\n"
           "anCtl.advertise10BASE_T_HalfDuplex = %s\n"
           "anCtl.advertiseAsymmetricPAUSE = %s\n"
           "anCtl.enableAutomaticDownshift = %s\n"
           "anCtl.automaticDownshiftRetryAttempts = %d\n"
           "anCtl.masterSlaveControl = %s\n"
           "anCtl.portType = %s\n"
           "anCtl.MDI_MDI_X_Control = %s\n"
           "anCtl.forceConnRate = %s\n",
           TF(anCtl.advertise10GBASE_T ),
           TF(anCtl.shortReach ),
           TF(anCtl.advertise5G ),
           TF(anCtl.advertise2_5G ),
           TF(anCtl.advertise1000BASE_T_FullDuplex ),
           TF(anCtl.advertise1000BASE_T_HalfDuplex ),
           TF(anCtl.advertise100BASE_TX_FullDuplex ),
           TF(anCtl.advertise100BASE_TX_HalfDuplex ),
           TF(anCtl.advertise10BASE_T_FullDuplex ),
           TF(anCtl.advertise10BASE_T_HalfDuplex ),
           TF(anCtl.advertiseAsymmetricPAUSE ),
           TF(anCtl.enableAutomaticDownshift ),
           anCtl.automaticDownshiftRetryAttempts,
           anCtl.masterSlaveControl ?  ((1 == anCtl.masterSlaveControl) ? "AN_Master" : "AN_Slave") : "AN_Automatic",
           anCtl.portType ? "AN_MultiPort" : "AN_SinglePort",
           anCtl.MDI_MDI_X_Control ? ((2 ==anCtl.MDI_MDI_X_Control) ? "MDC_MDI_X" : "MDC_MDI") : "MDC_Automatic",
           anCtl.forceConnRate ? ((2 ==  anCtl.forceConnRate) ? "Other" : "100M") : "ForceConnRate_Autonegotiate"
        );

    return rc;
}

int bdk_aqr_get_fwlbk(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;

    AQ_API_FWManagedLoopbackControl   	loopback;
    AQ_API_FWManagedLoopbackRate  	rate;

    aqr_issue(rc,AQ_API_GetFWManagedLoopbackControl, &aq_port, &loopback, &rate);
    if (AQ_RET_OK == rc)
    {
        const char *lbk = unktoken;
        const char *rt = unktoken;
        switch (loopback)
        {
            makecase2(lbk, AQ_FWMLC_,No_LB);
            makecase2(lbk, AQ_FWMLC_,SysIntf_SysLB);
            makecase2(lbk, AQ_FWMLC_,SysIntf_SysLB_Passthrough);
            makecase2(lbk, AQ_FWMLC_,SysIntf_NetLB);
            makecase2(lbk, AQ_FWMLC_,SysIntf_NetLB_Passthrough);
            makecase2(lbk, AQ_FWMLC_,SysIntf_NetLB_PassthroughMerge);
            makecase2(lbk, AQ_FWMLC_,NetIntf_SysLB);
            makecase2(lbk, AQ_FWMLC_,NetIntf_SysLB_Passthrough);
            makecase2(lbk, AQ_FWMLC_,NetIntf_SysLB_Plug);
            makecase2(lbk, AQ_FWMLC_,NetIntf_NetLB);
            makecase2(lbk, AQ_FWMLC_,NetIntf_NetLB_Passthrough);
            makecase2(lbk, AQ_FWMLC_,CrossConnect_SysLB);
            makecase2(lbk, AQ_FWMLC_,CrossConnect_NetLB);
            makecase2(lbk, AQ_FWMLC_,Other);
        }

        switch(rate) {
            makecase2(rt, AQ_FWML,Rate_Auto);
            makecase2(rt, AQ_FWML,Rate_10G);
            makecase2(rt, AQ_FWML,Rate_5G);
            makecase2(rt, AQ_FWML,Rate_2_5G);
            makecase2(rt, AQ_FWML,Rate_1G);
            makecase2(rt, AQ_FWML,Rate_100M);
            makecase2(rt, AQ_FWML,Rate_Other);
        }

        printf(" Loopback is %s(%d)\n"
               " Loopback rate is %s(%d)\n",
               lbk, loopback,
               rt, rate);
    }
    return rc;
}

int bdk_aqr_set_fwlbk(bdk_node_t node, int mdio_bus, int mdio_phy, int lbktype, int neg_rate)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    const char *lbk = unktoken;
    const char *rt = unktoken;
    switch (lbktype)
    {
        makecase2(lbk, AQ_FWMLC_,No_LB);
        makecase2(lbk, AQ_FWMLC_,SysIntf_SysLB);
        makecase2(lbk, AQ_FWMLC_,SysIntf_SysLB_Passthrough);
        makecase2(lbk, AQ_FWMLC_,SysIntf_NetLB);
        makecase2(lbk, AQ_FWMLC_,SysIntf_NetLB_Passthrough);
        makecase2(lbk, AQ_FWMLC_,SysIntf_NetLB_PassthroughMerge);
        makecase2(lbk, AQ_FWMLC_,NetIntf_SysLB);
        makecase2(lbk, AQ_FWMLC_,NetIntf_SysLB_Passthrough);
        makecase2(lbk, AQ_FWMLC_,NetIntf_SysLB_Plug);
        makecase2(lbk, AQ_FWMLC_,NetIntf_NetLB);
        makecase2(lbk, AQ_FWMLC_,NetIntf_NetLB_Passthrough);
        makecase2(lbk, AQ_FWMLC_,CrossConnect_SysLB);
        makecase2(lbk, AQ_FWMLC_,CrossConnect_NetLB);
        makecase2(lbk, AQ_FWMLC_,Other);
    }

    switch(neg_rate) {
        makecase2(rt, AQ_FWML,Rate_Auto);
        makecase2(rt, AQ_FWML,Rate_10G);
        makecase2(rt, AQ_FWML,Rate_5G);
        makecase2(rt, AQ_FWML,Rate_2_5G);
        makecase2(rt, AQ_FWML,Rate_1G);
        makecase2(rt, AQ_FWML,Rate_100M);
        makecase2(rt, AQ_FWML,Rate_Other);
    }
    printf("Setting loopback to type %s at rate %s\n",lbk,rt);
    aqr_issue(rc,AQ_API_SetFWManagedLoopbackControl, &aq_port,
              (AQ_API_FWManagedLoopbackControl) lbktype,
              (AQ_API_FWManagedLoopbackRate) neg_rate);
    return rc;
}

int bdk_aqr_get_opmodes(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    AQ_API_10G_SystemOperatingMode som_10G;
    AQ_API_10G_NetworkOperatingMode nom_10G;
    AQ_API_1G_NetworkOperatingMode nom_1G;
    extern  AQ_Retcode AQ_API_GetOperatingModes(AQ_API_Port*,
                                                AQ_API_10G_SystemOperatingMode*,
                                                AQ_API_10G_NetworkOperatingMode*,
                                                AQ_API_1G_NetworkOperatingMode*);
    aqr_issue(rc,AQ_API_GetOperatingModes,
              &aq_port,
              &som_10G,
              &nom_10G,
              &nom_1G);

    const char *som = unktoken;
    const char *nom10 = som;
    const char *nom1 = som;
    switch (som_10G)
    {
        makecase(som,AQ_API_10G_SOM_XFI);
        makecase(som,AQ_API_10G_SOM_RXAUI_Marvell);
        makecase(som,AQ_API_10G_SOM_RXAUI_Dune);
        makecase(som,AQ_API_10G_SOM_XAUI);
        makecase(som,AQ_API_10G_SOM_Other);
     }
    switch(nom_10G)
    {
        /*! The MDI (RJ-45) serves as the network interface*/
        makecase(nom10,AQ_API_10G_NOM_10GBASE_T);
        /*! The XFI lookaside interface serves as the network interface*/
        makecase(nom10,AQ_API_10G_NOM_XFI);
        /*! Unrecognized mode*/
        makecase(nom10,AQ_API_10G_NOM_Other);
    }
    switch(nom_1G)
    {
        /*! The MDI (RJ-45) serves as the network interface (1000BASE-T when
          connected at 1G, 100BASE-TX when connected at 100M)*/
        makecase(nom1,AQ_API_1G_NOM_1000BASE_T);
        /*! The SGMII lookaside interface serves as the network interface*/
        makecase(nom1,AQ_API_1G_NOM_1000BASE_X);
        /*! Unrecognized mode*/
        makecase(nom1,AQ_API_1G_NOM_Other);
    }
    printf(" System Operations Mode %s(%d)\n"
           " Network Operations Mode[10] %s(%d)\n"
           " Network Operations Mode[1] %s(%d)\n"
           , som, som_10G, nom10,nom_10G, nom1, nom_1G);
    return rc;
}

int bdk_aqr_connstat(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    AQ_API_ConnectionStatus conn_stat;

    bzero(&conn_stat,sizeof(conn_stat));
    aqr_issue(rc, AQ_API_GetConnectionStatus, &aq_port, &conn_stat);
    const char *var = unktoken;
    switch(conn_stat.state)
    {
        makecase2(var, AQ_API_,ConnS_Reset);
        makecase2(var, AQ_API_,ConnS_Stall);
        makecase2(var, AQ_API_,ConnS_Inactive);
        makecase2(var, AQ_API_,ConnS_CableDiagnostics);
        makecase2(var, AQ_API_,ConnS_10G_Autoneg);
        makecase2(var, AQ_API_,ConnS_5G_Autoneg);
        makecase2(var, AQ_API_,ConnS_2_5G_Autoneg);
        makecase2(var, AQ_API_,ConnS_1G_Autoneg);
        makecase2(var, AQ_API_,ConnS_100M_Autoneg);
        makecase2(var, AQ_API_,ConnS_10G_Training);
        makecase2(var, AQ_API_,ConnS_5G_Training);
        makecase2(var, AQ_API_,ConnS_2_5G_Training);
        makecase2(var, AQ_API_,ConnS_1G_Training);
        makecase2(var, AQ_API_,ConnS_100M_Training);
        makecase2(var, AQ_API_,ConnS_10G_Connected);
        makecase2(var, AQ_API_,ConnS_5G_Connected);
        makecase2(var, AQ_API_,ConnS_2_5G_Connected);
        makecase2(var, AQ_API_,ConnS_1G_Connected);
        makecase2(var, AQ_API_,ConnS_1G_WoL_Connected);
        makecase2(var, AQ_API_,ConnS_100M_Connected);
        makecase2(var, AQ_API_,ConnS_100M_WoL_Connected);
        makecase2(var, AQ_API_,ConnS_LinkBreak);
        makecase2(var, AQ_API_,ConnS_TestMode);
        makecase2(var, AQ_API_,ConnS_LoopbackMode);
        makecase2(var, AQ_API_,ConnS_LowPowerMode);
        makecase2(var, AQ_API_,ConnS_Invalid);
    }
    const char *mast_slave;
    switch(conn_stat.masterSlaveStatus)
    {
    default: mast_slave = unktoken; break;
        makecase2(mast_slave,AQ_API_MSS_,Master);
        makecase2(mast_slave,AQ_API_MSS_,Slave);
    }

    const char *mdix;
    switch(conn_stat.MDI_MDI_X)
    {
    default: mdix = unktoken; break;
        makecase2(mdix, AQ_API_MS_,None);
        makecase2(mdix, AQ_API_MS_,MDI);
        makecase2(mdix, AQ_API_MS_,MDI_X);
    }
    const char *som;
    switch(conn_stat.sysIntfCurrentMode)
    {
    default: som = unktoken; break;
        makecase(som, AQ_API_SIOM_XFI);
        makecase(som, AQ_API_SIOM_BackplaneKR);
        makecase(som, AQ_API_SIOM_BackplaneKX);
        makecase(som, AQ_API_SIOM_XAUI);
        makecase(som, AQ_API_SIOM_XAUI_PauseBased);
        makecase(som, AQ_API_SIOM_RXAUI);
        makecase(som, AQ_API_SIOM_SGMII);
        makecase(som, AQ_API_SIOM_USXGMII);
        makecase(som, AQ_API_SIOM_MAC);
        makecase(som, AQ_API_SIOM_OFF);
        makecase(som, AQ_API_SIOM_Other);
    }
    const char *srate;
    switch (conn_stat.sysIntfCurrentRate)
    {
    default: srate = unktoken; break;
        makecase(srate, AQ_API_SIR_10M);
        makecase(srate, AQ_API_SIR_100M);
        makecase(srate, AQ_API_SIR_1G);
        makecase(srate, AQ_API_SIR_10G);
        makecase(srate, AQ_API_SIR_2_5G);
        makecase(srate, AQ_API_SIR_5G);
        makecase(srate, AQ_API_SIR_PowerDown);
        makecase(srate, AQ_API_SIR_Other);
    }
    const char *ans;
    switch( conn_stat.sysIntfAutonegStatus)
    {
    default: ans = unktoken; break;
        makecase2(ans, AQ_API_SIAS_,NA);
        makecase2(ans, AQ_API_SIAS_,NotComplete);
        makecase2(ans, AQ_API_SIAS_,Complete);
        makecase2(ans, AQ_API_SIAS_,Other);
    }
    if (AQ_RET_OK == rc) {
        printf("\tNet: farEndDeviceExists %d\n"
               "\tNet: energyOnLine %d\n"
               "\tNet: numberOfConnectionAttempts %d\n"
               "\tNet: state %s(%d)\n"
               "\tNet: duplex %s\n"
               "\tNet: MDI_MDI_X %s\n"
               "\tNet: masterSlaveStatus %s\n"
               "\tSys: sysIntfCurrentMode %s(%d)\n"
               "\tSys: sysIntfCurrentRate %s(%d)\n"
               "\tSys: txReady %d rxLinkUp %d\n"
               "\tSys: sysIntfAutonegStatus %s(%d)\n"
               ,
               conn_stat.farEndDeviceExists,
               conn_stat.energyOnLine,
               conn_stat.numberOfConnectionAttempts,
               var, conn_stat.state, conn_stat.duplex ? "Full" : "Half",
               mdix, mast_slave,
               som,conn_stat.sysIntfCurrentMode,
               srate,conn_stat.sysIntfCurrentRate,
               conn_stat.txReady, conn_stat.rxLinkUp,
               ans,conn_stat.sysIntfAutonegStatus
            );
    }
    return rc;
}
int  bdk_aqr_counters(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    AQ_API_10G_ConnectionStatus cs10;
    aqr_issue(rc, AQ_API_Get10G_ConnectionStatus, &aq_port, &cs10);
    if (rc == AQ_RET_OK) {
        if (cs10.connected) {
            printf("10G statistics:\n"
                   "\terroredLDPC_Frames: %u\n"
                   "\terroredCRC_Frames:  %u\n"
                   "\tgoodLDPC_Frames: %u\n"
                   "\tLPDCavg: %d.%d\n"
                   "\tnetIntfGoodTxEthernetFrames: %u\n"
                   "\tnetIntfGoodRxEthernetFrames: %u\n"
                   "\tnetIntfBadTxEthernetFrames: %u\n"
                   "\tnetIntfBadRxEthernetFrames: %u\n"
                   "\tsysIntfGoodTxEthernetFrames: %u\n"
                   "\tsysIntfGoodRxEthernetFrames: %u\n"
                   "\tsysIntfBadTxEthernetFrames: %u\n"
                   "\tsysIntfBadRxEthernetFrames: %u\n"
                   ,
                   cs10.erroredLDPC_Frames,
                   cs10.erroredCRC_Frames,
                   cs10.goodLDPC_Frames,
                   cs10. averageNumberOfIterations/10, cs10. averageNumberOfIterations%10,
                   cs10.netIntfGoodTxEthernetFrames,
                   cs10.netIntfGoodRxEthernetFrames,
                   cs10.netIntfBadTxEthernetFrames,
                   cs10.netIntfBadRxEthernetFrames,
                   cs10.sysIntfGoodTxEthernetFrames,
                   cs10.sysIntfGoodRxEthernetFrames,
                   cs10.sysIntfBadTxEthernetFrames,
                   cs10.sysIntfBadRxEthernetFrames
                );
        } else {
            AQ_API_100M_1G_ConnectionStatus cs1;
            aqr_issue(rc,AQ_API_Get100M_1G_ConnectionStatus, &aq_port, &cs1);
            if ((AQ_RET_OK == rc) && cs1.connected)
            {
                printf("100M_1G statistics:\n"
                       "\tsysIntfGoodTxEthernetFrames: %u\n"
                       "\tsysIntfGoodRxEthernetFrames: %u\n"
                       "\tsysIntfBadTxEthernetFrames: %u\n"
                       "\tsysIntfBadRxEthernetFrames: %u\n"
                       "\tsgmiiRxFalseCarrierEvents: %u\n"
                       "\tsgmiiCollisionEvents: %u\n"
                       "\trxFalseCarrierEvents: %u\n"
                       "\tcollisionEvents: %u\n"
                       "\tframeAlignmentEvents: %u\n"
                       "\truntFrameEvents: %u\n"
                       ,
                       cs1.sysIntfGoodTxEthernetFrames,
                       cs1.sysIntfGoodRxEthernetFrames,
                       cs1.sysIntfBadTxEthernetFrames,
                       cs1.sysIntfBadRxEthernetFrames,
                       cs1.sgmiiRxFalseCarrierEvents,
                       cs1.sgmiiCollisionEvents,
                       cs1.rxFalseCarrierEvents,
                       cs1.collisionEvents,
                       cs1.frameAlignmentEvents,
                       cs1.runtFrameEvents
                    );
            }
        }
    }
    return rc;
}

int bdk_aqr_restart_an(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;

    aqr_issue(rc, AQ_API_RestartAutonegotiation, &aq_port);

    return (rc == AQ_RET_OK) ? 0 : -1;
}

int bdk_aqr_get_configuration(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;

    AQ_API_Configuration cfg;
    bzero(&cfg,sizeof(cfg));
    aqr_issue(rc, AQ_API_GetConfiguration, &aq_port,&cfg);
    if (rc ==  AQ_RET_OK) {
        dump_response("config:",&cfg,sizeof(cfg));
        for(int i = 0; i < 2; i++) {
            printf(
                "LED[%d]_On = %s\n"
                "LED[%d]_10G = %s\n"
                "LED[%d]_5G = %s\n"
                "LED[%d]_2_5G = %s\n"
                "LED[%d]_1G = %s\n"
                "LED[%d]_100M = %s\n"
                "LED[%d]_CONNECTING = %s\n"
                "LED[%d]_TX = %s\n"
                "LED[%d]_RX = %s\n"
                "LED[%d]_Stretch = %d\n",
                i,TF(cfg.LED_Control[i].LED_On),
                i,TF(cfg.LED_Control[i].LED_On_When10G_LinkEstablished),
                i, TF(cfg.LED_Control[i].LED_On_When5G_LinkEstablished),
                i, TF(cfg.LED_Control[i].LED_On_When2_5G_LinkEstablished),
                i, TF(cfg.LED_Control[i].LED_On_When1G_LinkEstablished),
                i, TF(cfg.LED_Control[i].LED_On_When100M_LinkEstablished),
                i, TF(cfg.LED_Control[i].LED_On_WhenConnecting),
                i, TF(cfg.LED_Control[i].LED_TogglesOnTransmitActivity),
                i, TF(cfg.LED_Control[i].LED_TogglesOnReceiveActivity),
                i, cfg.LED_Control[i].LED_Stretch);
        }

    }
    return rc;
}

int bdk_aqr_set_led(bdk_node_t node, int mdio_bus, int mdio_phy, int led)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;

    AQ_API_Configuration cfg;
    bzero(&cfg,sizeof(cfg));
    aqr_issue(rc, AQ_API_GetConfiguration, &aq_port,&cfg);
    if ((rc ==  AQ_RET_OK) && (led < 6)){
        cfg.LED_Control[led].LED_On = cfg.LED_Control[led].LED_On ? False : True;
        if (cfg.LED_Control[led].LED_On) {
            cfg.LED_Control[led].LED_Stretch = AQ_API_LS_100ms ;
        }
        cfg.LED_Control[led^1].LED_On_WhenConnecting = cfg.LED_Control[led^1].LED_On_WhenConnecting ? False : True;
        aqr_issue(rc, AQ_API_SetConfiguration, &aq_port,&cfg);
    }

    return rc;
}

int bdk_aqr_get_static_config(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    AQ_API_StaticConfiguration cfg;
    bzero(&cfg,sizeof(cfg));
    aqr_issue(rc, AQ_API_GetStaticConfiguration, &aq_port,&cfg);
    if (rc ==  AQ_RET_OK) {
        dump_response("Static config:",&cfg,sizeof(cfg));
    }
    return rc;
}

int bdk_aqr_set_lbk(bdk_node_t node, int mdio_bus, int mdio_phy, int mode)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    AQ_API_LoopbackControl lbk = ( AQ_API_LoopbackControl) mode;
    aqr_issue(rc, AQ_API_SetLoopbackControl, &aq_port,lbk);
    if (0 == rc) {
        const char *var;
        switch(lbk)
        {
        default: var = unktoken;
            makecase(var,No_Loopback);
            makecase(var, SystemInterface_NetworkLoopback);
            makecase(var, NetworkInterface_SystemLoopback);
        }
        printf("Loopback mode is set to %s\n",var);
    }
    return rc;
}

int bdk_aqr_get_lbk(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    AQ_API_LoopbackControl lbk ;
    aqr_issue(rc, AQ_API_GetLoopbackControl, &aq_port,&lbk);
    if (0 == rc) {
        const char *var;
        switch(lbk)
        {
        default: var = unktoken;
            makecase(var,No_Loopback);
            makecase(var, SystemInterface_NetworkLoopback);
            makecase(var, NetworkInterface_SystemLoopback);
        }
        printf("Loopback mode is %s\n",var);
    }
    return rc;
}


int bdk_aqr_cablediag(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    aqr_issue(rc, AQ_API_RunBasicCableDiags, &aq_port);
    return rc;
}

int bdk_aqr_cablediag_result(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    AQ_API_BasicCableDiagResults diag_result;
    bzero(&diag_result,sizeof(diag_result));
    aqr_issue(rc, AQ_API_GetBasicCableDiagsResults, &aq_port,&diag_result);
    if (rc ==  AQ_RET_OK) {
        const char *A,*B,*C,*D;
        switch(diag_result.pairAResult.status)
        {
        default: A = unktoken; break;
            makecase(A, AQ_API_BasicPairStatus_OK);
            makecase(A, AQ_API_BasicPairStatus_Short);
            makecase(A, AQ_API_BasicPairStatus_LowMismatch);
            makecase(A, AQ_API_BasicPairStatus_HighMismatch);
            makecase(A, AQ_API_BasicPairStatus_Open);
            makecase(A, AQ_API_BasicPairStatus_CrossoverA);
            makecase(A, AQ_API_BasicPairStatus_CrossoverB);
            makecase(A, AQ_API_BasicPairStatus_CrossoverC);
            makecase(A, AQ_API_BasicPairStatus_CrossoverD);
        }
        switch(diag_result.pairBResult.status)
        {
        default: B = unktoken; break;
            makecase(B, AQ_API_BasicPairStatus_OK);
            makecase(B, AQ_API_BasicPairStatus_Short);
            makecase(B, AQ_API_BasicPairStatus_LowMismatch);
            makecase(B, AQ_API_BasicPairStatus_HighMismatch);
            makecase(B, AQ_API_BasicPairStatus_Open);
            makecase(B, AQ_API_BasicPairStatus_CrossoverA);
            makecase(B, AQ_API_BasicPairStatus_CrossoverB);
            makecase(B, AQ_API_BasicPairStatus_CrossoverC);
            makecase(B, AQ_API_BasicPairStatus_CrossoverD);
        }
        switch(diag_result.pairCResult.status)
        {
        default: C = unktoken; break;
            makecase(C, AQ_API_BasicPairStatus_OK);
            makecase(C, AQ_API_BasicPairStatus_Short);
            makecase(C, AQ_API_BasicPairStatus_LowMismatch);
            makecase(C, AQ_API_BasicPairStatus_HighMismatch);
            makecase(C, AQ_API_BasicPairStatus_Open);
            makecase(C, AQ_API_BasicPairStatus_CrossoverA);
            makecase(C, AQ_API_BasicPairStatus_CrossoverB);
            makecase(C, AQ_API_BasicPairStatus_CrossoverC);
            makecase(C, AQ_API_BasicPairStatus_CrossoverD);
        }
        switch(diag_result.pairDResult.status)
        {
        default: D = unktoken; break;
            makecase(D, AQ_API_BasicPairStatus_OK);
            makecase(D, AQ_API_BasicPairStatus_Short);
            makecase(D, AQ_API_BasicPairStatus_LowMismatch);
            makecase(D, AQ_API_BasicPairStatus_HighMismatch);
            makecase(D, AQ_API_BasicPairStatus_Open);
            makecase(D, AQ_API_BasicPairStatus_CrossoverA);
            makecase(D, AQ_API_BasicPairStatus_CrossoverB);
            makecase(D, AQ_API_BasicPairStatus_CrossoverC);
            makecase(D, AQ_API_BasicPairStatus_CrossoverD);
        }
        printf("\tPair A :%s reflections(m) %d %d %d %d\n"
               "\tPair B :%s reflections(m) %d %d %d %d\n"
               "\tPair C :%s reflections(m) %d %d %d %d\n"
               "\tPair D :%s reflections(m) %d %d %d %d\n",
               A,
               diag_result.pairAResult.reflection_1_Distance,
               diag_result.pairAResult.reflection_2_Distance,
               diag_result.pairAResult.reflection_3_Distance,
               diag_result.pairAResult.reflection_4_Distance,
               B,
               diag_result.pairBResult.reflection_1_Distance,
               diag_result.pairBResult.reflection_2_Distance,
               diag_result.pairBResult.reflection_3_Distance,
               diag_result.pairBResult.reflection_4_Distance,
               C,
               diag_result.pairCResult.reflection_1_Distance,
               diag_result.pairCResult.reflection_2_Distance,
               diag_result.pairCResult.reflection_3_Distance,
               diag_result.pairCResult.reflection_4_Distance,
               D,
               diag_result.pairDResult.reflection_1_Distance,
               diag_result.pairDResult.reflection_2_Distance,
               diag_result.pairDResult.reflection_3_Distance,
               diag_result.pairDResult.reflection_4_Distance
            );

    }
    return rc;
}

int bdk_aqr_lps(bdk_node_t node, int mdio_bus, int mdio_phy)
{
    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;
    AQ_API_LinkPartnerStatus lps;
    aqr_issue(rc, AQ_API_GetLinkPartnerStatus, &aq_port, &lps);
    if (0 == rc)
        dump_response("Cable diag:",&lps,sizeof(lps));
   return rc;
}


/*
 * Lua Interface
 */

/* LUA: Load image into phy memory */
static int aqr107_load(lua_State *L)
{
    int node = luaL_checkinteger(L,1);
    int mdio_bus = luaL_checkinteger(L,2);
    int mdio_phy = luaL_checkinteger(L,3);
    const uint8_t *img = (typeof(img)) luaL_checkstring(L, 4);
    int img_len = luaL_checkinteger(L, 5);
    int rc = __bdk_aqr_load_ext_image(node,mdio_bus,mdio_phy, img, img_len);
    if (0 == rc) sayOK();
    lua_pushnumber(L, rc);
    return 1;
}
/* LUA: Write image into phy flash */
static int aqr107_flash(lua_State *L)
{
    int node = luaL_checkinteger(L,1);
    int mdio_bus = luaL_checkinteger(L,2);
    int mdio_phy = luaL_checkinteger(L,3);
    const uint8_t *img = (typeof(img)) luaL_checkstring(L, 4);
    int img_len = luaL_checkinteger(L, 5);
    int rc = __bdk_aqr_write_ext_image(node,mdio_bus,mdio_phy, img, img_len);
    if (0 == rc) sayOK();
    lua_pushnumber(L, rc);
    return 1;
}
/* LUA: Verify flash image against cld */
static int aqr107_verify(lua_State *L)
{
    int node = luaL_checkinteger(L,1);
    int mdio_bus = luaL_checkinteger(L,2);
    int mdio_phy = luaL_checkinteger(L,3);
    const uint8_t *img = (typeof(img)) luaL_checkstring(L, 4);
    uint32_t img_len = (uint32_t) luaL_checkinteger(L, 5);

    AQ_API_Port aq_port;
    make_aqport(&aq_port, node, mdio_bus, mdio_phy);
    AQ_Retcode rc;

    rc = AQ_API_VerifyFlashImage(&aq_port, &img_len, img);
    if (AQ_RET_OK != rc) {
        const char *vfyStatus = unktoken;
        switch(rc)
        {
            makecase2(vfyStatus,AQ_RET_,FLASHINTF_READINESS_TIMEOUT);
            makecase2(vfyStatus,AQ_RET_,FLASH_READINESS_TIMEOUT);
            makecase2(vfyStatus,AQ_RET_,FLASH_TYPE_UNKNOWN);
            makecase2(vfyStatus,AQ_RET_,FLASH_TYPE_BAD);
            makecase2(vfyStatus,AQ_RET_,FLASH_IMAGE_CORRUPT);
            makecase2(vfyStatus,AQ_RET_,FLASH_IMAGE_TOO_LARGE);
            makecase2(vfyStatus,AQ_RET_,FLASH_IMAGE_MISMATCH);
        }
        printf("\tVerify flash image returned rc %d := %s\n",
               rc, vfyStatus);
    } else {
        sayOK();
    }

    lua_pushnumber(L, rc);
    return 1;
}

/* Build table of available phy image files - helpers*/
typedef struct {
    lua_State *L;
    int count;
    char *suffix;
} fmt_state;

static void table_formatter(const char *outbuf, void *fmts)
{
    fmt_state *state = fmts;
    char *p = strcasestr(outbuf,state->suffix);
    if ( p && (strlen(p) == strlen(state->suffix))) {
        if (0 == state->count)
            lua_newtable(state->L);
        lua_pushnumber(state->L,state->count);
        lua_pushstring(state->L,outbuf);
        lua_settable(state->L,-3);
        state->count += 1;
    }
}
/* LUA: Build table of available phy image files */
static int aqr107_listfiles(lua_State *L)
{
    const char *prefix = luaL_checkstring(L,1);
    fmt_state fmts = {.L = L, .suffix = ".cld", .count = 0};
    bdk_fs_list(prefix,table_formatter,(void*) &fmts);
    if (0 == fmts.count)
        lua_pushnil(L);
    return 1;
}

/**
 * Initialize the aqr107 LUA module
 *
 * @param L
 *
 * @return
 */
void register_aqr107(lua_State *L)
{
    lua_newtable(L);
    lua_pushcfunction(L, aqr107_listfiles);
    lua_setfield(L, -2, "list");
    lua_pushcfunction(L, aqr107_load);
    lua_setfield(L, -2, "load");
    lua_pushcfunction(L, aqr107_flash);
    lua_setfield(L, -2, "flash");
    lua_pushcfunction(L, aqr107_verify);
    lua_setfield(L, -2, "verify");
    /* Name yourself */
    lua_setfield(L, -2, "aqr107");
}
