/*******************************************************************************
    Copyright 2008-2020 XXX Digital Technology Co., Ltd.
    FileName    : bootflash.h
    Description : define BOOT_PARMS
    Author      : JINWEI
    Date        : 2015.8.28
    Modification History:
    <version > <time> <author> <desc>
*******************************************************************************/
#ifndef __INCbootflashh
#define __INCbootflashh

#ifndef CFG_MAGIC
#define  CFG_MAGIC          0x5354524e  /* STRN */
#endif

#ifndef MAX_ETHERNET
#define MAX_ETHERNET        2
#endif

#ifndef MACADDR_LEN
#define MACADDR_LEN         6
#endif

#define PRODDATELEN         8           /* �������� */
#define PRODNUMLEN          9           /* 9λ�������к� */
#define SERIALNO_LEN        48          /* ���кų��� */
#define MODEL_LEN           64          /* �Զ����Ʒ�ͺų��� */

/* reserved feature numbers */
#define RESERVED_FEA_NUMS	15

typedef struct
{   
/* 256 bytes */
/* 0  */unsigned int        magicNumber;                            /* ���� */
/* 4  */unsigned int        paraChecksum;                           /* ���� */
/* 8  */unsigned int        paraLength;                             /* �ṹ���� */  /* ���͡����ȴ�'encryptVer'��ʼ���� */
/* 12 */unsigned int        encryptVer;                             /* ���ܰ汾:���ڿ��ƴ˽ṹ�ĸ��� */
/*
    ����4���û���������:�����������ļ����е�����һ��
*/
/* 16 */unsigned int        language;                               /* ���� */
/* 20 */unsigned int        device_class;                           /* ��Ʒ����, 1 -- DS9000 DVR, ... */
/* 24 */unsigned int        oemCode;                                /* oem ����: 1 -- hikvision�Լ�, ... */
/* 28 */unsigned char		upgradeVersion;						    /* �����汾��*/
/* 29 */unsigned char		reservedFeature[RESERVED_FEA_NUMS];		/* �����Ĳ�Ʒ���ԣ������������� */
/* 44 */unsigned short      encodeChans;                            /* ����·�� */
/* 46 */unsigned short      decodeChans;                            /* ����·�� */
/* 48 */unsigned short      ipcChans;                               /* IPCͨ���� */
/* 50 */unsigned short      ivsChans;                               /* ����ͨ���� */
/* 52 */unsigned char       picFormat;                              /* �������ֱ��� 0--CIF, 1--2CIF, 2--4CIF */
/* 53 */unsigned char       macAddr[MAX_ETHERNET][MACADDR_LEN];     /* �����ַ */
/* 65 */unsigned char       prodDate[PRODDATELEN];                  /* �������� */
/* 73 */unsigned char       prodNo[PRODNUMLEN];                     /* ��Ʒ��� */
/* 82 */unsigned char       devHigh;                                /* �߶� 1--1U, 2--2U                     */
/* 83 */unsigned char       cpuFreq;                                /* ARM��Ƶ: 1--400Mhz, 2--500Mhz ..      */
/* 84 */unsigned char       dspFreq;                                /* DSP��Ƶ: 1--700Mhz, 2--900Mhz ..      */
/* 85 */unsigned char       zone;                                   /* ���۵���: 1--��½ 2--��̨ 3--���� ... */
/* 86 */unsigned char       webSupport;                             /* ֧��WEB */
/* 87 */unsigned char       voipSupport;                            /* ֧��VOIP */
/* 88 */unsigned char       usbNums;                                /* USB����: 0��1��2 */
/* 89 */unsigned char       lcdSupport;                             /* ֧��LCD */
/* 90 */unsigned char       voNums;                                 /* ����VO����: 0��1��2 */
/* 91 */unsigned char       vganums;                                /* VGA����: 0��1��2 */
/* 92 */unsigned char       vtSupport;                              /* ֧�������Խ�  */
/* 93 */unsigned char       videoMaxtrix;                           /* ��Ƶ�������: 0 -- �ޣ�1 -- 16��4�� ... */
/* 94 */unsigned char       extendedDecoder;                        /* ��·������չ�� */
/* 95 */unsigned char       extendedIVS;                            /* ������Ƶ������չ�� */
/* 96 */unsigned char       extendedAlarmOut;                       /* ���������չ�� */
/* 97 */unsigned char       res1[3];
/*100 */unsigned short      devType;                                /* �豸�ͺţ�2���ֽ� */
/*102 */unsigned char       res2[2];
/*104 */unsigned int        ubootAdrs;                              /* uboot���flash��ַ       */
/*108 */unsigned int        ubootSize;                              /* uboot��С                */
/*112 */unsigned int        ubootCheckSum;                          /* ubootУ��ֵ              */
/*116 */unsigned int        tinyKernelAdrs;                         /* tinyKernel���flash��ַ  */
/*120 */unsigned int        tinyKernelSize;                         /* tinyKernel��С           */
/*124 */unsigned int        tinyKernelCheckSum;                     /* tinyKernelУ��ֵ         */
/*128 */unsigned char       devModel[MODEL_LEN];                    /* ��Ʒ�ͺ�:���ǹ����ͺţ����䵽64�ֽ� */
/*192 */unsigned char       writeDate[PRODDATELEN];                 /* �豸��Ϣ��������,ASCII */
/*200 */unsigned int        crypto;                                 /* �Ƿ���ܹ� 1���ǣ�0���� */
/*204 */unsigned int        kmem;                                   /* �ں�ʹ�õ��ڴ��С */
/*208 */unsigned int        dspmem;                                 /* DSP����ʹ�õ��ڴ��С */
/*212 */unsigned char       res3[44];
}BOOT_PARAMS;


/* Define Hardware version information */
#ifndef HVER_MAGIC
#define  HVER_MAGIC               0x48564552  /* HVER */
#endif

/* Hardware �ṹ��Ϣ */
typedef union {
    struct {
        u16    ddr_bitw           :4;   //[0..3]
        u16    ddr_freq           :4;   //[4..7]
        u16    arm_freq           :4;   //[8..11]
        u16    arm_chip           :4;   //[12..15]
    } bits;
    u16    reg;
} u_sys;

typedef union {
    struct {
        u16    reserve0           :4;   //[0..3]
        u16    encrypt_chip       :4;   //[4..7]
        u16    flash_volume       :4;   //[8..11]
        u16    flash_type         :4;   //[12..15]
    } bits;
    u16    reg;
} u_flash;

typedef union {
    struct {
        u16 day_u                 :4;   //[3..0]
        u16 day_d                 :2;   //[5..4]
        u16 month                 :4;   //[9..6]
        u16 year_u                :4;   //[13..10]
        u16 year_d                :2;   //[15..14]
    } bits;
    u16 reg;
}u_firmv;

typedef union {
    struct {
        u16    cpld_date          :4;   //[0..3]
        u16    rtc_inner          :4;   //[4..7]
        u16    device_type        :4;   //[8..11]
        u16    panel_type         :4;   //[12..15]
    } bits;
    u16    reg;
} u_peri;

typedef union {
    struct {
        u16    audio_intercom     :4;   //[0..3]
        u16    ad_type            :4;   //[4..7]
        u16    audio_input        :8;   //[8..15]
    } bits;
    u16    reg;
} u_auin;

typedef union {
    struct {
        u16    reserved0          :8;   //[0..7]
        u16    da_type            :4;   //[8..11]
        u16    audio_output       :4;   //[11..15]
    } bits;
    u16    reg;
} u_auout;

typedef union {
    struct{
        u16    reserve0           :4;   //[0..3]
        u16    reserve1           :4;   //[4..7]
        u16    mac1_mode          :4;   //[8..11]
        u16    mac0_mode          :4;   //[12..15]
    } bits;
    u16    reg;
} u_mac;

typedef union {
    struct {
        u16    phy1_chip          :8;   //[0..7]
        u16    phy0_chip          :8;   //[8..15]
    } bits;
    u16    reg;
} u_phytype;

typedef union {
    struct {
        u16    phy1_addr          :8;   //[0..7]
        u16    phy0_addr          :8;   //[8..15]
    } bits;
    u16    reg;
} u_phyaddr;

typedef union {
    struct{
        u16    esata_num          :4;   //[0..3]
        u16    pm_type            :4;   //[4..7]
        u16    sata_num           :8;   //[8..15]
    } bits;
    u16    reg;
} u_sata;

typedef union {
    struct{
        u16    reserve0           :4;   //[0..3]
        u16    reserve1           :4;   //[4..7]
        u16    hub_type           :4;   //[8..11]
        u16    usb_num            :4;   //[12..15]
    } bits;
    u16    reg;
} u_usb;

typedef union {
    struct {
        u16    alarm_out          :8;   //[0..7]
        u16    alarm_in           :8;   //[8..15]
    } bits;
    u16    reg;
} u_alarm;

typedef union {
    struct{
        u16    reserve0           :4;   //[0..3]
        u16    cvbs_num           :4;   //[4..7]
        u16    hdmi_num           :4;   //[8..11]
        u16    vga_num            :4;   //[12..15]
    } bits;
    u16    reg;
} u_vou;

typedef union {
    struct {
        u16    reserved0          :4;   //[0..3]
        u16    rs485_type         :4;   //[4..7]
        u16    rs485_num          :4;   //[8..11]
        u16    rs232_num          :4;   //[12..15]
    } bits;
    u16    reg;
} u_serial;

typedef union {
    struct {
        u16    reserve0           :4;   //[0..3]
        u16    reserve1           :4;   //[4..7]
        u16    reserve2           :4;   //[8..11]
        u16    reserve3           :4;   //[12..15]
    } bits;
    u16    reg;
} u_pcie;

typedef union {
    struct{
        u16    reserve0           :4;   //[0..3]
        u16    reserve1           :4;   //[4..7]
        u16    reserve2           :4;   //[8..11]
        u16    reserve3           :4;   //[12..15]
    } bits;
    u16    reg;
} u_video;

typedef struct {
		u32         magic;                  /*0*/
		u16         pcb;                    /*4*/
		u8          reserved[8];            /*6*/
		u16         board;                  /*E*/
		u_sys       sys;                    /*0x10*/
		u_flash     attr_flash;             /*0x12*/
		u_firmv     firmv;                  /*0x14*/
		u_peri      peri;                   /*0x16*/
		u_auin      audio_in;               /*0x18*/
		u_auout     audio_out;              /*0x1A*/ 
		u_mac       mac_mode;               /*0x1C*/
		u_phytype   phy_type;               /*0x1E*/
		u_phyaddr   phy_addr;               /*0x20*/
		u_sata      attr_sata;              /*0x22*/
		u_usb       attr_usb;               /*0x24*/
		u_alarm     alarm;                  /*0x26*/
		u_vou       if_vou;                 /*0x28*/
		u_serial    serial;                 /*0x2A*/
		u_pcie      pcie_flags;             /*0x2C*/
		u_video     video;                  /*0x2E*/
		u16         expand[8];              /*0x30*/
}hardware_info; /*64B */

#endif /* End of __INCbootflashh */
