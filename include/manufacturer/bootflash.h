/*******************************************************************************
    Copyright 2008-2020 XXX Digital Technology Co., Ltd.
    FileName    : bootflash.h
    Description : define BOOT_PARMS
    Author      : JINWEI
    Date        : 2015.8.28
    Modification History:
    <version > <time> <author> <desc>
*******************************************************************************/
#ifndef __BOOTFLASH_H
#define __BOOTFLASH_H

#ifndef CFG_MAGIC
#define  CFG_MAGIC              0x5354524e  /* STRN */
#endif

#ifndef MAX_ETHERNET
#define MAX_ETHERNET            6
#endif

#ifndef MACADDR_LEN
#define MACADDR_LEN             6
#endif

#ifndef SERIALNO_LEN
#define SERIALNO_LEN            48          /* ���кų��� */
#endif

/* reserved feature numbers */
#define RESERVED_FEA_NUMS       25
#define PRODDATELEN             8           /* �������� */
#define PRODNUMLEN              9           /* 9λ�������к� */
#define MODEL_LEN               64          /* �Զ����Ʒ�ͺų��� */
#define BOOT_PARAMS_LEN()       (sizeof(BOOT_PARAMS) - 12)

typedef struct {
/* 0  */unsigned int   magicNumber;                         /* ���� */
/* 4  */unsigned int   paraChecksum;                        /* ���� */
/* 8  */unsigned int   paraLength;                          /* �ṹ����  ���͡����ȴ�'encryptVer'��ʼ���� */
/* 12 */unsigned int   encryptVer;                          /* ���ܰ汾:���ڿ��ƴ˽ṹ�ĸ��� */

/*����4���û���������:�����������ļ����е�����һ��*/
/* 16 */unsigned int   language;                            /* ֧������ */
/* 20 */unsigned int   deviceClass;                         /* ��Ʒ���� */
/* 24 */unsigned int   oemCode;                             /* OEM���룺1---�����Լ� */
/* 28 */unsigned char  res1[RESERVED_FEA_NUMS];             /* ������Ʒ���ԣ������������� */
/* 53 */unsigned char  macAddr[MAX_ETHERNET][MACADDR_LEN];  /* �豸MAC��ַ */
/* 89 */unsigned char  prodDate[PRODDATELEN];               /* �豸��������,ASCII */
/* 97 */unsigned char  prodNo[PRODNUMLEN];                  /* �豸���к� */
/*106 */unsigned char  zone;                                /* ���۵��� */
/*107 */unsigned char  res2[21];
/*128 */unsigned int   devType;                             /* �豸���ͣ�4���ֽ� */
/*132 */unsigned char  devModel[MODEL_LEN];                 /* ��Ʒ�ͺ�:���ǹ����ͺţ����䵽64�ֽ� */
/*196 */unsigned char  writeDate[PRODDATELEN];              /* �豸��Ϣ��������,ASCII */
/*204 */unsigned int   crypto;                              /* �Ƿ���ܹ� 1���ǣ�0���� */
/*208 */unsigned char  res3[48];
} BOOT_PARAMS;

/* 512 Bytes */
typedef struct
{
    BOOT_PARAMS     boot_params;                                //boot����
    unsigned int    year;                                       //��ǰʱ�䣺�ꡢ�¡��ա�ʱ���֡���
    unsigned int    month;
    unsigned int    day;
    unsigned int    hour;
    unsigned int    minute;
    unsigned int    second;
    unsigned int    dayofweek;
    unsigned int    dogId;                                      //������Ա��ID(���ܹ�����ˮ��)
    unsigned int    formatFlash;                                //0 --- ����ʽ����1 --- ��ʽ��
    unsigned int    irewrite;                                   //0 --- ����д��  1 --- ��д
    unsigned char   res[512 - 296];
}PRODUCT_INFO, *PPRODUCT_INFO;

/* Define Hardware version information */
#ifndef HVER_MAGIC
#define  HVER_MAGIC               0x48564552  /* HVER */
#endif

/* Hardware �ṹ��Ϣ */
typedef union {
    struct {
        unsigned short    ddr_bitw           :4;   //[0..3]
        unsigned short    ddr_freq           :4;   //[4..7]
        unsigned short    arm_freq           :4;   //[8..11]
        unsigned short    arm_chip           :4;   //[12..15]
    } bits;
    unsigned short    reg;
} u_sys;

typedef union {
    struct {
        unsigned short    reserve0           :4;   //[0..3]
        unsigned short    encrypt_chip       :4;   //[4..7]
        unsigned short    flash_volume       :4;   //[8..11]
        unsigned short    flash_type         :4;   //[12..15]
    } bits;
    unsigned short    reg;
} u_flash;

typedef union {
    struct {
        unsigned short day_u                 :4;   //[3..0]
        unsigned short day_d                 :2;   //[5..4]
        unsigned short month                 :4;   //[9..6]
        unsigned short year_u                :4;   //[13..10]
        unsigned short year_d                :2;   //[15..14]
    } bits;
    unsigned short reg;
}u_firmv;

typedef union {
    struct {
        unsigned short    cpld_date          :4;   //[0..3]
        unsigned short    rtc_inner          :4;   //[4..7]
        unsigned short    device_type        :4;   //[8..11]
        unsigned short    panel_type         :4;   //[12..15]
    } bits;
    unsigned short    reg;
} u_peri;

typedef union {
    struct {
        unsigned short    audio_intercom     :4;   //[0..3]
        unsigned short    ad_type            :4;   //[4..7]
        unsigned short    audio_input        :8;   //[8..15]
    } bits;
    unsigned short    reg;
} u_auin;

typedef union {
    struct {
        unsigned short    reserved0          :8;   //[0..7]
        unsigned short    da_type            :4;   //[8..11]
        unsigned short    audio_output       :4;   //[11..15]
    } bits;
    unsigned short    reg;
} u_auout;

typedef union {
    struct{
        unsigned short    reserve0           :4;   //[0..3]
        unsigned short    reserve1           :4;   //[4..7]
        unsigned short    mac1_mode          :4;   //[8..11]
        unsigned short    mac0_mode          :4;   //[12..15]
    } bits;
    unsigned short    reg;
} u_mac;

typedef union {
    struct {
        unsigned short    phy1_chip          :8;   //[0..7]
        unsigned short    phy0_chip          :8;   //[8..15]
    } bits;
    unsigned short    reg;
} u_phytype;

typedef union {
    struct {
        unsigned short    phy1_addr          :8;   //[0..7]
        unsigned short    phy0_addr          :8;   //[8..15]
    } bits;
    unsigned short    reg;
} u_phyaddr;

typedef union {
    struct{
        unsigned short    esata_num          :4;   //[0..3]
        unsigned short    pm_type            :4;   //[4..7]
        unsigned short    sata_num           :8;   //[8..15]
    } bits;
    unsigned short    reg;
} u_sata;

typedef union {
    struct{
        unsigned short    reserve0           :4;   //[0..3]
        unsigned short    reserve1           :4;   //[4..7]
        unsigned short    hub_type           :4;   //[8..11]
        unsigned short    usb_num            :4;   //[12..15]
    } bits;
    unsigned short    reg;
} u_usb;

typedef union {
    struct {
        unsigned short    alarm_out          :8;   //[0..7]
        unsigned short    alarm_in           :8;   //[8..15]
    } bits;
    unsigned short    reg;
} u_alarm;

typedef union {
    struct{
        unsigned short    reserve0           :4;   //[0..3]
        unsigned short    cvbs_num           :4;   //[4..7]
        unsigned short    hdmi_num           :4;   //[8..11]
        unsigned short    vga_num            :4;   //[12..15]
    } bits;
    unsigned short    reg;
} u_vou;

typedef union {
    struct {
        unsigned short    reserved0          :4;   //[0..3]
        unsigned short    rs485_type         :4;   //[4..7]
        unsigned short    rs485_num          :4;   //[8..11]
        unsigned short    rs232_num          :4;   //[12..15]
    } bits;
    unsigned short    reg;
} u_serial;

typedef union {
    struct {
        unsigned short    reserve0           :4;   //[0..3]
        unsigned short    reserve1           :4;   //[4..7]
        unsigned short    reserve2           :4;   //[8..11]
        unsigned short    reserve3           :4;   //[12..15]
    } bits;
    unsigned short    reg;
} u_pcie;

typedef union {
    struct{
        unsigned short    reserve0           :4;   //[0..3]
        unsigned short    reserve1           :4;   //[4..7]
        unsigned short    reserve2           :4;   //[8..11]
        unsigned short    reserve3           :4;   //[12..15]
    } bits;
    unsigned short    reg;
} u_video;

typedef struct {
		unsigned int magic;                 /*0*/
		unsigned short pcb;                 /*4*/
		unsigned char reserved[8];          /*6*/
		unsigned short board;               /*E*/
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
		unsigned short expand[8];           /*0x30*/
}hardware_info; /*64B */

#endif /* End of __INCbootflashh */

