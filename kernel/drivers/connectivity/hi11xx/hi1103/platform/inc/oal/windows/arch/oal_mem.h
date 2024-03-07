

#ifndef __OAL_WINDOWS_MEM_H__
#define __OAL_WINDOWS_MEM_H__

/* �궨�� */
#define OAL_HCC_HDR_LEN 8
#define OAL_MAX_CB_LEN  19
#define OAL_TX_CB_LEN   19

#define MAX_MAC_HEAD_LEN WLAN_MAX_MAC_HDR_LEN  // ������4��ַ�����MACͷ����30 4�ֽڶ��뵽32
#define MAC_HEAD_OFFSET  (OAL_NETBUF_MACHDR_BYTE_LEN - MAX_MAC_HEAD_LEN)
#define CB_OFFSET        (OAL_NETBUF_MACHDR_BYTE_LEN - MAX_MAC_HEAD_LEN - OAL_MAX_CB_LEN)

/* ����enhanced���͵�����ӿ����ͷŽӿڣ�ÿһ���ڴ�鶼����һ��4�ֽڵ�ͷ���� */
/* ����ָ���ڴ������ṹ��oal_mem_struc�������ڴ��Ľṹ������ʾ��           */
/*                                                                           */
/* +-------------------+------------------------------------------+---------+ */
/* | oal_mem_stru addr |                    payload               | dog tag | */
/* +-------------------+------------------------------------------+---------+ */
/* |      4 byte       |                                          | 4 byte  | */
/* +-------------------+------------------------------------------+---------+ */
#define OAL_MEM_INFO_SIZE 4

#define IORESOURCE_TYPE_BITS 0x00001f00 /* Resource type */
#define IORESOURCE_IO        0x00000100 /* PCI/ISA I/O ports */
#define IORESOURCE_MEM       0x00000200
#define IORESOURCE_REG       0x00000300 /* Register offsets */
#define IORESOURCE_IRQ       0x00000400
#define IORESOURCE_DMA       0x00000800
#define IORESOURCE_BUS       0x00001000

#define IORESOURCE_PREFETCH    0x00002000 /* No side effects */
#define IORESOURCE_READONLY    0x00004000
#define IORESOURCE_CACHEABLE   0x00008000
#define IORESOURCE_RANGELENGTH 0x00010000
#define IORESOURCE_SHADOWABLE  0x00020000

#define OAL_IORESOURCE_IO  IORESOURCE_IO
#define OAL_IORESOURCE_MEM IORESOURCE_MEM
#define OAL_IORESOURCE_REG IORESOURCE_REG

/*
 * ö����  : oal_mem_netbuf_pool_id_enum_uint8
 * ö��˵��: netbuf�ڴ��ID
 */
typedef enum {
    OAL_MEM_NETBUF_POOL_ID_SHORT_PKT = 0, /* ��֡�ڴ�� */
    OAL_MEM_NETBUF_POOL_ID_MGMT_PKT,      /* ����֡ */
    OAL_MEM_NETBUF_POOL_ID_LARGE_PKT,     /* ��֡�ڴ�� */
    OAL_MEM_NETBUF_POOL_ID_OAM_PKT,       /* SDT�ڴ�� */

    OAL_MEM_NETBUF_POOL_ID_BUTT
} oal_mem_netbuf_pool_id_enum;
typedef oal_uint8 oal_mem_netbuf_pool_id_enum_uint8;

/*
 * �ṹ��  : oal_netbuf_subpool_stru
 * �ṹ˵��: ��ϵͳ��netbuf���ڴ�ؽṹ��
 */
typedef struct {
    oal_uint16 us_free_cnt;    /* �����ڴ�ؿ����ڴ���� */
    oal_uint16 us_total_cnt;   /* �����ڴ���ڴ������ */
    oal_uint16 us_start_index; /* �����ڴ��paylaod����ʼindex */
    oal_uint16 us_len;         /* �����ڴ�ص��ڴ�鳤�� */

    /* ��¼oal_netbuf_stru�����ڴ���������ջ��Ԫ�أ�������Ϊoal_netbuf_struָ�� */
    oal_netbuf_stru *pst_free_stack;
} oal_netbuf_subpool_stru;

/*
 * �ṹ��  : oal_netbuf_pool_stru
 * �ṹ˵��: ��ϵͳ��netbuf�ڴ�����ýṹ��
 */
typedef struct oal_netbuf_pool {
    oal_uint16 us_max_byte_len;  /* ���ڴ�ؿɷ����ڴ����󳤶� */
    oal_uint16 us_mem_total_cnt; /* ���ڴ��һ���ж����ڴ�� */
    oal_uint16 us_mem_used_cnt;  /* ���ڴ�������ڴ�� */
    oal_uint8 uc_subpool_cnt;    /* ���ڴ��һ���ж������ڴ�� */
    oal_uint8 uc_reserved;
    /* ���ڴ������������ */
    oal_netbuf_subpool_stru ast_subpool_table[OAL_MEM_NETBUF_POOL_ID_BUTT];

} oal_netbuf_pool_stru;

/* �������� */
/* device ����ϵͳ�� host��ĺ������ */
extern oal_uint8 *oal_netbuf_cb(oal_netbuf_stru *pst_netbuf);
extern oal_uint8 *oal_netbuf_data(oal_netbuf_stru *pst_netbuf);
extern oal_uint8 *oal_netbuf_header(oal_netbuf_stru *pst_netbuf);
extern oal_uint8 *oal_netbuf_payload(oal_netbuf_stru *pst_netbuf);

extern oal_uint32 oal_netbuf_get_len(oal_netbuf_stru *pst_netbuf);
extern oal_netbuf_stru *oal_netbuf_alloc(oal_uint32 ul_size, oal_int32 l_reserve, oal_uint32 l_align);
extern oal_uint32 oal_mem_netbuf_free(oal_uint32 ul_file_id,
                                      oal_uint32 ul_line_num,
                                      oal_netbuf_stru *pst_netbuf,
                                      oal_uint8 uc_lock);
extern oal_uint32 oal_netbuf_free(oal_netbuf_stru *pst_netbuf);
extern oal_uint8 *oal_netbuf_get_mac_hdr_addr(oal_netbuf_stru *pst_netbuf);
extern oal_void oal_netbuf_queue_purge(oal_netbuf_head_stru *pst_netbuf_head);
extern oal_void oal_netbuf_set_len(oal_netbuf_stru *pst_netbuf, oal_uint32 ul_len);
extern oal_uint8 *oal_netbuf_get_hcc_hdr_addr(oal_netbuf_stru *pst_netbuf);
extern oal_uint8 *oal_netbuf_get_payload_addr(oal_netbuf_stru *pst_netbuf);
extern oal_netbuf_stru *oal_mem_multi_netbuf_alloc(oal_uint32 ul_file_id, oal_uint32 ul_line_num, oal_uint32 ul_len);
extern oal_netbuf_stru *oal_netbuf_get_ctrl_blk(oal_uint16 us_index);
extern oal_uint32 oal_mem_multi_netbuf_free(oal_uint32 ul_line_num, oal_netbuf_stru *pst_netbuf);

#endif /* end of oal_mm.h */